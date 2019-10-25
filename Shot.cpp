#include"Main.h"

/*テンプレ：追加後は_後数字変更・上の関数ポインタに追加

//説明
void Shot_(_shot_arg arg)
{
	int cnt = arg.e->GetCnt();
}

*/

//自機狙いの角度を返す
double PlayerAim(_shot_arg arg)
{
	double y = arg.p->GetPos().y - arg.e->GetPos().y;
	double x = arg.p->GetPos().x - arg.e->GetPos().x;
	return atan2(y,x);
}
//連射する時、現在のカウント、合計発射数と発射間隔を計算して発射するかどうかのフラグを返す
bool BlazeBullet(int cnt, int totalShot, int shotSpace)
{
	return (cnt != 0 && cnt < (totalShot+1) * shotSpace && cnt % shotSpace == 0);
}
//死ぬまでショットをやめない時
bool ForeverBullet(int cnt, int shotSpace)
{
	return (cnt != 0 && cnt % shotSpace == 0);
}

///弾幕メインアップデート部分
//自機狙い連射
void Shot_00(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (BlazeBullet(cnt,arg.e->GetData(0), arg.e->GetData(1)))
	{
		int j = arg.bul->Search();
		if (j != -1)
		{
			//登録
			arg.bul->bul[j].Active(arg.e->GetPos(), PlayerAim(arg), 4, U"bul0", Random(0, 9));
		}
	}
}
//角度固定自機狙い連射
void Shot_01(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt == 0) arg.bul->ang = PlayerAim(arg);
	if (BlazeBullet(cnt, arg.e->GetData(0), arg.e->GetData(1)))
	{
		int j = arg.bul->Search();
		if (j != -1)
		{
			//登録
			arg.bul->bul[j].Active(arg.e->GetPos(), arg.bul->ang, 4, U"bul0", Random(0,9));
		}
	}
}
//円形に発射
void Shot_02(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (BlazeBullet(cnt, arg.e->GetData(0), arg.e->GetData(1)))
	{
		double ang = PlayerAim(arg);
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//登録
				arg.bul->bul[j].Active(arg.e->GetPos(), ang + (PI * 2) / 15 * i, 4, U"bul0", i % 8);
			}
		}
	}
}
//しぬまで円形にうて
void Shot_03(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (ForeverBullet(cnt, arg.e->GetData(1)))
	{
		double ang = PlayerAim(arg);
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//登録
				arg.bul->bul[j].Active(arg.e->GetPos(), ang + (PI * 2) / 15 * i, 4, U"bul0", i % 8);
			}
		}
	}
}
//うずまき円形に発射
void Shot_04(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (BlazeBullet(cnt, arg.e->GetData(0), arg.e->GetData(1)))
	{
		double ang = PlayerAim(arg);
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//登録
				arg.bul->bul[j].Active(arg.e->GetPos(), (ang + cnt/10) + (PI*2)/15*i, 4, U"bul0", i%8);
			}
		}
	}
}
//すこしずつずらして円形に発射
void Shot_05(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt == 10)
		arg.bul->ang = PlayerAim(arg);
	if (BlazeBullet(cnt, arg.e->GetData(0), arg.e->GetData(1)))
	{
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//登録
				arg.bul->bul[j].Active(arg.e->GetPos(), (arg.bul->ang + (cnt/10)*0.5) + (PI*2)/15*i, 3, U"bul0", i%8);
			}
		}
	}
}
//敵まで一直線に速度違い弾
void Shot_06(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt == 0)
	{
		for (auto i : step((int)arg.e->GetData(0)))
		{
			int j = arg.bul->Search();
			if (j != -1)
				arg.bul->bul[j].Active(arg.e->GetPos(), PlayerAim(arg), 3+(i*0.2), U"bul0", i % 10);
		}
	}
}
//後からだんだん速い弾が出る
void Shot_07(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt % 2 == 0 && cnt < 14)
	{
		int j = arg.bul->Search();
		if (j != -1)
		{
			//登録
			arg.bul->bul[j].Active(arg.e->GetPos(), PlayerAim(arg), 3+(cnt/2), U"bul0", Random(0, 9));
		}
	}
}
//3way
void Shot_08(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (BlazeBullet(cnt, arg.e->GetData(0), arg.e->GetData(1)))
	{
		int i;
		//登録

		//左
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)-(10*PI / 180), 4, U"bul0", 0);
		//真ん中
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)              , 4, U"bul0", 0);
		//右
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)+(10*PI / 180), 4, U"bul0", 0);
	}
}
//2way
void Shot_09(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (BlazeBullet(cnt, arg.e->GetData(0), arg.e->GetData(1)))
	{
		int i;
		//登録

		//左
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)-(5*PI / 180), 4, U"bul0", 0);
		//右
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)+(5*PI / 180), 4, U"bul0", 0);
	}
}

//------------------------------------//
//------------------------------------//
//------------------------------------//
void (*Shot[])(_shot_arg arg) =
{
	Shot_00,
	Shot_01,
	Shot_02,
	Shot_03,
	Shot_04,
	Shot_05,
	Shot_06,
	Shot_07,
	Shot_08,
	Shot_09
};