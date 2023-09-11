#include <Novice.h>

#pragma once
class GameManager
{
public:

	void Initialize();

	void Update(int stageNo, char keys[256]);

	void Draw(int stageNo);

private:

	struct Vector2 {
		float x;
		float y;
	};

	int Size = 64;	// ブロックサイズ

	// ステージ
	int stageNumber = 0;
	enum stageNumber {
		STAGE0,
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		STAGE5,
		STAGE6,
		STAGE7 //追加分
	};

	// マップ初期値
	int mapCountX = 0, mapCountY = 0;

	//int move = 0;	// プレイヤーの向き 0右 1左

	int map0[12][15] = {
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 1
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 2
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 3
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 4
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 5
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 6
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 7
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 8
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 9
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	int initializeMap0[12][15] = {
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 1
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 2
	  {2,0,0,0,0,0,2,8,2,0,0,0,0,0,2},  // 3
	  {2,0,0,0,0,0,2,2,2,0,0,0,0,0,2},  // 4
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 5
	  {2,0,2,2,2,0,0,0,0,0,2,2,2,0,2},  // 6
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 7
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 8
	  {2,0,0,0,0,0,2,0,2,0,0,0,0,0,2},  // 9
	  {2,0,0,0,0,0,0,1,0,0,0,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	int map1[12][15] = {
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,8,0,0,2,0,0,0,0,0,0,0,0,6,2},  // 1
	  {2,0,0,6,0,5,2,2,2,2,2,0,2,0,2},  // 2
	  {2,0,6,0,2,0,4,0,0,6,0,3,2,0,2},  // 3
	  {2,0,0,6,2,3,0,2,0,0,0,0,2,0,2},  // 4
	  {2,6,0,0,2,0,3,0,8,5,0,0,2,0,2},  // 5
	  {2,0,0,0,2,0,4,0,0,0,0,3,2,0,2},  // 6
	  {2,3,0,0,2,3,0,0,5,0,3,0,2,0,2},  // 7
	  {2,2,2,2,2,2,0,2,2,2,0,2,2,0,2},  // 8
	  {2,4,0,0,0,0,0,0,0,0,0,0,0,5,2},  // 9
	  {2,1,3,2,0,0,0,0,0,0,0,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	int initializeMap1[12][15] = {
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,8,0,0,2,0,0,0,0,0,0,0,0,6,2},  // 1
	  {2,0,0,6,0,5,2,2,2,2,2,0,2,0,2},  // 2
	  {2,0,6,0,2,0,4,0,0,6,0,3,2,0,2},  // 3
	  {2,0,0,6,2,3,0,2,0,0,0,0,2,0,2},  // 4
	  {2,6,0,0,2,0,3,0,0,5,0,0,2,0,2},  // 5
	  {2,0,0,0,2,0,4,0,0,0,0,3,2,0,2},  // 6
	  {2,3,0,0,2,3,0,0,5,0,3,0,2,0,2},  // 7
	  {2,2,2,2,2,2,0,2,2,2,0,2,2,0,2},  // 8
	  {2,4,0,0,0,0,0,0,0,0,0,0,0,5,2},  // 9
	  {2,1,3,2,0,0,0,0,0,0,0,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	int map2[12][15] = {
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 1
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 2
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 3
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 4
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 5
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 6
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 7
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 8
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 9
	  {2,1,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	int initializeMap2[12][15] = {
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 1
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 2
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 3
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 4
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 5
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 6
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 7
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 8
	  {2,0,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 9
	  {2,1,0,0,0,0,0,0,0,0,2,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	enum MapInfo {
		BACK,    // 0 背景
		PLAYER,    // 1 プレイヤー
		WALL,    // 2 壁
		UP,    // 3 上
		RIGHT,    // 4 右
		LEFT,    // 5 左
		DOWN,    // 6 下
		CLEAR,
		ENEMY,
	};

	// マウス
	int mousePosX_ = 0;
	int mousePosY_ = 0;

	// 選択ボックス(仮)
	int selectWX_[4];
	int selectWY_[4];
	int selectWR_[4];
	int selectWColor_[4];

	int backColor_[12][15];

	// 四隅の判定
	int leftTX[4];
	int leftTY[4];
	int leftBX[4];
	int leftBY[4];
	int rightTX[4];
	int rightTY[4];
	int rightBX[4];
	int rightBY[4];
	int saveLeftTX[4];
	int saveLeftTY[4];

	// プレイヤーの弾
	int shotPosX_;//弾のX位置
	int shotPosY_;//弾のY位置
	int shotSpead_;//弾のスピード
	int shotFlag_;//打った判定をとるフラグ
	int shotMove_;//打つ弾の向き
	int collisionFlag_;//判定をとるフラグ
	int setShotFlag_;//打つまでのフラグ

	// プレイヤーの向き
	int savePlayerPosX_;
	int savePlayerPosY_;

	// フラグ
	bool isWall[4];
	int clickFlag_;
	int judgeFlag_ = 0;

	float efectPosX_[20];
	float efectPosY_[20];
	int efectTimer_;
	int efectFlag_[20];
	int saveFlag_;
	int Timer_[20];
	float efectVelocity_[20];
	float efectAcceleration_[20];
	int randSave[20];
	int shakeRandX_ = 0;
	int shakeRandY_ = 0;
	int shakeTimer_ = 0;
	int shakeFlag_ = 0;
	int update_ = 24;
	int enemyColor = 0;
	int a = 0;

	// フラグ
	int back = 0;
	int wall = 0;
	int deadFlag_ = 0;

	int BG = Novice::LoadTexture("./Resource/images/BG.png");

	int player = Novice::LoadTexture("./Resource/images/player.png");
	int enemy = Novice::LoadTexture("./Resource/images/enemy.png");

	int Bullet = Novice::LoadTexture("./Resource/images/Bullet.png");

	int up = Novice::LoadTexture("./Resource/images/up.png");
	int down = Novice::LoadTexture("./Resource/images/down.png");
	int right = Novice::LoadTexture("./Resource/images/right.png");
	int left = Novice::LoadTexture("./Resource/images/left.png");

	int upAllow = Novice::LoadTexture("./Resource/images/AllowUp.png");
	int downAllow = Novice::LoadTexture("./Resource/images/Allowdown.png");
	int rightAllow = Novice::LoadTexture("./Resource/images/AllowRight.png");
	int leftAllow = Novice::LoadTexture("./Resource/images/AllowLeft.png");


	int panel = Novice::LoadTexture("./Resource/images/panel.png");
};

