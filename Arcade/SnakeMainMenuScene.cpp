#include "SnakeMainMenuScene.h"

#include <Windows.h>

#include "Picture.h"
#include "Label.h"
#include "SnakeGameScene.h"
#include "SceneManager.h"
#include "Button.h"
#include "ButtonSelector.h"

SnakeMainMenuScene::SnakeMainMenuScene(std::weak_ptr<SceneManager> sceneManager) : Scene(sceneManager) { }

SnakeMainMenuScene::~SnakeMainMenuScene() { }

void SnakeMainMenuScene::init()
{
	Vector2Int snakePictureSize = Vector2Int(63, 5);
	Vector2Int snakePicturePosition = Vector2Int((getGraphics()->getWidth() - snakePictureSize.getX()) / 2, (getGraphics()->getHeight() - snakePictureSize.getY()) * 0.25);
	const wchar_t* snakePictureContents = L"   _____ _   _____    __ __ ______   _________    __  _________  / ___// | / /   |  / //_// ____/  / ____/   |  /  |/  / ____/  \\__ \\/  |/ / /| | / ,<  / __/    / / __/ /| | / /|_/ / __/    ___/ / /|  / ___ |/ /| |/ /___   / /_/ / ___ |/ /  / / /___   /____/_/ |_/_/  |_/_/ |_/_____/   \\____/_/  |_/_/  /_/_____/   ";
	auto snakePicture = std::shared_ptr<Picture>(new Picture(shared_from_base<SnakeMainMenuScene>(), snakePicturePosition, snakePictureSize, snakePictureContents));
	addGameObject(snakePicture);

	Vector2Int buttonsSize = Vector2Int(25, 3);

	Vector2Int playButtonPosition = Vector2Int((getGraphics()->getWidth() - buttonsSize.getX()) / 2, (getGraphics()->getHeight() - buttonsSize.getY()) * 0.6);
	std::wstring playButtonLabelContents = L"Start Game";
	auto playButton = std::shared_ptr<Button>(new Button(shared_from_base<SnakeMainMenuScene>(), playButtonPosition, buttonsSize, playButtonLabelContents));
	playButton->OnActivate += std::bind(&SnakeMainMenuScene::playGame, this);
	addGameObject(playButton);

	Vector2Int exitButtonPosition = Vector2Int((getGraphics()->getWidth() - buttonsSize.getX()) / 2, (getGraphics()->getHeight() - buttonsSize.getY()) * 0.75);
	std::wstring exitButtonLabelContents = L"Exit";
	auto exitButton = std::shared_ptr<Button>(new Button(shared_from_base<SnakeMainMenuScene>(), exitButtonPosition, buttonsSize, exitButtonLabelContents));
	exitButton->OnActivate += std::bind(&SnakeMainMenuScene::exit, this);
	addGameObject(exitButton);

	auto buttonSelector = std::shared_ptr<ButtonSelector>(new ButtonSelector(shared_from_base<SnakeMainMenuScene>()));
	buttonSelector->addButton(playButton);
	buttonSelector->addButton(exitButton);
	addGameObject(buttonSelector);
}

void SnakeMainMenuScene::playGame()
{
	auto scene = std::shared_ptr<SnakeGameScene>(new SnakeGameScene(getSceneManager()));
	getSceneManager().lock()->setScene(scene);
}

void SnakeMainMenuScene::exit()
{
	getSceneManager().lock()->stop();
}