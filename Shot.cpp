#include"Main.h"

/*�e���v���F�ǉ����_�㐔���ύX�E��̊֐��|�C���^�ɒǉ�

//����
void Shot_(_shot_arg arg)
{
	int cnt = arg.e->GetCnt();
}

*/

//���@�_���̊p�x��Ԃ�
double PlayerAim(_shot_arg arg)
{
	double y = arg.p->GetPos().y - arg.e->GetPos().y;
	double x = arg.p->GetPos().x - arg.e->GetPos().x;
	return atan2(y,x);
}

///�e�����C���A�b�v�f�[�g����

//���@�_�������
void Shot_00(_shot_arg arg)
{
	if (arg.bul->cnt == 0)
	{
		int i = arg.bul->Search();
		if (i != -1)
		{
			//�o�^
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg), 4, U"bul0", 0);
		}
	}
}
//���@�_���A��
void Shot_01(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt < 160 && cnt % 15 == 0)
	{
		int j = arg.bul->Search();
		if (j != -1)
		{
			//�o�^
			arg.bul->bul[j].Active(arg.e->GetPos(), PlayerAim(arg), 4, U"bul0", Random(0, 9));
		}
	}
}
//�p�x�Œ莩�@�_���A��
void Shot_02(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt == 0) arg.bul->ang = PlayerAim(arg);
	if (cnt != 0 && cnt < 160 && cnt % 15 == 0)
	{
		int j = arg.bul->Search();
		if (j != -1)
		{
			//�o�^
			arg.bul->bul[j].Active(arg.e->GetPos(), arg.bul->ang, 4, U"bul0", Random(0,9));
		}
	}
}
//�~�`�ɔ���
void Shot_03(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt < 180 && cnt % 30 == 0)
	{
		double ang = PlayerAim(arg);
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//�o�^
				arg.bul->bul[j].Active(arg.e->GetPos(), ang + (PI * 2) / 15 * i, 4, U"bul0", i % 8);
			}
		}
	}
}
//���ʂ܂ŉ~�`�ɂ���
void Shot_04(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt % 40 == 0)
	{
		double ang = PlayerAim(arg);
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//�o�^
				arg.bul->bul[j].Active(arg.e->GetPos(), ang + (PI * 2) / 15 * i, 4, U"bul0", i % 8);
			}
		}
	}
}
//�����܂��~�`�ɔ���
void Shot_05(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt < 180 && cnt % 10 == 0)
	{
		double ang = PlayerAim(arg);
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//�o�^
				arg.bul->bul[j].Active(arg.e->GetPos(), (ang + cnt/10) + (PI*2)/15*i, 4, U"bul0", i%8);
			}
		}
	}
}
//�����������炵�ĉ~�`�ɔ���
void Shot_06(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt == 10)
		arg.bul->ang = PlayerAim(arg);
	if (cnt != 0 && cnt < 100 && cnt % 10 == 0)
	{
		for (auto i : step(15))
		{
			int j = arg.bul->Search();
			if (j != -1)
			{
				//�o�^
				arg.bul->bul[j].Active(arg.e->GetPos(), (arg.bul->ang + (cnt/10)*0.5) + (PI*2)/15*i, 3, U"bul0", i%8);
			}
		}
	}
}
//�G�܂ň꒼���ɑ��x�Ⴂ�e
void Shot_07(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt == 0)
	{
		for (auto i : step(10))
		{
			int j = arg.bul->Search();
			if (j != -1)
				arg.bul->bul[j].Active(arg.e->GetPos(), PlayerAim(arg), 3+(i*0.2), U"bul0", i % 10);
		}
	}
}
//�ォ�炾�񂾂񑬂��e���o��
void Shot_08(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt % 2 == 0 && cnt < 14)
	{
		int j = arg.bul->Search();
		if (j != -1)
		{
			//�o�^
			arg.bul->bul[j].Active(arg.e->GetPos(), PlayerAim(arg), 3+(cnt/2), U"bul0", Random(0, 9));
		}
	}
}
//3way
void Shot_09(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt < 180 && cnt % 30 == 0)
	{
		int i;
		//�o�^

		//��
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)-(10*PI / 180), 4, U"bul0", 0);
		//�^��
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)              , 4, U"bul0", 0);
		//�E
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)+(10*PI / 180), 4, U"bul0", 0);
	}
}
//2way
void Shot_10(_shot_arg arg)
{
	int cnt = arg.bul->cnt;
	if (cnt != 0 && cnt < 180 && cnt % 30 == 0)
	{
		int i;
		//�o�^

		//��
		i = arg.bul->Search();
		if (i != -1)
			arg.bul->bul[i].Active(arg.e->GetPos(), PlayerAim(arg)-(5*PI / 180), 4, U"bul0", 0);
		//�E
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
	Shot_09,
	Shot_10
};