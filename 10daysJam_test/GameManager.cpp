#include "GameManager.h"

void GameManager::Initialize()
{
	shotFlag_ = 0;
	shotPosX_ = 0;
	shotPosY_ = 0;
	shotMove_ = 3;
	shotSpead_ = 8;
	collisionFlag_ = 1;
	setShotFlag_ = 0;

	// ステージ１
	mapCountX = sizeof(map0[0]) / sizeof(map0[0][0]);
	mapCountY = sizeof(map0) / sizeof(map0[0]);

	for (int y = 0; y < mapCountY; y++) {
		for (int x = 0; x < mapCountX; x++) {

			// ステージ１
			map0[y][x] = initializeMap0[y][x];
			// ステージ２
			map1[y][x] = initializeMap1[y][x];
			// ステージ３
			map2[y][x] = initializeMap2[y][x];

			backColor_[y][x] = WHITE;
		}
	}

	for (int i = 0; i < 4; i++) {
		leftTX[i] = 0;
		leftTY[i] = 0;
		leftBX[i] = 0;
		leftBY[i] = 0;
		rightTX[i] = 0;
		rightTY[i] = 0;
		rightBX[i] = 0;
		rightBY[i] = 0;
		selectWX_[i] = 1085;
		selectWY_[0] = 165;
		selectWY_[1] = 330;
		selectWY_[2] = 485;
		selectWY_[3] = 650;
		selectWR_[i] = 64;
		selectWColor_[i] = 0;
		saveLeftTX[i] = 0;
		saveLeftTY[i] = 0;
		isWall[i] = 0;
		clickFlag_ = 0;
	}

	// テクスチャ
	back = Novice::LoadTexture("./Resource/images/floor.png");                      //背景
	wall = Novice::LoadTexture("./Resource/images/metaru.png");                     //壁

}

