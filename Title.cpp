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
	title(U"�e��STG�i���̖��m��j").draw(Arg::topCenter(300, 50));
	FontAsset(U"main")(U"Press Space to Start").drawAt(300, 700, AlphaF(1.0 * Periodic::Jump0_1(3s)));
}