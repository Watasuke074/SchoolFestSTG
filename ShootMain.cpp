#include "Main.h"

int EnemyBulHitBox(String);

void ShootMain::Init()
{
	for (auto i : step(2))
		SE[i] = false;
	  cnt = 0;
	score = 0;
	stage = 0;
	graze = 0;
	for (auto i : step(ENEMY_READY_MAX))
		enemyReady[i].Clear();
	CSVload(stage);
	sTitle.reset();
	player.Clear();
	ClearBul(-1);
	for (auto i : step(ENEMY_MAX))
		enemy[i].Clear();
}

void ShootMain::CSVload(int stage)
{
	String a = U"Data/csv/{}.csv"_fmt(stage);
	int cnt; Vec2 pos; int shotKnd, moveKnd, shotCnt, hp; double sp; String name;
	CSVData csv(U"Data/csv/{}.csv"_fmt(stage));
	for (auto i : step(csv.rows()))
	{
		if (i < 2) continue;
		pos.set(csv.get<int>(i, 0), csv.get<int>(i, 1));
		    cnt = csv.get<int>(i, 2);
		shotKnd = csv.get<int>(i, 3);
		moveKnd = csv.get<int>(i, 4);
		     sp = csv.get<double>(i, 5);
		shotCnt = csv.get<int>(i, 6);
		     hp = csv.get<int>(i, 7);
		   name = csv.get<String>(i, 8);
		enemyReady[i-2].SetEnemyReady(cnt, pos, shotKnd, moveKnd, sp, shotCnt, hp, name);
	}
}

void ShootMain::Update()
{
	if (KeyEscape.down()) Init();
	Print << cnt;
	Print << enemy[0].IsActive();
	player.Update();
	for (auto i : step(ENEMY_MAX))
	{
		bool f=false;
		if (enemy[i].IsActive())
			f=enemy[i].Update();
		if (f)
			ActiveBul(i);
	}
	for (auto i : step(ENEMY_READY_MAX))
	{
		//出現時間になったら
		if (enemyReady[i].startCnt == cnt)
		{
			for (auto j : step(ENEMY_MAX))
				if (!enemy[j].IsActive())
				{
					enemyReady[i].Clear();
					enemy[j].Active(enemyReady[i]);
					break;
				}
		}
	}
	UpdateBul();
	Draw();
	HitBox();
	AudioPlay();
	cnt++;
}

void ShootMain::Draw()
{
	Scene::Rect().draw(Palette::Darkcyan);
	player.Draw();
	for (auto i : step(ENEMY_MAX))
	{
		if (enemy[i].IsActive())
			//ステージタイトル
			if (enemy[i].GetName() == U"-1")
			{
				//リセット
				if (!sTitle.isRunning())
				{
					sTitle.restart();
					Periodic::Jump0_1(0s);
				}
				double t = Periodic::Jump0_1(5s,sTitle.sF());
				Rect(0, 250, 700, 150).draw(ColorF(0.2, t));
				if(sTitle >= 1.5s)
				FontAsset(U"main")(U"STAGE {}"_fmt(stage))
					.draw(Arg::bottomLeft=Vec2(FILED_X,400).lerp( Vec2(10,400),EaseInOutCirc(Min(sTitle.sF()-1.5,1.0)) ), ColorF(0.85, t));
				//8秒で終了
				if (sTitle > 5s)
				{
					sTitle.reset();
					enemy[i].Clear();
				}
				Print << sTitle;
			}
			else enemy[i].Draw();
	}
	DrawBul();
	//すこあ・残り残機
	FontAsset(U"score")(U"SCORE") .draw(0, 0);
	FontAsset(U"score")(U"{:0>10}"_fmt(score)) .draw(0, 20);
	if(player.GetHP() > 0)
	for (auto i : step(player.GetHP()))
		Shape2D::Star(15, Vec2(15 + 25 * i, 60)).draw(ColorF(0.9,0.1,0.2));
	//グレイズ数
	FontAsset(U"graze")(U"{:0>3}"_fmt(graze)) .draw(Arg::topCenter(FILED_X/2, 0));
	//ハイスコア・残りボム数
	FontAsset(U"score")(U"HIGH-SCORE").draw(Arg::topRight(FILED_X, 0));
	FontAsset(U"score")(U"{:0>10}"_fmt(hScore)).draw(Arg::topRight(FILED_X, 20));
	if (player.GetHaveBom() > 0)
	for (auto i : step(player.GetHaveBom()))
		Circle(Arg::topRight(FILED_X-(10 + 25*i), 60) , 10).draw(ColorF(0.3, 0.8, 0.2));
}

