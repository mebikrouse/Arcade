#include "SnakeGameScene.h"

#include <Windows.h>

#include "Snack.h"
#include "Wall.h"
#include "Snake.h"
#include "SnakeGameOverScene.h"
#include "SceneManager.h"
#include "SnackHandler.h"
#include "Utility.h"

SnakeGameScene::SnakeGameScene(std::weak_ptr<SceneManager> sceneManager) : Scene(sceneManager) 
{ 
	_score = 0;
}

SnakeGameScene::~SnakeGameScene() { }

void SnakeGameScene::init()
{
	wchar_t wallRepr = L'\u2592';
	createWall(Vector2Int(2, 3), Vector2Int(getGraphics()->getWidth() - 4, 2), wallRepr);
	createWall(Vector2Int(2, getGraphics()->getHeight() - 3), Vector2Int(getGraphics()->getWidth() - 4, 2), wallRepr);
	createWall(Vector2Int(2, 5), Vector2Int(4, getGraphics()->getHeight() - 8), wallRepr);
	createWall(Vector2Int(getGraphics()->getWidth() - 6, 5), Vector2Int(4, getGraphics()->getHeight() - 8), wallRepr);

	wchar_t snakeHeadRepr = L'\u25CB';
	wchar_t snakeRepr = L'\u25CB';
	auto snake = std::shared_ptr<Snake>(new Snake(shared_from_base<SnakeGameScene>(), Vector2Int(15, 11), 5, SOUTH, snakeHeadRepr, snakeRepr));
	snake->OnDestroy += EventHandler(std::bind(&SnakeGameScene::onSnakeDestroy, this));
	snake->init();
	addGameObject(snake);
	
	wchar_t snackRepr = L'\u2022';
	Rect snackArea = Rect(Vector2Int(6, 5), Vector2Int(getGraphics()->getWidth() - 12, getGraphics()->getHeight() - 8));
	auto snackHandler = std::shared_ptr<SnackHandler>(new SnackHandler(shared_from_base<SnakeGameScene>(), snackArea, snackRepr));
	snackHandler->OnSnackDestroy += std::bind(&SnakeGameScene::onSnackDestroy, this);
	snackHandler->generate();
	addGameObject(snackHandler);

	float manipulatorStepDuration = 0.125;
	_manipulator = std::shared_ptr<ManualSnakeManipulator>(new ManualSnakeManipulator(shared_from_base<SnakeGameScene>(), snake, manipulatorStepDuration));
	addGameObject(_manipulator);

	std::wstring scoreLabelContents = L"Current score: 0";
	Vector2Int scoreLabelPosition = Vector2Int(2, 1);
	_scoreLabel = std::shared_ptr<Label>(new Label(shared_from_base<SnakeGameScene>(), scoreLabelPosition, scoreLabelContents));
	addGameObject(_scoreLabel);

	std::wstring helpLabelContents = L"\u25B2 \u25BC \u25C4 \u25BA to move snake; ESC to stop game;";
	Vector2Int helpLabelPosition = Vector2Int(getGraphics()->getWidth() - helpLabelContents.length() - 1, 1);
	auto helpLabel = std::shared_ptr<Label>(new Label(shared_from_base<SnakeGameScene>(), helpLabelPosition, helpLabelContents));
	addGameObject(helpLabel);
}

void SnakeGameScene::update()
{
	Scene::update();

	if (Utility::IsKeyPressed(VK_ESCAPE))
		showGameOverScene();
}

void SnakeGameScene::createSnack(Vector2Int position, wchar_t repr)
{
	auto snack = std::shared_ptr<Snack>(new Snack(shared_from_base<SnakeGameScene>(), position, repr));
	addGameObject(snack);
	addCollidable(snack);
}

void SnakeGameScene::createWall(Vector2Int position, Vector2Int size, wchar_t repr)
{
	auto wall = std::shared_ptr<Wall>(new Wall(shared_from_base<SnakeGameScene>(), position, size, repr));
	addGameObject(wall);
	addCollidable(wall);
}

void SnakeGameScene::onSnakeDestroy()
{
	_manipulator->destroy();
	_manipulator.reset();

	getSceneManager().lock()->getTimer()->setTimeout(std::bind(&SnakeGameScene::showGameOverScene, this), 2);
}

void SnakeGameScene::showGameOverScene()
{
	auto gameOverScene = std::shared_ptr<SnakeGameOverScene>(new SnakeGameOverScene(getSceneManager(), _score));
	getSceneManager().lock()->setScene(gameOverScene);
}

void SnakeGameScene::onSnackDestroy()
{
	_score++;
	_scoreLabel->setContents(L"Current score: " + std::to_wstring(_score));
}
