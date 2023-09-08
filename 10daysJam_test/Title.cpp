#include "Title.h"

void Title::Initialize()
{
	title_ = Novice::LoadTexture("./Resource/images/title.png");
	start_ = Novice::LoadTexture("./Resource/images/start.png");
}

void Title::Update()
{
	Novice::GetMousePosition(&mousePosX_, &mousePosY_);

	// クリックスタートボックスのマウスとの判定
	if (mousePosX_ >= selectStartX_ && mousePosX_ <= selectStartX_ + selectStartW_ && mousePosY_ >= selectStartY_ && mousePosY_ <= selectStartY_ + selectStartH_)
	{
		selectStartColor_ = RED;
	}
	else
	{
		selectStartColor_ = WHITE;
	}

	if (selectStartColor_ == RED && Novice::IsPressMouse(0))
	{
		isStart_ = true;
	}

}

void Title::Draw()
{
	Novice::DrawSprite(0, 0, title_, 1.f, 1.f, 0.f, WHITE);

	Novice::DrawSprite(selectStartX_, selectStartY_, start_, 1.f, 1.f, 0.f, selectStartColor_);
}