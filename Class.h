#pragma once
#ifdef  GL_SET
#define GL
#else
#define GL extern
#endif

///�e���Ǘ��p�N���X��
///�e��(�e�̂܂Ƃ܂�,_bulManager)���e�����g�p����e����(bul)

//�e����
typedef struct 
{
	bool f;
	//�O���C�Y�������ǂ���
	bool isGrazed;
	//���W
	Vec2 pos;
	//�摜��
	String name;
	//�J�E���^�A�e�̐F
	int cnt, col;
	//���x�A�p�x
	double sp, ang;
	void Active(Vec2 _pos, double _ang, double _sp, String picName, int _col)
	{
		   f = true;
	isGrazed = false;
		 cnt = 0;
		 pos = _pos;
		 ang = _ang;
		  sp = _sp;
		name = picName;
		 col = _col;
	}
	void Clear(){ f = false; }
}bullet;

//�e��
typedef struct
{
	int f=false;//0-�����A1-�L���A2-�V�K�o�^�Ȃ��i���˂���Ȃ��j
	int knd;
	int cnt;
	int enemy;
	double ang;//�p�x�̈ꎞ�ۑ�
	bullet bul[BUL_MAX];
	int Search()
	{
		for (auto i : step(BUL_MAX))
			if (!bul[i].f) return i;
		return -1;
	}
}_bulManager;


//�v���C���[
class _player
{
	private:
		struct
		{
			bool f;
			double r;
			Stopwatch cnt;
		}bomb;
	protected:
		Vec2 pos;
		Vec2 beforePos;
		//���G���ǂ����A�`�悷�邩
		bool isSA, isDraw;
		//���@�̉�]�A���G�_�ŃA�j���[�V����
		int anm, anmSA;
		//�c�@�A�c��{����,���G�o�ߎ���
		int hp, haveBom, cnt;
		int shotTime;
	public:
		bullet bul[20];
		_player();
		virtual void Clear();
		virtual void Update();
		virtual void Draw();

		void Hit();
		int GetHP() { return hp; };
		int GetHaveBom() { return haveBom; };
		bool IsBomb() { return bomb.f; };
		double GetBombR() { return bomb.r; };
		Vec2 GetPos() { return pos; };
		void MoveX(double x) { pos.x += x; };
		void MoveY(double y) { pos.y += y; };
		 int BulSearch();
};


//�G
typedef struct
{
	int startCnt; Vec2 pos; int shotKnd, moveKnd, shotCnt, hp; double sp; String name;
	void SetEnemyReady(int _cnt, Vec2 _pos, int _shotKnd, int _moveKnd, double _sp, int _shotCnt, int _hp, String _name)
	{
		startCnt = _cnt;
		     pos = _pos;
		 shotKnd = _shotKnd;
		 moveKnd = _moveKnd;
		      sp = _sp;
		 shotCnt = _shotCnt;
		      hp = _hp;
		    name = _name;
	}
	void Clear()
	{
		startCnt = -1;
	}
}_enemyReady;

class _enemy : public _player
{
	protected:
		bool f;
		//�o �� �� ��  �V���b�g��ł܂ł̎���
		int shotCnt;
		//�V���b�g�A�ړ��̎��
		int shotKnd, moveKnd;
		//�ړ����x
		double sp;
		//�����蔻��̑傫��
		int box;
		//�摜��
		String name;
	public:
		_enemy();
		void Active(_enemyReady);
		void Clear() override;
		bool Update(int);
		void Draw() override;

		void Hit(int a=1);
		bool IsActive() { return f;}
		 int GetCnt() { return cnt; }
		 int GetBox() { return box; }
		 int GetShotKnd() { return shotKnd; }
		 int GetMoveKnd() { return moveKnd; }
		String GetName() { return name; }
		double GetSpeed() { return sp; }
};
class _boss : public _enemy
{
public:
	void Active();
	void Clear()  override;
	void Update() override;
	void Draw()   override;
};


//�e���X�V���̈����p
typedef struct {
	_bulManager* bul;
	_enemy* e;
	_player* p;
}_shot_arg;