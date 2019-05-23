#pragma once

#include "Scene.h"
#include "Timer.h"

class SceneManager
{
public:
	SceneManager(std::shared_ptr<ConsoleGraphics>);
	~SceneManager();

	std::shared_ptr<ConsoleGraphics> getGraphics();
	std::shared_ptr<Timer> getTimer();

	void setScene(std::shared_ptr<Scene>);
	void stop();

private:
	std::shared_ptr<ConsoleGraphics> _graphics;
	std::shared_ptr<Scene> _currentScene;

	std::shared_ptr<Timer> _timer;

	bool _loop;

	void startGameLoop();
};

