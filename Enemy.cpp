#include "Main.h"
int EnemyHitBox(String);

_enemy::_enemy()
{
	Clear();
}
void _enemy::Clear()
{
	f = false;
	cnt = 0;
	anm = 0;
	hp = 20;
}
void _enemy::Hit(int a)
{
	hp -= a;
	if (hp <= 0) Clear();
}
bool _enemy::Update(int q)
{
	cnt++;
	//移動、画面外なら消去
	//pos.y += 2;
	if (moveKnd != -1)
		Move[moveKnd](this);
	if  (	pos.x < -70 ||
			pos.x > FILED_X + 70 ||
			pos.y > FILED_Y + 70 ||
			pos.y < -70
		) Clear();
	//アニメーション
	anm++;
	//登場しばらくしたら弾を打つ
	if (cnt == shotCnt)
		return true;
	else return false;
}
void _enemy::Draw()
{
	//Enemy
	if (name != U"-1")
		TextureAsset(U"enemy{}_{}"_fmt(name, (anm/6)%3 )).drawAt(pos);
	for (auto i : step(20))
	{
		if (bul[i].f)
			TextureAsset(bul[i].name).drawAt(bul[i].pos);
	}
}
void _enemy::Active(_enemyReady e)
{
	       f = true;
	     cnt = 0;
		 pos = e.pos;
	 shotKnd = e.shotKnd;
	 moveKnd = e.moveKnd;
	      sp = e.sp;
	 shotCnt = e.shotCnt;
	      hp = e.hp;
	    name = e.name;
		data = e.data;
		 box = EnemyHitBox(name);
}

//敵の種類によって当たり判定の大きさを変える
//画像名は（例：bul0）なので最後を取得する
int EnemyHitBox(String s)
{
	char t = s.back();
	int r=20;
	switch (t)
	{
	case '0':
		r = 23;
		break;
	case '1':
		r = 46;
		break;
	}
	return r;
}