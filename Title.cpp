#include "Main.h"

void Title::Init()
{
	title = Font(50);
}
void Title::Update()
{
	if (KeySpace.down())
		now = 1;
	Draw();
}
void Title::Draw()
{
	title(U"�߂�����O���C�Y����\n���n�C�X�s�[�h\n�e��STG�i���j").draw(Arg::topCenter(300, 50));
	FontAsset(U"main")(U"Press Space to Start").drawAt(300, 700, AlphaF(1.0 * Periodic::Jump0_1(3s)));
}