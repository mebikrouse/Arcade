#include "SnakeGameOverScene.h"

#include <Windows.h>

#include "Picture.h"
#include "Label.h"
#include "SnakeGameScene.h"
#include "SceneManager.h"
#include "Button.h"
#include "ButtonSelector.h"

SnakeGameOverScene::SnakeGameOverScene(std::weak_ptr<SceneManager> sceneManager, int score) : Scene(sceneManager) 
{
	_score = score;
}

SnakeGameOverScene::~SnakeGameOverScene() { }

void SnakeGameOverScene::init()
{
	Vector2Int gameOverPictureSize = Vector2Int(55, 5);
	Vector2Int gameOverPicturePosition = Vector2Int((getGraphics()->getWidth() - gameOverPictureSize.getX()) / 2, (getGraphics()->getHeight() - gameOverPictureSize.getY()) * 0.25);
	const wchar_t* gameOverPictureContents = L"   _________    __  _________   ____ _    ____________   / ____/   |  /  |/  / ____/  / __ \\ |  / / ____/ __ \\ / / __/ /| | / /|_/ / __/    / / / / | / / __/ / /_/ // /_/ / ___ |/ /  / / /___   / /_/ /| |/ / /___/ _, _/ \\____/_/  |_/_/  /_/_____/   \\____/ |___/_____/_/ |_|  ";
	auto gameOverPicture = std::shared_ptr<Picture>(new Picture(shared_from_base<SnakeGameOverScene>(), gameOverPicturePosition, gameOverPictureSize, gameOverPictureContents));
	addGameObject(gameOverPicture);

	std::wstring scoreLabelContents = L"Score achieved: " + std::to_wstring(_score);
	Vector2Int scoreLabelPosition = Vector2Int((getGraphics()->getWidth() - scoreLabelContents.length()) / 2, getGraphics()->getHeight() * 0.475);
	auto scoreLabel = std::shared_ptr<Label>(new Label(shared_from_base<SnakeGameOverScene>(), scoreLabelPosition, scoreLabelContents));
	addGameObject(scoreLabel);

	Vector2Int buttonsSize = Vector2Int(25, 3);

	Vector2Int playButtonPosition = Vector2Int((getGraphics()->getWidth() - buttonsSize.getX()) / 2, (getGraphics()->getHeight() - buttonsSize.getY()) * 0.7);
	std::wstring playButtonLabelContents = L"Play again";
	auto playButton = std::shared_ptr<Button>(new Button(shared_from_base<SnakeGameOverScene>(), playButtonPosition, buttonsSize, playButtonLabelContents));
	playButton->OnActivate += std::bind(&SnakeGameOverScene::playGame, this);
	addGameObject(playButton);

	Vector2Int exitButtonPosition = Vector2Int((getGraphics()->getWidth() - buttonsSize.getX()) / 2, (getGraphics()->getHeight() - buttonsSize.getY()) * 0.85);
	std::wstring exitButtonLabelContents = L"Exit";
	auto exitButton = std::shared_ptr<Button>(new Button(shared_from_base<SnakeGameOverScene>(), exitButtonPosition, buttonsSize, exitButtonLabelContents));
	exitButton->OnActivate += std::bind(&SnakeGameOverScene::exit, this);
	addGameObject(exitButton);

	auto buttonSelector = std::shared_ptr<ButtonSelector>(new ButtonSelector(shared_from_base<SnakeGameOverScene>()));
	buttonSelector->addButton(playButton);
	buttonSelector->addButton(exitButton);
	addGameObject(buttonSelector);
}

void SnakeGameOverScene::playGame()
{
	auto scene = std::shared_ptr<SnakeGameScene>(new SnakeGameScene(getSceneManager()));
	getSceneManager().lock()->setScene(scene);
}

void SnakeGameOverScene::exit()
{
	getSceneManager().lock()->stop();
}