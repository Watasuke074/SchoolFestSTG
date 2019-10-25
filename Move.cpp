#include "Main.h"

void Move_00(_enemy*);
void Move_01(_enemy*);
void Move_02(_enemy*);
void Move_03(_enemy*);
void Move_04(_enemy*);
void (*Move[])(_enemy*) =
{
	Move_00,
	Move_01,
	Move_02,
	Move_03,
	Move_04
};

/*テンプレ：追加後は_後数字変更・上の関数ポインタに追加

//説明
void Move_01(_enemy* e)
{

}

*/

///敵移動メインアップデート部分

//ただ画面したまで降りるだけ
void Move_00(_enemy* e)
{
	e->MoveY(e->GetSpeed());
}
//ちょっと降りて止まってしばらくしたら上がる
void Move_01(_enemy* e)
{
	if(e->GetCnt() <= 60)
		e->MoveY(e->GetSpeed());
	else if(e->GetCnt() >= 300)
		e->MoveY(-(e->GetSpeed() / 2));
}
//ただ画面を横に移動するだけ
void Move_02(_enemy* e)
{
	e->MoveX(e->GetSpeed());
}
//ちょっと横移動して止まってしばらくしたら外に出る
void Move_03(_enemy* e)
{
	if (e->GetCnt() <= 60)
		e->MoveX(e->GetSpeed());
	else if (e->GetCnt() >= 360)
		e->MoveX(-(e->GetSpeed()));
}
//けっこう降りてかなり止まる(ボス用)
void Move_04(_enemy* e)
{
	if (e->GetCnt() <= 120)
		e->MoveY(e->GetSpeed());
	else if (e->GetCnt() >= 720)
		e->MoveX(-(e->GetSpeed()));
}