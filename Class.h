#pragma once
#ifdef  GL_SET
#define GL
#else
#define GL extern
#endif

///弾幕管理用クラス類
///弾幕(弾のまとまり,_bulManager)→弾幕が使用する弾一つ一つ(bul)

//弾一つ一つ
typedef struct 
{
	bool f;
	//グレイズしたかどうか
	bool isGrazed;
	//座標
	Vec2 pos;
	//画像名
	String name;
	//カウンタ、弾の色
	int cnt, col;
	//速度、角度
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

//弾幕
typedef struct
{
	int f=false;//0-無効、1-有効、2-新規登録なし（発射されない）
	int knd;
	int cnt;
	int enemy;
	double ang;//角度の一時保存
	bullet bul[BUL_MAX];
	int Search()
	{
		for (auto i : step(BUL_MAX))
			if (!bul[i].f) return i;
		return -1;
	}
}_bulManager;


//プレイヤー
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
		//無敵かどうか、描画するか
		bool isSA, isDraw;
		//自機の回転、無敵点滅アニメーション
		int anm, anmSA;
		//残機、残りボム数,無敵経過時間
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


//敵
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
		//出 て か ら  ショットを打つまでの時間
		int shotCnt;
		//ショット、移動の種類
		int shotKnd, moveKnd;
		//移動速度
		double sp;
		//当たり判定の大きさ
		int box;
		//画像名
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


//弾幕更新時の引数用
typedef struct {
	_bulManager* bul;
	_enemy* e;
	_player* p;
}_shot_arg;