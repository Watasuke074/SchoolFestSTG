#define GL_SET
#include "Main.h"

void FirstInit();
void Register();

void Main()
{
	FirstInit();
	Register();
	//シーン初期化
	ShootMain shootmain;
	Title title;
	now = 0;
	//メインループ
	Font f(15);
	while (System::Update())
	{
		ClearPrint();
		Print << U"\n\n";
		switch (now)
		{
		case 0:
			title.Update();
			break;
		case 1:
			shootmain.Update();
			break;
		default:
			break;
		}
		f(U"FPS[{}]"_fmt(Profiler::FPS())).draw(Arg::bottomRight(FILED_X,FILED_Y));
	}
}

void Register()
{
	///Font
	FontAsset::Register(U"main", 30);
	FontAsset::Register(U"score", 20);
	FontAsset::Register(U"graze", 45, U"Data/OCRAStd.ttf");

	///Audio
	AudioAsset::Register(U"enemyDead", U"Data/Audio/enemyDead.wav");
	AudioAsset::Register(U"graze", U"Data/Audio/graze.wav");
	AudioAsset::Register(U"playerDead", U"Data/Audio/playerDead.wav");

	///Texture
	//player
	TextureAsset::Register(U"player0", U"Data/pic/player/player0.png");
	TextureAsset::Register(U"player1", U"Data/pic/player/player1.png");
	TextureAsset::Register(U"player2", U"Data/pic/player/player2.png");
	TextureAsset::Register(U"playerOpt", U"Data/pic/player/option.png");
	TextureAsset::Register(U"playerBul", U"Data/pic/player/bullet.png");
	TextureAsset::Register(U"playerBul1", U"Data/pic/player/bullet1.png");
	//enemy
	TextureAsset::Register(U"enemy0_0", U"Data/pic/enemy/enemy0.png");
	TextureAsset::Register(U"enemy0_1", U"Data/pic/enemy/enemy1.png");
	TextureAsset::Register(U"enemy0_2", U"Data/pic/enemy/enemy2.png");
	TextureAsset::Register(U"enemyB_0", U"Data/pic/enemy/enemyB0.png");
	TextureAsset::Register(U"enemyB_1", U"Data/pic/enemy/enemyB1.png");
	TextureAsset::Register(U"enemyB_2", U"Data/pic/enemy/enemyB2.png");
	//Bul
	TextureAsset::Register(U"bul0", U"Data/pic/bul/bul0.png");
}

void FirstInit()
{
	//基本設定
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);
	Graphics::SetTargetFrameRateHz(60);
	Scene::SetBackground(Palette::Black);
	Scene::Resize(FILED_X, FILED_Y);
	Window::Resize(FILED_X, FILED_Y);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Maximize();
}

