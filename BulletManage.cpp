#include "Main.h"

void ShootMain::ClearBul(int a)
{
	if (a == -1)
	for (auto i : step(MANAGER_MAX))
	{
		bulManager[i].cnt = 0;
		bulManager[i].f = false;
		bulManager[i].knd = -1;
		for (auto j : step(BUL_MAX))
			bulManager[i].bul[j].Clear();
	}
	else
	{
		bulManager[a].cnt = 0;
		bulManager[a].f = false;
		bulManager[a].knd = -1;
		for (auto i : step(BUL_MAX))
			bulManager[a].bul[i].Clear();
	}
}

void ShootMain::UpdateBul()
{
	for(auto i:step(MANAGER_MAX))
	if(bulManager[i].f)
	{
		//発射した敵がいないならこれ以上追加しない
		if (!enemy[bulManager[i].enemy].IsActive())
			bulManager[i].f = 2;
		_shot_arg arg{ &bulManager[i], &enemy[bulManager[i].enemy], &player };
		//更新
		if(bulManager[i].knd!=-1 && bulManager[i].f == 1)
			Shot[bulManager[i].knd](arg);

		bool activeBul=false;
		for(auto j:step(BUL_MAX))
			if (bulManager[i].bul[j].f)
			{
				activeBul = true;
				//弾の移動
				bulManager[i].bul[j].pos.x += cos(bulManager[i].bul[j].ang) * bulManager[i].bul[j].sp;
				bulManager[i].bul[j].pos.y += sin(bulManager[i].bul[j].ang) * bulManager[i].bul[j].sp;
				bulManager[i].bul[j].cnt++;
				//場外なら消す
				if
					(
						bulManager[i].bul[j].pos.x < -30 ||
						bulManager[i].bul[j].pos.x > FILED_X + 30 ||
						bulManager[i].bul[j].pos.y > FILED_Y + 30 ||
						bulManager[i].bul[j].pos.y < -30
					)
					bulManager[i].bul[j].Clear();
			}
		if (!activeBul && bulManager[i].f == 2)
			ClearBul(i);

		bulManager[i].cnt++;
	}
}

void ShootMain::ActiveBul(int en)
{
	for (auto i : step(MANAGER_MAX))
		if (!bulManager[i].f)
		{
			ClearBul(i);
			bulManager[i].f     = 1;
			bulManager[i].enemy = en;
			bulManager[i].knd = enemy[en].GetShotKnd();
			return;
		}
}


//画像(必ず正方形）の一辺の長さを返す
//画像名は（例：bul0）なので最後を取得する
int BulletSize(String s)
{
	char t = s.back();
	int a;
	switch (t)
	{
	case '0':
		a = 20;
		break;
	default:
		a = 0;
		break;
	}
	return a;
}
void ShootMain::DrawBul()
{
	for (auto i : step(MANAGER_MAX))
		if (bulManager[i].f)

		for (auto j : step(BUL_MAX))
			if (bulManager[i].bul[j].f)
			{
				int   a = BulletSize(bulManager[i].bul[j].name);
				int col = bulManager[i].bul[j].col;
				TextureAsset(bulManager[i].bul[j].name)(col*a, 0, a, a).drawAt(bulManager[i].bul[j].pos);
			}
}