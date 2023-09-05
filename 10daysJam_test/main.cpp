#include <Novice.h>

const char kWindowTitle[] = "GC2A_16_タナカケイスケ";

struct Vector2 {
	float x;
	float y;
};

struct player {
	Vector2 pos;    // 座標
	Vector2 vel;    // 速度
	Vector2 acc;	// 加速度
	Vector2 srcJump;
	Vector2 src;
	int rad;        // 大きさ
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 768);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

	player P{
	   {32,32},
	   {2,2},
	   {0,0},
	   {0,0},
	   {0,0},
	   32
	};

	int color = WHITE;


	// マップ初期値
	int mapCountX = 0, mapCountY = 0;

	//int move = 0;	// プレイヤーの向き 0右 1左

	int map0[12][15] = {                // チュートリアル
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 0
	  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},  // 1
	  {2,0,0,0,0,0,0,0,4,4,4,4,0,0,2},  // 2
	  {2,0,0,0,0,0,0,3,0,0,0,0,3,0,2},  // 3
	  {2,0,0,0,0,2,0,9,0,2,0,0,3,0,2},  // 4
	  {2,0,0,0,0,2,0,0,0,2,0,0,3,0,2},  // 5
	  {2,0,0,0,0,2,2,2,2,2,0,0,3,0,2},  // 6
	  {2,0,0,0,0,0,0,3,0,0,0,0,3,0,2},  // 7
	  {2,4,4,4,4,4,4,5,4,4,4,4,0,0,2},  // 8
	  {2,0,0,0,0,0,0,3,0,0,0,0,3,0,2},  // 9
	  {2,0,0,0,0,0,0,1,0,0,0,0,3,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};

	int map1[12][15] = {                // ステージ１
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
	  {2,0,1,0,0,0,0,0,0,0,0,0,0,0,2},  // 10
	  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},  // 11
	};


	enum MapInfo {
		BACK,	      // 0 背景、マス目
		PLAYER,	      // 1 プレイヤー
		WALL,	      // 2 壁
		VERTICAL,     // 3 縦真っ直ぐ
		SIDE,         // 4 横真っ直ぐ
		UNDERRIGHT,   // 5 下と右
		UNDERLEFT,    // 6 下と左
		TOPRIGHT,     // 7 上と右
		TOPLEFT,	  // 8 上と左
		ENEMY,        // 9 エネミー
		CLEAR
	};

	mapCountX = sizeof(map0[0]) / sizeof(map0[0][0]);
	mapCountY = sizeof(map0) / sizeof(map0[0]);

	int player = Novice::LoadTexture("./Resource/images/player.png");
	int enemy = Novice::LoadTexture("./Resource/images/enemy.png");

	int math = Novice::LoadTexture("./Resource/images/math.png");      // マス目
	int wall = Novice::LoadTexture("./Resource/images/metaru.png");    // 壁

	int vertical = Novice::LoadTexture("./Resource/images/vertical.png");
	int side = Novice::LoadTexture("./Resource/images/side.png");

	int underRight = Novice::LoadTexture("./Resource/images/underRight.png");
	int underLeft = Novice::LoadTexture("./Resource/images/underLeft.png");
	int topRight = Novice::LoadTexture("./Resource/images/topRight.png");
	int topLeft = Novice::LoadTexture("./Resource/images/topLeft.png");

	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int y = 0; y < mapCountY; y++) {
			for (int x = 0; x < mapCountX; x++) {

				if (stageNumber == STAGE0) {
					// 背景
					if (map0[y][x] == BACK)
					{
						Novice::DrawSprite(x* Size, y* Size, math, 2, 2, 0, color);
					}
					
					// 壁
					if (map0[y][x] == WALL) {
						Novice::DrawSprite(x * Size, y * Size, wall, 2, 2, 0, WHITE);
					}

					// 縦真っ直ぐ
					if (map0[y][x] == VERTICAL) {
						Novice::DrawSprite(x * Size, y * Size, vertical, 2, 2, 0, WHITE);
					}
					// 横真っ直ぐ
					if (map0[y][x] == SIDE) {
						Novice::DrawSprite(x * Size, y * Size, side, 2, 2, 0, WHITE);
					}

					// 上と右
					if (map0[y][x] == UNDERRIGHT) {
						Novice::DrawSprite(x * Size, y * Size,underRight, 2, 2, 0, WHITE);
					}
					// 上と左
					if (map0[y][x] == UNDERLEFT) {
						Novice::DrawSprite(x * Size, y * Size, underLeft, 2, 2, 0, WHITE);
					}
					// 下と右
					if (map0[y][x] == TOPRIGHT) {
						Novice::DrawSprite(x * Size, y * Size, topRight, 2, 2, 0, WHITE);
					}
					// 下と左
					if (map0[y][x] == TOPLEFT) {
						Novice::DrawSprite(x * Size, y * Size, topLeft, 2, 2, 0, WHITE);
					}

					// プレイヤー
					if (map0[y][x] == PLAYER) {
						Novice::DrawSprite(x * Size, y * Size, player, 2, 2, 0, WHITE);
					}
					// エネミー
					if (map0[y][x] == ENEMY) {
						Novice::DrawSprite(x * Size, y * Size, enemy, 1, 1, 0, WHITE);
					}
				}
			}
		}



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}