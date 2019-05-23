#pragma once

#include "Scene.h"
#include "Snake.h"
#include "ManualSnakeManipulator.h"
#include "Label.h"

class SnakeGameScene : public Scene
{
public:
	SnakeGameScene(std::weak_ptr<SceneManager>);
	~SnakeGameScene();

	void init();
	void update();

private:
	std::shared_ptr<Snake> _snake;
	std::shared_ptr<ManualSnakeManipulator> _manipulator;
	std::shared_ptr<Label> _scoreLabel;

	int _score;

	void createSnack(Vector2Int, wchar_t);
	void createWall(Vector2Int, Vector2Int, wchar_t);

	void onSnakeDestroy();
	void showGameOverScene();

	void onSnackDestroy();
};