void ShootMain::HitBox()
{
	bool isHit[2]{ false,false };
	Circle grazeBox(player.GetPos(), GRAZE_BOX);
	Circle bombBox(player.GetPos(), player.GetBombR());
	Circle playerBox(player.GetPos(),PLAYER_BOX);
	Circle playerBulBox(PLAYERBUL_BOX);
	Circle  enemyBulBox;
	Circle  enemyBox(ENEMY_BOX);
	///敵との当たり判定
	
	//敵-ボム
	for (auto i : step(ENEMY_MAX))
		if (enemy[i].IsActive() && player.IsBomb())
		{
			enemyBox.setPos(enemy[i].GetPos());
			if (enemyBox.intersects(bombBox))
			{
				enemy[i].Hit(10);
				if (!enemy[i].IsActive())
				{
					ScoreUp(500);
					SE[0] = true;
				}
			}
		}
	for (auto j : step(PLAYER_SHOT_MAX))
		if (player.bul[j].f)
		{
			for (auto k : step((int)player.bul[j].sp))
			{
				playerBulBox.setPos(player.bul[j].pos);
				//playerBulBox.draw(Palette::Yellowgreen);
				for (auto i : step(ENEMY_MAX))
				{
					if (enemy[i].IsActive())
					{
						enemyBox.setPos(enemy[i].GetPos());
						//enemyBox.draw(Palette::Skyblue);
						//敵-自機ショット
						if (enemyBox.intersects(playerBulBox))
						{
							enemy[i].Hit();
							if (!enemy[i].IsActive())
							{
								ScoreUp(500);
								SE[0] = true;
							}
							player.bul[j].Clear();
							break;
						}
					}
				}
				player.bul[j].pos.y--;
				player.bul[j].sp--;
			}
		}
	//敵-自機ショットおわり
	///敵との当たり判定おわり

	///自機との当たり判定
	//自機-敵弾
	for (auto i : step(MANAGER_MAX))
		if (bulManager[i].f)
		for (auto j : step(BUL_MAX))
		//弾が有効なら
		if (bulManager[i].bul[j].f)
		{
			enemyBulBox.setPos(bulManager[i].bul[j].pos);
			enemyBulBox.setR( EnemyBulHitBox(bulManager[i].bul[j].name) );
			//enemyBulBox.draw(Palette::Blueviolet);
			//grazeBox.draw(Palette::Burlywood);
			//playerBox.draw(Palette::Olive);
			if (enemyBulBox.intersects(playerBox))
			{
				bulManager[i].bul[j].Clear();
				player.Hit();
			}
			if (player.IsBomb() && enemyBulBox.intersects(bombBox))
				bulManager[i].bul[j].Clear();
			else if (enemyBulBox.intersects(grazeBox) && !bulManager[i].bul[j].isGrazed)
			{
				graze++;
				SE[1] = true;
				bulManager[i].bul[j].isGrazed = true;
			}
		}
}

void ShootMain::ScoreUp(int p)
{
	score += p+p*(graze * 0.2);
	if (score > hScore) hScore = score;
}

void ShootMain::AudioPlay()
{
	if (SE[0]) AudioAsset(U"enemyDead").playOneShot(0.4);
	if (SE[1]) AudioAsset(U"graze").playOneShot(0.8);
	for (auto i : step(2))
		SE[i] = false;
}

//弾幕の種類によって当たり判定の大きさを変える
//画像名は（例：bul0）なので最後を取得する
int EnemyBulHitBox(String s)
{
	char t = s.back();
	int r;
	switch (t)
	{
	case '0':
		r = 6;
		break;
	default:
		r = 3;
		break;
	}
	return r;
}