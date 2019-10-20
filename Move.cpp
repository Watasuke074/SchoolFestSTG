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

/*ƒeƒ“ƒvƒŒF’Ç‰ÁŒã‚Í_Œã”Žš•ÏXEã‚ÌŠÖ”ƒ|ƒCƒ“ƒ^‚É’Ç‰Á

//à–¾
void Move_01(_enemy* e)
{

}

*/

///“GˆÚ“®ƒƒCƒ“ƒAƒbƒvƒf[ƒg•”•ª

//‚½‚¾‰æ–Ê‚µ‚½‚Ü‚Å~‚è‚é‚¾‚¯
void Move_00(_enemy* e)
{
	e->MoveY(e->GetSpeed());
}
//‚¿‚å‚Á‚Æ~‚è‚ÄŽ~‚Ü‚é
void Move_01(_enemy* e)
{
	if(e->GetCnt() <= 60)
		e->MoveY(e->GetSpeed());
	else if(e->GetCnt() >= 300)
		e->MoveY(-(e->GetSpeed() / 2));
}
//‚½‚¾‰æ–Ê‚ð‰¡‚ÉˆÚ“®‚·‚é‚¾‚¯
void Move_02(_enemy* e)
{
	e->MoveX(e->GetSpeed());
}
//‚¿‚å‚Á‚Æ‰¡ˆÚ“®‚µ‚ÄŽ~‚Ü‚é
void Move_03(_enemy* e)
{
	if (e->GetCnt() <= 60)
		e->MoveX(e->GetSpeed());
	else if (e->GetCnt() >= 360)
		e->MoveX(-(e->GetSpeed()));
}
//‚¯‚Á‚±‚¤~‚è‚ÄŽ~‚Ü‚é
void Move_04(_enemy* e)
{
	if (e->GetCnt() <= 120)
		e->MoveY(e->GetSpeed());
}