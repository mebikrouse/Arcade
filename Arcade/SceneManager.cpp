#include "SceneManager.h"

#include <Windows.h>
#include <ctime>

#include "Time.h"

SceneManager::SceneManager(std::shared_ptr<ConsoleGraphics> graphics)
{
	_graphics = graphics;
	_timer = std::shared_ptr<Timer>(new Timer());
	_loop = false;
}

SceneManager::~SceneManager() { }

std::shared_ptr<ConsoleGraphics> SceneManager::getGraphics()
{
	return _graphics;
}

std::shared_ptr<Timer> SceneManager::getTimer()
{
	return _timer;
}

void SceneManager::setScene(std::shared_ptr<Scene> scene)
{
	bool temp = _loop;
	_loop = true;

	_currentScene = scene;
	_currentScene->init();

	if (!temp)
		startGameLoop();
}

void SceneManager::stop()
{
	_loop = false;
}

void SceneManager::startGameLoop()
{
	clock_t begin = clock();
	clock_t end = clock();

	while (_loop)
	{
		end = clock();
		Time::deltaTime = float(end - begin) / CLOCKS_PER_SEC;
		begin = clock();

		_timer->update();
		_currentScene->update();
		_currentScene->draw();
		_graphics->update();
	}
}
