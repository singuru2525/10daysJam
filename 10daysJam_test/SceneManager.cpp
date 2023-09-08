#include "SceneManager.h"

SceneManager::~SceneManager()
{
	delete gameManager_;
	delete title_;
	delete stageSelect_;
}

void SceneManager::Initialize()
{
	// ゲーム管理の初期化
	gameManager_ = new GameManager;

	// タイトル管理の初期化
	title_ = new Title;
	title_->Initialize();

	// ステージセレクトの初期化
	stageSelect_ = new StageSelect;
	stageSelect_->Initialize();

	sceneNo_ = TitleScene;
}

void SceneManager::Update(char* keys, char* preKeys)
{
	switch (sceneNo_) {
	case TitleScene:

		title_->Update();

		if (title_->GetIsStart() == true)
		{
			sceneNo_ = StageSelectScene;

		}
		break;

	case StageSelectScene:

		stageSelect_->Update();
		if (stageSelect_->IsGameStart() == true)
		{
			gameManager_->Initialize();
			sceneNo_ = Game;
		}

		break;

	case Game:

		gameManager_->Update(stageSelect_->GetStageNo(), keys);

		if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
			stageSelect_->Initialize();
			sceneNo_ = StageSelectScene;
		}

		break;
	case GameClear:

		break;
	case GameOver:

		if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
			sceneNo_ = Game;
			Initialize();
		}

		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	switch (sceneNo_) {
	case TitleScene:

		title_->Draw();

		break;

	case StageSelectScene:

		stageSelect_->Draw();

		break;


	case Game:

		gameManager_->Draw(stageSelect_->GetStageNo());

		break;
	case GameClear:

		break;
	case GameOver:

		break;
	default:
		break;
	}
}