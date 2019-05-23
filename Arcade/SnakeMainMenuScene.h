#pragma once

#include "Scene.h"

class SnakeMainMenuScene : public Scene
{
public:
	SnakeMainMenuScene(std::weak_ptr<SceneManager>);
	~SnakeMainMenuScene();

	void init();

private:
	void playGame();
	void exit();
};