void GameManager::Update(int stageNo, char keys[256])
{

	Novice::GetMousePosition(&mousePosX_, &mousePosY_);

	int leftTopX_ = (shotPosX_) / Size;
	int leftBottomX_ = (shotPosX_) / Size;

	int rightTopX_ = (shotPosX_ + Size) / Size;
	int rightBottomX_ = (shotPosX_ + Size) / Size;

	int leftBottomY_ = (shotPosY_ + Size) / Size;
	int rightBottomY_ = (shotPosY_ + Size) / Size;

	int rightTopY_ = (shotPosY_) / Size;
	int leftTopY_ = (shotPosY_) / Size;

	for (int i = 0; i < 4; i++) {
		// 四隅の判定
		leftTX[i] = selectWX_[i] / Size;
		leftTY[i] = selectWY_[i] / Size;
		leftBX[i] = selectWX_[i] / Size;
		leftBY[i] = (selectWY_[i] + selectWR_[i] - 1) / Size;
		rightTX[i] = (selectWX_[i] + selectWR_[i] - 1) / Size;
		rightTY[i] = selectWY_[i] / Size;
		rightBX[i] = (selectWX_[i] + selectWR_[i] - 1) / Size;
		rightBY[i] = (selectWY_[i] + selectWR_[i] - 1) / Size;
	}
	//左ブロック
	if (mousePosX_ >= selectWX_[0] && mousePosX_ <= selectWX_[0] + selectWR_[0] &&
		mousePosY_ >= selectWY_[0] && mousePosY_ <= selectWY_[0] + selectWR_[0] && !isWall[0])
	{
		selectWColor_[0] = RED;
	}
	else
	{
		selectWColor_[0] = WHITE;
	}
	if (clickFlag_ == 0) {
		if (selectWColor_[0] == RED && Novice::IsPressMouse(0))
		{
			isWall[0] = true;
			clickFlag_ = 1;
		}
	}
	if (isWall[0])
	{
		selectWX_[0] = mousePosX_;
		selectWY_[0] = mousePosY_;
	}

	// ステージ1
	if (stageNo == STAGE1)
	{
		// プレイヤー操作
		for (int y = 0; y < mapCountY; y++) {
			for (int x = 0; x < mapCountX; x++) {
				if (map0[y][x] == PLAYER) {
					if (shotFlag_ == 0) {

						shotPosX_ = x * Size;
						shotPosY_ = y * Size;
					}
				}
				//壁の判定

				//左
				if (shotMove_ == 1) {
					if (collisionFlag_ == 1) {
						if (map0[leftTopY_][leftTopX_] == WALL) {
							if (map0[rightTopY_][rightTopX_] == BACK || map0[rightTopY_][rightTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map0[rightBottomY_][rightBottomX_] == LEFT) {
								setShotFlag_ = 1;
							}
						}
						if (map0[leftTopY_][leftTopX_] == UP || map0[rightBottomY_][rightBottomX_] == DOWN ||
							map0[leftBottomY_][leftBottomX_] == RIGHT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map0[leftTopY_][leftTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;

					}
				}

				//右
				if (shotMove_ == 2) {
					if (collisionFlag_ == 1) {
						if (map0[rightTopY_][rightTopX_] == WALL) {
							if (map0[leftTopY_][leftTopX_] == BACK || map0[leftTopY_][leftTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map0[leftBottomY_][leftBottomX_] == RIGHT) {
								setShotFlag_ = 1;
							}
						}
						if (map0[leftTopY_][leftTopX_] == UP || map0[leftTopY_][leftTopX_] == DOWN ||
							map0[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map0[rightTopY_][rightTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;
					}

				}

				//上
				if (shotMove_ == 3) {

					if (collisionFlag_ == 1) {
						if (map0[leftTopY_][leftTopX_] == WALL) {
							if (map0[leftBottomY_][leftBottomX_] == BACK || map0[leftBottomY_][leftBottomX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map0[leftBottomY_][leftBottomX_] == UP) {
								setShotFlag_ = 1;
							}
						}
						if (map0[leftTopY_][leftTopX_] == DOWN ||
							map0[leftTopY_][leftTopX_] == RIGHT || map0[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}

					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map0[leftTopY_][leftTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;
					}

				}

				//下
				if (shotMove_ == 4) {


					if (collisionFlag_ == 1) {
						if (map0[leftBottomY_][leftBottomX_] == WALL) {
							if (map0[leftTopY_][leftTopX_] == BACK || map0[leftTopY_][leftTopX_] == PLAYER || map0[rightTopY_][rightTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map0[leftTopY_][leftTopX_] == DOWN) {
								setShotFlag_ = 1;
							}
						}

						if (map0[leftTopY_][leftTopX_] == UP ||
							map0[leftTopY_][leftTopX_] == RIGHT || map0[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map0[leftBottomY_][leftBottomX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;

					}

				}


				//スライド
				if (shotMove_ == 1) {
					if (map0[leftTopY_][leftTopX_ + 1] == UP) {
						shotMove_ = 3;
						shotPosX_ = (leftTopX_ + 1) * Size;
					}

					if (map0[leftTopY_][leftTopX_ + 1] == RIGHT) {
						shotMove_ = 2;
					}

					if (map0[leftTopY_][leftTopX_ + 1] == LEFT) {
						shotMove_ = 1;
					}

					if (map0[leftTopY_][leftTopX_ + 1] == DOWN) {
						shotMove_ = 4;
						shotPosX_ = (leftTopX_ + 1) * Size;
					}
				}

				if (shotMove_ == 2) {
					if (map0[leftTopY_][leftTopX_] == UP) {
						shotMove_ = 3;
					}

					if (map0[leftTopY_][leftTopX_] == RIGHT) {
						shotMove_ = 2;
					}

					if (map0[leftTopY_][leftTopX_] == LEFT) {
						shotMove_ = 1;
					}

					if (map0[leftTopY_][leftTopX_] == DOWN) {
						shotMove_ = 4;
					}
				}

				if (shotMove_ == 3) {
					if (map0[leftTopY_ + 1][leftTopX_] == UP) {
						shotMove_ = 3;
					}

					if (map0[leftTopY_ + 1][leftTopX_] == RIGHT) {
						shotMove_ = 2;
						shotPosY_ = (leftTopY_ + 1) * Size;
					}

					if (map0[leftTopY_ + 1][leftTopX_] == LEFT) {
						shotMove_ = 1;
						shotPosY_ = (leftTopY_ + 1) * Size;
					}

					if (map0[leftTopY_ + 1][leftTopX_] == DOWN) {
						shotMove_ = 4;
					}
				}

				if (shotMove_ == 4) {

					if (map0[leftTopY_][leftTopX_] == UP) {

						shotMove_ = 3;

					}

					if (map0[leftTopY_][leftTopX_] == RIGHT) {

						shotMove_ = 2;

					}

					if (map0[leftTopY_][leftTopX_] == LEFT) {

						shotMove_ = 1;

					}
					if (map0[leftTopY_ + 1][leftTopX_] == DOWN) {

						shotMove_ = 4;

					}
				}

			}
		}

		// マップとブロックの配置判定
		if (map0[leftTY[0]][leftTX[0]] == BACK && isWall[0] && selectWX_[0] <= 960)
		{
			backColor_[saveLeftTY[0]][saveLeftTX[0]] = WHITE;
			backColor_[leftTY[0]][leftTX[0]] = RED;
			saveLeftTX[0] = leftTX[0];
			saveLeftTY[0] = leftTY[0];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[0]][leftTX[0]] == RED)
		{
			map0[leftTY[0]][leftTX[0]] = LEFT;
			isWall[0] = false;
			clickFlag_ = 0;
			selectWX_[0] = 1085;
			selectWY_[0] = 165;
		}

		//右ブロック
		if (mousePosX_ >= selectWX_[1] && mousePosX_ <= selectWX_[1] + selectWR_[1] &&
			mousePosY_ >= selectWY_[1] && mousePosY_ <= selectWY_[1] + selectWR_[1] && !isWall[1])
		{
			selectWColor_[1] = RED;
		}
		else
		{
			selectWColor_[1] = WHITE;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[1] == RED && Novice::IsPressMouse(0))
			{
				isWall[1] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[1])
		{
			selectWX_[1] = mousePosX_;
			selectWY_[1] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map0[leftTY[1]][leftTX[1]] == BACK && isWall[1] && selectWX_[1] <= 960)
		{
			backColor_[saveLeftTY[1]][saveLeftTX[1]] = WHITE;
			backColor_[leftTY[1]][leftTX[1]] = RED;
			saveLeftTX[1] = leftTX[1];
			saveLeftTY[1] = leftTY[1];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[1]][leftTX[1]] == RED)
		{
			map0[leftTY[1]][leftTX[1]] = RIGHT;
			isWall[1] = false;
			clickFlag_ = 0;
			selectWX_[1] = 1085;
			selectWY_[1] = 330;
		}


		//下ブロック
		if (mousePosX_ >= selectWX_[2] && mousePosX_ <= selectWX_[2] + selectWR_[2] &&
			mousePosY_ >= selectWY_[2] && mousePosY_ <= selectWY_[2] + selectWR_[2] && !isWall[2])
		{
			selectWColor_[2] = RED;
		}
		else
		{
			selectWColor_[2] = WHITE;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[2] == RED && Novice::IsPressMouse(0))
			{
				isWall[2] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[2])
		{
			selectWX_[2] = mousePosX_;
			selectWY_[2] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map0[leftTY[2]][leftTX[2]] == BACK && isWall[2] && selectWX_[2] <= 960)
		{
			backColor_[saveLeftTY[2]][saveLeftTX[2]] = WHITE;
			backColor_[leftTY[2]][leftTX[2]] = RED;
			saveLeftTX[2] = leftTX[2];
			saveLeftTY[2] = leftTY[2];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[2]][leftTX[2]] == RED)
		{
			map0[leftTY[2]][leftTX[2]] = DOWN;
			isWall[2] = false;
			clickFlag_ = 0;
			selectWX_[2] = 1085;
			selectWY_[2] = 485;
		}

		//上ブロック
		if (mousePosX_ >= selectWX_[3] && mousePosX_ <= selectWX_[3] + selectWR_[3] &&
			mousePosY_ >= selectWY_[3] && mousePosY_ <= selectWY_[3] + selectWR_[3] && !isWall[3])
		{
			selectWColor_[3] = RED;
		}
		else
		{
			selectWColor_[3] = WHITE;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[3] == RED && Novice::IsPressMouse(0))
			{
				isWall[3] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[3])
		{
			selectWX_[3] = mousePosX_;
			selectWY_[3] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map0[leftTY[3]][leftTX[3]] == BACK && isWall[3] && selectWX_[3] <= 960)
		{
			backColor_[saveLeftTY[3]][saveLeftTX[3]] = WHITE;
			backColor_[leftTY[3]][leftTX[3]] = RED;
			saveLeftTX[3] = leftTX[3];
			saveLeftTY[3] = leftTY[3];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[3]][leftTX[3]] == RED)
		{
			map0[leftTY[3]][leftTX[3]] = UP;
			isWall[3] = false;
			clickFlag_ = 0;
			selectWX_[3] = 1085;
			selectWY_[3] = 650;
		}
	}

	// ステージ2
	if (stageNo == STAGE2)
	{
		// プレイヤー操作
		for (int y = 0; y < mapCountY; y++) {
			for (int x = 0; x < mapCountX; x++) {
				if (map1[y][x] == PLAYER) {
					if (shotFlag_ == 0) {

						shotPosX_ = x * Size;
						shotPosY_ = y * Size;
					}
				}
				//壁の判定

				//左
				if (shotMove_ == 1) {
					if (collisionFlag_ == 1) {
						if (map1[leftTopY_][leftTopX_] == WALL) {
							if (map1[rightTopY_][rightTopX_] == BACK || map0[rightTopY_][rightTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map1[rightBottomY_][rightBottomX_] == LEFT) {
								setShotFlag_ = 1;
							}
						}
						if (map1[leftTopY_][leftTopX_] == UP || map1[rightBottomY_][rightBottomX_] == DOWN ||
							map1[leftBottomY_][leftBottomX_] == RIGHT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map1[leftTopY_][leftTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;

					}
				}

				//右
				if (shotMove_ == 2) {
					if (collisionFlag_ == 1) {
						if (map1[rightTopY_][rightTopX_] == WALL) {
							if (map1[leftTopY_][leftTopX_] == BACK || map1[leftTopY_][leftTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map1[leftBottomY_][leftBottomX_] == RIGHT) {
								setShotFlag_ = 1;
							}
						}
						if (map1[leftTopY_][leftTopX_] == UP || map1[leftTopY_][leftTopX_] == DOWN ||
							map1[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map1[rightTopY_][rightTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;
					}

				}

				//上
				if (shotMove_ == 3) {

					if (collisionFlag_ == 1) {
						if (map1[leftTopY_][leftTopX_] == WALL) {
							if (map1[leftBottomY_][leftBottomX_] == BACK || map1[leftBottomY_][leftBottomX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map1[leftBottomY_][leftBottomX_] == UP) {
								setShotFlag_ = 1;
							}
						}
						if (map1[leftTopY_][leftTopX_] == DOWN ||
							map1[leftTopY_][leftTopX_] == RIGHT || map1[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}

					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map1[leftTopY_][leftTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;
					}

				}

				//下
				if (shotMove_ == 4) {


					if (collisionFlag_ == 1) {
						if (map1[leftBottomY_][leftBottomX_] == WALL) {
							if (map1[leftTopY_][leftTopX_] == BACK || map1[leftTopY_][leftTopX_] == PLAYER || map1[rightTopY_][rightTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map1[leftTopY_][leftTopX_] == DOWN) {
								setShotFlag_ = 1;
							}
						}

						if (map1[leftTopY_][leftTopX_] == UP ||
							map1[leftTopY_][leftTopX_] == RIGHT || map1[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map1[leftBottomY_][leftBottomX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;

					}

				}


				//スライド
				if (shotMove_ == 1) {
					if (map1[leftTopY_][leftTopX_ + 1] == UP) {
						shotMove_ = 3;
						shotPosX_ = (leftTopX_ + 1) * Size;
					}

					if (map1[leftTopY_][leftTopX_ + 1] == RIGHT) {
						shotMove_ = 2;
					}

					if (map1[leftTopY_][leftTopX_ + 1] == LEFT) {
						shotMove_ = 1;
					}

					if (map1[leftTopY_][leftTopX_ + 1] == DOWN) {
						shotMove_ = 4;
						shotPosX_ = (leftTopX_ + 1) * Size;
					}
				}

				if (shotMove_ == 2) {
					if (map1[leftTopY_][leftTopX_] == UP) {
						shotMove_ = 3;
					}

					if (map1[leftTopY_][leftTopX_] == RIGHT) {
						shotMove_ = 2;
					}

					if (map1[leftTopY_][leftTopX_] == LEFT) {
						shotMove_ = 1;
					}

					if (map1[leftTopY_][leftTopX_] == DOWN) {
						shotMove_ = 4;
					}
				}

				if (shotMove_ == 3) {
					if (map1[leftTopY_ + 1][leftTopX_] == UP) {
						shotMove_ = 3;
					}

					if (map1[leftTopY_ + 1][leftTopX_] == RIGHT) {
						shotMove_ = 2;
						shotPosY_ = (leftTopY_ + 1) * Size;
					}

					if (map1[leftTopY_ + 1][leftTopX_] == LEFT) {
						shotMove_ = 1;
						shotPosY_ = (leftTopY_ + 1) * Size;
					}

					if (map1[leftTopY_ + 1][leftTopX_] == DOWN) {
						shotMove_ = 4;
					}
				}

				if (shotMove_ == 4) {

					if (map1[leftTopY_][leftTopX_] == UP) {

						shotMove_ = 3;

					}

					if (map1[leftTopY_][leftTopX_] == RIGHT) {

						shotMove_ = 2;

					}

					if (map1[leftTopY_][leftTopX_] == LEFT) {

						shotMove_ = 1;

					}
					if (map1[leftTopY_ + 1][leftTopX_] == DOWN) {

						shotMove_ = 4;

					}
				}

			}
		}

		// マップとブロックの配置判定
		if (map1[leftTY[0]][leftTX[0]] == BACK && isWall[0] && selectWX_[0] <= 960)
		{
			backColor_[saveLeftTY[0]][saveLeftTX[0]] = WHITE;
			backColor_[leftTY[0]][leftTX[0]] = RED;
			saveLeftTX[0] = leftTX[0];
			saveLeftTY[0] = leftTY[0];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[0]][leftTX[0]] == RED)
		{
			map1[leftTY[0]][leftTX[0]] = LEFT;
			isWall[0] = false;
			clickFlag_ = 0;
			selectWX_[0] = 1085;
			selectWY_[0] = 165;
		}

		//右ブロック
		if (mousePosX_ >= selectWX_[1] && mousePosX_ <= selectWX_[1] + selectWR_[1] &&
			mousePosY_ >= selectWY_[1] && mousePosY_ <= selectWY_[1] + selectWR_[1] && !isWall[1])
		{
			selectWColor_[1] = RED;
		}
		else
		{
			selectWColor_[1] = 0xFF00FFFF;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[1] == RED && Novice::IsPressMouse(0))
			{
				isWall[1] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[1])
		{
			selectWX_[1] = mousePosX_;
			selectWY_[1] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map0[leftTY[1]][leftTX[1]] == BACK && isWall[1] && selectWX_[1] <= 960)
		{
			backColor_[saveLeftTY[1]][saveLeftTX[1]] = WHITE;
			backColor_[leftTY[1]][leftTX[1]] = RED;
			saveLeftTX[1] = leftTX[1];
			saveLeftTY[1] = leftTY[1];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[1]][leftTX[1]] == RED)
		{
			map0[leftTY[1]][leftTX[1]] = RIGHT;
			isWall[1] = false;
			clickFlag_ = 0;
			selectWX_[1] = 1085;
			selectWY_[1] = 330;
		}


		//下ブロック
		if (mousePosX_ >= selectWX_[2] && mousePosX_ <= selectWX_[2] + selectWR_[2] &&
			mousePosY_ >= selectWY_[2] && mousePosY_ <= selectWY_[2] + selectWR_[2] && !isWall[2])
		{
			selectWColor_[2] = RED;
		}
		else
		{
			selectWColor_[2] = 0xCC00FFFF;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[2] == RED && Novice::IsPressMouse(0))
			{
				isWall[2] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[2])
		{
			selectWX_[2] = mousePosX_;
			selectWY_[2] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map1[leftTY[2]][leftTX[2]] == BACK && isWall[2] && selectWX_[2] <= 960)
		{
			backColor_[saveLeftTY[2]][saveLeftTX[2]] = WHITE;
			backColor_[leftTY[2]][leftTX[2]] = RED;
			saveLeftTX[2] = leftTX[2];
			saveLeftTY[2] = leftTY[2];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[2]][leftTX[2]] == RED)
		{
			map1[leftTY[2]][leftTX[2]] = DOWN;
			isWall[2] = false;
			clickFlag_ = 0;
			selectWX_[2] = 1085;
			selectWY_[2] = 485;
		}

		//上ブロック
		if (mousePosX_ >= selectWX_[3] && mousePosX_ <= selectWX_[3] + selectWR_[3] &&
			mousePosY_ >= selectWY_[3] && mousePosY_ <= selectWY_[3] + selectWR_[3] && !isWall[3])
		{
			selectWColor_[3] = RED;
		}
		else
		{
			selectWColor_[3] = BLUE;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[3] == RED && Novice::IsPressMouse(0))
			{
				isWall[3] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[3])
		{
			selectWX_[3] = mousePosX_;
			selectWY_[3] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map1[leftTY[3]][leftTX[3]] == BACK && isWall[3] && selectWX_[3] <= 960)
		{
			backColor_[saveLeftTY[3]][saveLeftTX[3]] = WHITE;
			backColor_[leftTY[3]][leftTX[3]] = RED;
			saveLeftTX[3] = leftTX[3];
			saveLeftTY[3] = leftTY[3];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[3]][leftTX[3]] == RED)
		{
			map1[leftTY[3]][leftTX[3]] = UP;
			isWall[3] = false;
			clickFlag_ = 0;
			selectWX_[3] = 1085;
			selectWY_[3] = 650;
		}
	}

	// ステージ3
	if (stageNo == STAGE3)
	{
		// プレイヤー操作
		for (int y = 0; y < mapCountY; y++) {
			for (int x = 0; x < mapCountX; x++) {
				if (map2[y][x] == PLAYER) {
					if (shotFlag_ == 0) {

						shotPosX_ = x * Size;
						shotPosY_ = y * Size;
					}
				}
				//壁の判定

				//左
				if (shotMove_ == 1) {
					if (collisionFlag_ == 1) {
						if (map2[leftTopY_][leftTopX_] == WALL) {
							if (map2[rightTopY_][rightTopX_] == BACK || map0[rightTopY_][rightTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map2[rightBottomY_][rightBottomX_] == LEFT) {
								setShotFlag_ = 1;
							}
						}
						if (map2[leftTopY_][leftTopX_] == UP || map2[rightBottomY_][rightBottomX_] == DOWN ||
							map2[leftBottomY_][leftBottomX_] == RIGHT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map2[leftTopY_][leftTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;

					}
				}

				//右
				if (shotMove_ == 2) {
					if (collisionFlag_ == 1) {
						if (map2[rightTopY_][rightTopX_] == WALL) {
							if (map2[leftTopY_][leftTopX_] == BACK || map2[leftTopY_][leftTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map2[leftBottomY_][leftBottomX_] == RIGHT) {
								setShotFlag_ = 1;
							}
						}
						if (map2[leftTopY_][leftTopX_] == UP || map2[leftTopY_][leftTopX_] == DOWN ||
							map2[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map2[rightTopY_][rightTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;
					}

				}

				//上
				if (shotMove_ == 3) {

					if (collisionFlag_ == 1) {
						if (map2[leftTopY_][leftTopX_] == WALL) {
							if (map2[leftBottomY_][leftBottomX_] == BACK || map2[leftBottomY_][leftBottomX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map2[leftBottomY_][leftBottomX_] == UP) {
								setShotFlag_ = 1;
							}
						}
						if (map2[leftTopY_][leftTopX_] == DOWN ||
							map2[leftTopY_][leftTopX_] == RIGHT || map2[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}

					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map2[leftTopY_][leftTopX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;
					}

				}

				//下
				if (shotMove_ == 4) {


					if (collisionFlag_ == 1) {
						if (map2[leftBottomY_][leftBottomX_] == WALL) {
							if (map2[leftTopY_][leftTopX_] == BACK || map2[leftTopY_][leftTopX_] == PLAYER || map2[rightTopY_][rightTopX_] == PLAYER) {
								setShotFlag_ = 1;
							}
							if (map2[leftTopY_][leftTopX_] == DOWN) {
								setShotFlag_ = 1;
							}
						}

						if (map2[leftTopY_][leftTopX_] == UP ||
							map2[leftTopY_][leftTopX_] == RIGHT || map2[leftTopY_][leftTopX_] == LEFT) {
							setShotFlag_ = 2;
						}
					}

					if (setShotFlag_ == 1) {
						shotFlag_ = 0;
						setShotFlag_ = 0;
					}
					if (setShotFlag_ == 2) {
						setShotFlag_ = 0;
					}

					if (map2[leftBottomY_][leftBottomX_] == WALL) {
						collisionFlag_ = 1;
					}
					else {
						collisionFlag_ = 0;

					}

				}


				//スライド
				if (shotMove_ == 1) {
					if (map2[leftTopY_][leftTopX_ + 1] == UP) {
						shotMove_ = 3;
						shotPosX_ = (leftTopX_ + 1) * Size;
					}

					if (map2[leftTopY_][leftTopX_ + 1] == RIGHT) {
						shotMove_ = 2;
					}

					if (map2[leftTopY_][leftTopX_ + 1] == LEFT) {
						shotMove_ = 1;
					}

					if (map2[leftTopY_][leftTopX_ + 1] == DOWN) {
						shotMove_ = 4;
						shotPosX_ = (leftTopX_ + 1) * Size;
					}
				}

				if (shotMove_ == 2) {
					if (map2[leftTopY_][leftTopX_] == UP) {
						shotMove_ = 3;
					}

					if (map2[leftTopY_][leftTopX_] == RIGHT) {
						shotMove_ = 2;
					}

					if (map2[leftTopY_][leftTopX_] == LEFT) {
						shotMove_ = 1;
					}

					if (map2[leftTopY_][leftTopX_] == DOWN) {
						shotMove_ = 4;
					}
				}

				if (shotMove_ == 3) {
					if (map2[leftTopY_ + 1][leftTopX_] == UP) {
						shotMove_ = 3;
					}

					if (map2[leftTopY_ + 1][leftTopX_] == RIGHT) {
						shotMove_ = 2;
						shotPosY_ = (leftTopY_ + 1) * Size;
					}

					if (map2[leftTopY_ + 1][leftTopX_] == LEFT) {
						shotMove_ = 1;
						shotPosY_ = (leftTopY_ + 1) * Size;
					}

					if (map2[leftTopY_ + 1][leftTopX_] == DOWN) {
						shotMove_ = 4;
					}
				}

				if (shotMove_ == 4) {

					if (map2[leftTopY_][leftTopX_] == UP) {

						shotMove_ = 3;

					}

					if (map2[leftTopY_][leftTopX_] == RIGHT) {

						shotMove_ = 2;

					}

					if (map2[leftTopY_][leftTopX_] == LEFT) {

						shotMove_ = 1;

					}
					if (map2[leftTopY_ + 1][leftTopX_] == DOWN) {

						shotMove_ = 4;

					}
				}

			}
		}

		// マップとブロックの配置判定
		if (map2[leftTY[0]][leftTX[0]] == BACK && isWall[0] && selectWX_[0] <= 960)
		{
			backColor_[saveLeftTY[0]][saveLeftTX[0]] = WHITE;
			backColor_[leftTY[0]][leftTX[0]] = RED;
			saveLeftTX[0] = leftTX[0];
			saveLeftTY[0] = leftTY[0];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[0]][leftTX[0]] == RED)
		{
			map2[leftTY[0]][leftTX[0]] = LEFT;
			isWall[0] = false;
			clickFlag_ = 0;
			selectWX_[0] = 1085;
			selectWY_[0] = 165;
		}

		//右ブロック
		if (mousePosX_ >= selectWX_[1] && mousePosX_ <= selectWX_[1] + selectWR_[1] &&
			mousePosY_ >= selectWY_[1] && mousePosY_ <= selectWY_[1] + selectWR_[1] && !isWall[1])
		{
			selectWColor_[1] = RED;
		}
		else
		{
			selectWColor_[1] = 0xFF00FFFF;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[1] == RED && Novice::IsPressMouse(0))
			{
				isWall[1] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[1])
		{
			selectWX_[1] = mousePosX_;
			selectWY_[1] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map2[leftTY[1]][leftTX[1]] == BACK && isWall[1] && selectWX_[1] <= 960)
		{
			backColor_[saveLeftTY[1]][saveLeftTX[1]] = WHITE;
			backColor_[leftTY[1]][leftTX[1]] = RED;
			saveLeftTX[1] = leftTX[1];
			saveLeftTY[1] = leftTY[1];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[1]][leftTX[1]] == RED)
		{
			map2[leftTY[1]][leftTX[1]] = RIGHT;
			isWall[1] = false;
			clickFlag_ = 0;
			selectWX_[1] = 1085;
			selectWY_[1] = 330;
		}


		//下ブロック
		if (mousePosX_ >= selectWX_[2] && mousePosX_ <= selectWX_[2] + selectWR_[2] &&
			mousePosY_ >= selectWY_[2] && mousePosY_ <= selectWY_[2] + selectWR_[2] && !isWall[2])
		{
			selectWColor_[2] = RED;
		}
		else
		{
			selectWColor_[2] = 0xCC00FFFF;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[2] == RED && Novice::IsPressMouse(0))
			{
				isWall[2] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[2])
		{
			selectWX_[2] = mousePosX_;
			selectWY_[2] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map2[leftTY[2]][leftTX[2]] == BACK && isWall[2] && selectWX_[2] <= 960)
		{
			backColor_[saveLeftTY[2]][saveLeftTX[2]] = WHITE;
			backColor_[leftTY[2]][leftTX[2]] = RED;
			saveLeftTX[2] = leftTX[2];
			saveLeftTY[2] = leftTY[2];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[2]][leftTX[2]] == RED)
		{
			map2[leftTY[2]][leftTX[2]] = DOWN;
			isWall[2] = false;
			clickFlag_ = 0;
			selectWX_[2] = 1085;
			selectWY_[2] = 485;
		}

		//上ブロック
		if (mousePosX_ >= selectWX_[3] && mousePosX_ <= selectWX_[3] + selectWR_[3] &&
			mousePosY_ >= selectWY_[3] && mousePosY_ <= selectWY_[3] + selectWR_[3] && !isWall[3])
		{
			selectWColor_[3] = RED;
		}
		else
		{
			selectWColor_[3] = BLUE;
		}
		if (clickFlag_ == 0) {
			if (selectWColor_[3] == RED && Novice::IsPressMouse(0))
			{
				isWall[3] = true;
				clickFlag_ = 1;
			}
		}
		if (isWall[3])
		{
			selectWX_[3] = mousePosX_;
			selectWY_[3] = mousePosY_;
		}
		// マップとブロックの配置判定
		if (map2[leftTY[3]][leftTX[3]] == BACK && isWall[3] && selectWX_[3] <= 960)
		{
			backColor_[saveLeftTY[3]][saveLeftTX[3]] = WHITE;
			backColor_[leftTY[3]][leftTX[3]] = RED;
			saveLeftTX[3] = leftTX[3];
			saveLeftTY[3] = leftTY[3];
		}

		if (Novice::IsPressMouse(1) && backColor_[leftTY[3]][leftTX[3]] == RED)
		{
			map2[leftTY[3]][leftTX[3]] = UP;
			isWall[3] = false;
			clickFlag_ = 0;
			selectWX_[3] = 1085;
			selectWY_[3] = 650;
		}
	}

	// 弾操作
	if (keys[DIK_SPACE]) {
		shotFlag_ = 1;
	}

	if (shotFlag_ == 1 && shotMove_ == 1) {
		shotPosX_ -= shotSpead_;
	}
	if (shotFlag_ == 1 && shotMove_ == 2) {
		shotPosX_ += shotSpead_;
	}
	if (shotFlag_ == 1 && shotMove_ == 3) {
		shotPosY_ -= shotSpead_;
	}
	if (shotFlag_ == 1 && shotMove_ == 4) {
		shotPosY_ += shotSpead_;

	}

	if (shotFlag_ == 0) {

		if (keys[DIK_LEFT]) {
			shotMove_ = 1;
		}
		if (keys[DIK_RIGHT]) {
			shotMove_ = 2;
		}
		if (keys[DIK_UP]) {
			shotMove_ = 3;
		}
		if (keys[DIK_DOWN]) {
			shotMove_ = 4;
		}
	}

	if (Novice::IsPressMouse(1) && isWall[0])
	{
		isWall[0] = false;
		backColor_[saveLeftTY[0]][saveLeftTX[0]] = WHITE;
		saveLeftTX[0] = leftTX[0];
		saveLeftTY[0] = leftTY[0];
		clickFlag_ = 0;
		selectWX_[0] = 1085;
		selectWY_[0] = 165;
	}

	if (Novice::IsPressMouse(1) && isWall[1])
	{
		isWall[1] = false;
		backColor_[saveLeftTY[1]][saveLeftTX[1]] = WHITE;
		saveLeftTX[1] = leftTX[1];
		saveLeftTY[1] = leftTY[1];
		clickFlag_ = 0;
		selectWX_[1] = 1085;
		selectWY_[1] = 330;
	}

	if (Novice::IsPressMouse(1) && isWall[2])
	{
		isWall[2] = false;
		backColor_[saveLeftTY[2]][saveLeftTX[2]] = WHITE;
		saveLeftTX[2] = leftTX[2];
		saveLeftTY[2] = leftTY[2];
		clickFlag_ = 0;
		selectWX_[2] = 1085;
		selectWY_[2] = 485;
	}

	if (Novice::IsPressMouse(1) && isWall[3])
	{
		isWall[3] = false;
		backColor_[saveLeftTY[3]][saveLeftTX[3]] = WHITE;
		saveLeftTX[3] = leftTX[3];
		saveLeftTY[3] = leftTY[3];
		clickFlag_ = 0;
		selectWX_[3] = 1085;
		selectWY_[3] = 650;
	}
}


void GameManager::Draw(int stageNo)
{
	stageNumber = stageNo;

	for (int y = 0; y < mapCountY; y++) {
		for (int x = 0; x < mapCountX; x++) {

			if (stageNumber == STAGE1) {

				// 背景
				if (map0[y][x] == BACK) {
					Novice::DrawSprite(x * Size, y * Size, back, 1, 1, 0, backColor_[y][x]);
				}

				// 壁
				if (map0[y][x] == WALL) {
					Novice::DrawSprite(x * Size, y * Size, wall, 1, 1, 0, WHITE);
				}

				if (map0[y][x] == PLAYER) {
					Novice::DrawSprite(x * Size, y * Size, player, 2, 2, 0, WHITE);
				}
				// 上
				if (map0[y][x] == UP) {
					Novice::DrawSprite(x * Size, y * Size, up, 2, 2, 0, WHITE);
				}
				// 下
				if (map0[y][x] == DOWN) {
					Novice::DrawSprite(x * Size, y * Size, down, 2, 2, 0, WHITE);
				}
				// 右
				if (map0[y][x] == RIGHT) {
					Novice::DrawSprite(x * Size, y * Size, right, 2, 2, 0, WHITE);
				}
				// 左
				if (map0[y][x] == LEFT) {
					Novice::DrawSprite(x * Size, y * Size, left, 2, 2, 0, WHITE);
				}

				Novice::DrawSprite(960, 0, panel, 1, 1, 0, WHITE);
			}

			if (stageNumber == STAGE2) {

				// 背景
				if (map1[y][x] == BACK) {
					Novice::DrawSprite(x * Size, y * Size, back, 2, 2, 0, backColor_[y][x]);
				}

				// 壁
				if (map1[y][x] == WALL) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, WHITE);
				}

				if (map1[y][x] == PLAYER) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, RED);
				}
				if (map1[y][x] == UP) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, BLUE);
				}
				if (map1[y][x] == RIGHT) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, 0xFF00FFFF);
				}
				if (map1[y][x] == LEFT) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, 0x00FFFFFF);
				}
				if (map1[y][x] == DOWN) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, 0xCC00FFFF);
				}

			}

			if (stageNumber == STAGE3) {

				// 背景
				if (map2[y][x] == BACK) {
					Novice::DrawSprite(x * Size, y * Size, back, 2, 2, 0, backColor_[y][x]);
				}

				// 壁
				if (map2[y][x] == WALL) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, WHITE);
				}

				if (map2[y][x] == PLAYER) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, RED);
				}
				if (map2[y][x] == UP) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, BLUE);
				}
				if (map2[y][x] == RIGHT) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, 0xFF00FFFF);
				}
				if (map2[y][x] == LEFT) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, 0x00FFFFFF);
				}
				if (map2[y][x] == DOWN) {
					Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, 0xCC00FFFF);
				}
			}
		}
	}

	Novice::ScreenPrintf(1000, 0, "map[%d][%d]", leftTY, leftTX);
	Novice::ScreenPrintf(1000, 20, "saveMap[%d][%d]", saveLeftTY, saveLeftTX);

	Novice::ScreenPrintf(1000, 40, "laserMove : %d", shotMove_);
	Novice::ScreenPrintf(1000, 60, "colision : %d", collisionFlag_);
	Novice::ScreenPrintf(1000, 80, "click : %d", clickFlag_);
	Novice::ScreenPrintf(1000, 100, "LEFT,RIGHT,DOWN,UP");

	for (int i = 0; i < 4; i++) {
		Novice::DrawBox(selectWX_[i], selectWY_[i], selectWR_[i], selectWR_[i], 0.f, selectWColor_[i], kFillModeSolid);
	}
	Novice::DrawSprite(selectWX_[0], selectWY_[0], left, 2, 2, 0, selectWColor_[0]);
	Novice::DrawSprite(selectWX_[1], selectWY_[1], right, 2, 2, 0, selectWColor_[1]);
	Novice::DrawSprite(selectWX_[2], selectWY_[2], down, 2, 2, 0, selectWColor_[2]);
	Novice::DrawSprite(selectWX_[3], selectWY_[3], up, 2, 2, 0, selectWColor_[3]);
	if (shotFlag_ == 1) {
		Novice::DrawSprite(shotPosX_, shotPosY_, wall, 1.0f, 1.0f, 0.0f, GREEN);

	}
}