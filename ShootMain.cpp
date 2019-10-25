#include "Main.h"

int EnemyBulHitBox(String);

void ShootMain::Init()
{
	gameover = false;
	for (auto i : step(3))
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
	boss.Clear();
	for (auto i : step(ENEMY_MAX))
		enemy[i].Clear();
}

void ShootMain::CSVload(int stage)
{
	int p = 0;
	String a = U"Data/csv/{}.csv"_fmt(stage);
	int cnt; Vec2 pos; int shotKnd, moveKnd, shotCnt, hp; double sp; String name; Array<double> data;
	CSVData csv(U"Data/csv/{}.csv"_fmt(stage));
	data.clear();
	for (auto i : step(csv.rows()))
	{
		if (i < 2) continue;
		if (csv.get<String>(i, 0).starts_with(U"#")) continue;
		p++;
		pos.set(csv.get<int>(i, 0), csv.get<int>(i, 1));
		    cnt = csv.get<int>(i, 2);
		shotKnd = csv.get<int>(i, 3);
		moveKnd = csv.get<int>(i, 4);
		     sp = csv.get<double>(i, 5);
		shotCnt = csv.get<int>(i, 6);
		     hp = csv.get<int>(i, 7);
		   name = csv.get<String>(i, 8);
		   for (auto j : step(csv.columns(i)-8))
			   data << csv.get<double>(i, 9+j);
		enemyReady[p].SetEnemyReady(cnt, pos, shotKnd, moveKnd, sp, shotCnt, hp, name, data);
	}
}

void ShootMain::Update()
{
	//if (KeyEscape.down()) Init();
	if (cnt == 2500)
	{
		cnt = 0;
		CSVload(stage);
	}
	//Print << cnt;
	if(!gameover)player.Update();
	for (auto i : step(ENEMY_MAX))
	{
		bool f=false;
		if (enemy[i].IsActive())
			f=enemy[i].Update(0);
		if (f)
			ActiveBul(i);
	}
	for (auto i : step(ENEMY_READY_MAX))
	{
		//�o�����ԂɂȂ��ă{�X�����Ȃ��Ȃ�
		if (enemyReady[i].startCnt == cnt && !boss.IsActive())
		{
			for (auto j : step(ENEMY_MAX))
				if (!enemy[j].IsActive())
				{
					if (enemyReady[i].name == U"-2")
						boss.Active();
					else
						enemy[j].Active(enemyReady[i]);
					enemyReady[i].Clear();
					break;
				}
		}
	}
	UpdateBul();
	if(!gameover)HitBox();
	AudioPlay();
	Draw();
	cnt++;
}

void ShootMain::Draw()
{
	Scene::Rect().draw(Palette::Darkcyan);
	if(!gameover) player.Draw();
	for (auto i : step(ENEMY_MAX))
	{
		if (enemy[i].IsActive())
			//�X�e�[�W�^�C�g��
			if (enemy[i].GetName() == U"-1")
			{
				//���Z�b�g
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
				//8�b�ŏI��
				if (sTitle > 5s)
				{
					sTitle.reset();
					enemy[i].Clear();
				}
				//Print << sTitle;
			}
			else enemy[i].Draw();
	}
	DrawBul();
	//�������E�c��c�@
	FontAsset(U"score")(U"SCORE") .draw(0, 0);
	FontAsset(U"score")(U"{:0>10}"_fmt(score)) .draw(0, 20);
	if(player.GetHP() > 0)
	for (auto i : step(player.GetHP()))
		Shape2D::Star(15, Vec2(15 + 25 * i, 60)).draw(ColorF(0.9,0.1,0.2));
	//�O���C�Y��
	FontAsset(U"graze")(U"{:0>3}"_fmt(graze)) .draw(Arg::topCenter(FILED_X/2, 0));
	//�n�C�X�R�A�E�c��{����
	FontAsset(U"score")(U"HIGH-SCORE").draw(Arg::topRight(FILED_X, 0));
	FontAsset(U"score")(U"{:0>10}"_fmt(hScore)).draw(Arg::topRight(FILED_X, 20));
	if (player.GetHaveBom() > 0)
	for (auto i : step(player.GetHaveBom()))
		Circle(Arg::topRight(FILED_X-(10 + 25*i), 60) , 10).draw(ColorF(0.3, 0.8, 0.2));
	/*if (Key0.down())
		gameover = true;*/
	if (gameover)
	{
		Rect(0, 300, 800, 200).draw(ColorF(0.2, 0.8));
		FontAsset(U"main")(U"GAMEOVER\n\n\nPress Space")
			.drawAt(Vec2(FILED_X/2,FILED_Y/2));
		FontAsset(U"score")(U"Score:{}\nHighScore:{}"_fmt(score, hScore))
			.drawAt(Vec2(FILED_X/2,FILED_Y/2 + 10));
		if (KeySpace.down())
		{
			Init();
			now = 0;
		}
	}
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
	///�G�Ƃ̓����蔻��
	
	//�G-�{��
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
						enemyBox=Circle(enemy[i].GetPos(),enemy[i].GetBox());
						//enemyBox.draw(Palette::Skyblue);
						//�G-���@�V���b�g
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
	//�G-���@�V���b�g�����
	///�G�Ƃ̓����蔻�肨���

	///���@�Ƃ̓����蔻��
	//���@-�G�e
	for (auto i : step(MANAGER_MAX))
		if (bulManager[i].f)
		for (auto j : step(BUL_MAX))
		//�e���L���Ȃ�
		if (bulManager[i].bul[j].f)
		{
			enemyBulBox.setPos(bulManager[i].bul[j].pos);
			enemyBulBox.setR( EnemyBulHitBox(bulManager[i].bul[j].name) );
			//enemyBulBox.draw(Palette::Blueviolet);
			//grazeBox.draw(Palette::Burlywood);
			//playerBox.draw(Palette::Olive);
			if (enemyBulBox.intersects(playerBox))
			{
				if (player.GetHP() == 0)
					gameover = true;
				else
				{
					bulManager[i].bul[j].Clear();
					if (player.Hit())
						SE[2] = true;
				}
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
	if (SE[0]) AudioAsset(U"enemyDead").playOneShot(0.3);
	if (SE[1]) AudioAsset(U"graze").playOneShot(0.6);
	if (SE[2]) AudioAsset(U"playerDead").playOneShot(0.5);
	for (auto i : step(3))
		SE[i] = false;
}

//�e���̎�ނɂ���ē����蔻��̑傫����ς���
//�摜���́i��Fbul0�j�Ȃ̂ōŌ���擾����
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