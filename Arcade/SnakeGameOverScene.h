#pragma once

#include "Scene.h"

class SnakeGameOverScene : public Scene
{
public:
	SnakeGameOverScene(std::weak_ptr<SceneManager>, int);
	~SnakeGameOverScene();

	void init();

private:
	int _score;

	void playGame();
	void exit();
};

