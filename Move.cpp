#include "Main.h"

void Move_00(_enemy*);
void Move_01(_enemy*);
void Move_02(_enemy*);
void Move_03(_enemy*);
void (*Move[])(_enemy*) =
{
	Move_00,
	Move_01,
	Move_02,
	Move_03
};

/*�e���v���F�ǉ����_�㐔���ύX�E��̊֐��|�C���^�ɒǉ�

//����
void Move_01(_enemy* e)
{

}

*/

///�G�ړ����C���A�b�v�f�[�g����

//������ʂ����܂ō~��邾��
void Move_00(_enemy* e)
{
	e->MoveY(e->GetSpeed());
}
//������ƍ~��Ď~�܂�
void Move_01(_enemy* e)
{
	if(e->GetCnt() <= 60)
		e->MoveY(e->GetSpeed());
	else if(e->GetCnt() >= 360)
		e->MoveY(-(e->GetSpeed() / 2));
}
//������ʂ����Ɉړ����邾��
void Move_02(_enemy* e)
{
	e->MoveX(e->GetSpeed());
}
//������Ɖ��ړ����Ď~�܂�
void Move_03(_enemy* e)
{
	if (e->GetCnt() <= 60)
		e->MoveX(e->GetSpeed());
	else if (e->GetCnt() >= 360)
		e->MoveX(-(e->GetSpeed()));
}