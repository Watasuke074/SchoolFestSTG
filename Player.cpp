#include "Main.h"

_player::_player()
{
	Clear();
}

void _player::Clear()
{
	isSA   = true;
	isDraw = true;
	bomb.f = false;
	bomb.cnt.reset();
	anm = 0;
	anmSA = 0;
	hp = 2;
	haveBom = 3;
	cnt = 0;
	pos.set(300, 770);
	shotTime = 0;
	for (auto i : step(PLAYER_SHOT_MAX))
		bul[i].Clear();
}
void _player::Hit()
{
	if (isSA) return;
	isSA = true;
	hp--;
	haveBom = 3;
	//pos.set(300, 770);
	anm = 0;
	shotTime = 0;
}

bool _player::Update()
{
	beforePos = pos;
	//key
	double sp = (bomb.f)? PLAYER_SP_FAST*1.5 : PLAYER_SP_FAST, move=1.0;
	if (KeyLShift.pressed() || KeyRShift.pressed())
		sp = (bomb.f) ? PLAYER_SP_SLOW*1.5 : PLAYER_SP_SLOW;
	int direct[2] = {0,0};
	if (KeyRight.pressed()) direct[0] =  1;//みぎ
	if (KeyLeft.pressed() ) direct[0] = -1;//ひだり
	if (KeyDown.pressed() ) direct[1] =  1;//した
	if (KeyUp.pressed()   ) direct[1] = -1;//うえ
	//pad
	for (const auto userIndex : step(Gamepad.MaxUserCount))
	{
		if (const auto pad = Gamepad(userIndex))
		{
			if (pad.povRight.pressed()) direct[0] = 1;//みぎ
			if (pad.povLeft.pressed())  direct[0] = -1;//ひだり
			if (pad.povDown.pressed())  direct[1] = 1;//した
			if (pad.povUp.pressed())    direct[1] = -1;//うえ
			break;
		}
	}
	//移動
	if (abs(direct[0]) + abs(direct[1]) == 2)
		move = 0.70710678118;
	pos.x += direct[0] * sp * move;
	pos.y += direct[1] * sp * move;
	//アニメーション
	anm++;
	if (anm >= 18)
		anm = 0;
	//無敵、ボムの更新
	if (isSA)
	{
		anmSA++;
		if (anmSA == 5)
		{
			anmSA = 0;
			isDraw = !isDraw;
		}
		cnt++;
		if (cnt == 180)
		{
			isSA = false;
			isDraw = true;
			cnt = 0;
			anmSA = 0;
		}
	}
	if (bomb.f)
	{
		isSA = true;
		bomb.r -= 0.5;
		if (bomb.cnt.s() >= 7)
		{
			bomb.f = false;
			bomb.r = false;
			bomb.cnt.reset();
		}
	}
	//画面内に収める
	pos.x = Clamp(pos.x, (double)30, (double)FILED_X-30);
	pos.y = Clamp(pos.y, (double)30, (double)FILED_Y-30);
	//if (pos.x < 30) pos.x = 30;
	//if (pos.y < 30) pos.y = 30;
	//if (pos.x > FILED_X-30) pos.x = FILED_X - 30;
	//if (pos.y > FILED_Y-30) pos.y = FILED_Y - 30;
	//弾
	for (auto i : step(PLAYER_SHOT_MAX))
	{
		if (bul[i].f)
		{
			bul[i].pos.y -= bul[i].sp;
			bul[i].sp = 32;
			if (bul[i].pos.y <= -32)
				bul[i].f = false;
		}
	}
	if (KeyX.down() && haveBom > 0 && !bomb.f)
	{
		haveBom--;
		bomb.f = true;
		isSA = true;
		bomb.cnt.start();
		bomb.r = BOMB_BOX;
	}
	if (KeyZ.pressed() && shotTime > 3)
	{
		bul[BulSearch()].Active(Vec2(pos.x-16, pos.y - 64), 0, 32, U"playerBul", 0);
		bul[BulSearch()].Active(Vec2(pos.x+16, pos.y - 64), 0, 32, U"playerBul", 0);
		shotTime = 0;
	}else shotTime++;

	return false;
}

int _player::BulSearch()
{
	for (auto i : step(PLAYER_SHOT_MAX))
		if (!bul[i].f)
			return i;
}

void _player::Draw()
{
	//Player
	ColorF c = ((isDraw) ? AlphaF(1) : ColorF(0));
	if (bomb.f) {
		Circle(pos, bomb.r).draw(ColorF(0.2, 0.3, 0.8));
		TextureAsset(U"player{}"_fmt(anm / 6)).drawAt(beforePos, ColorF(0.15, 0.5));
	}
	TextureAsset(U"player{}"_fmt(anm / 6)).drawAt(pos, c);
	Circle(pos, PLAYER_BOX+2).draw(Palette::Red);
	//Option
	TextureAsset(U"playerOpt").drawAt(Vec2(pos.x - 16, pos.y - 30));
	TextureAsset(U"playerOpt").drawAt(Vec2(pos.x + 16, pos.y - 30));
	for (auto i : step(PLAYER_SHOT_MAX))
	{
		if (bul[i].f)
			TextureAsset(bul[i].name).drawAt(bul[i].pos);
	}
}