#pragma once

//ƒeƒ“ƒvƒŒ
class scene
{
public:
	scene(){ Init(); }
	virtual void Init()   {};
	virtual void Update() {};
	virtual void Draw()   {};
};

class Title : public scene
{
private:
	Font title;
public:
	Title() { Init(); };
	void Init()   override;
	void Update() override;
	void Draw()   override;
};

class ShootMain : public scene
{
private:
	bool gameover = false;
	bool SE[3];
	int cnt;
	int stage;//ˆê–Ê=0
	Stopwatch sTitle;
	int graze;
	_player player;
	_enemy enemy[ENEMY_MAX];
	_enemyReady enemyReady[ENEMY_READY_MAX];
	_boss boss;
	_bulManager bulManager[MANAGER_MAX];
public:
	ShootMain() { Init(); };
	void Init()   override;
	void Update() override;
	void Draw()   override;

	void CSVload(int);
	void ScoreUp(int);
	void HitBox();
	void AudioPlay();

	void ClearBul(int);
	void ActiveBul(int);
	void UpdateBul();
	void DrawBul();
};