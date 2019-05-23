#pragma once

#include <memory>
#include <vector>

#include "ConsoleGraphics.h"
#include "GameObject.h"
#include "Collidable.h"
#include "Object.h"
#include "Timer.h"

class SceneManager;

class Scene : public Object
{
public:
	Scene(std::weak_ptr<SceneManager>);
	virtual ~Scene();

	void addGameObject(std::shared_ptr<GameObject>);
	void removeGameObject(std::shared_ptr<GameObject>);
	std::vector<std::shared_ptr<GameObject>> getGameObjects();

	void addCollidable(std::shared_ptr<Collidable>);
	void removeCollidable(std::shared_ptr<Collidable>);
	std::vector<std::shared_ptr<Collidable>> getCollidables();

	virtual void draw();
	virtual void update();
	virtual void init();

	std::shared_ptr<ConsoleGraphics> getGraphics();
	std::weak_ptr<SceneManager> getSceneManager();

private:
	std::weak_ptr<SceneManager> _sceneManager;
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	std::vector<std::shared_ptr<Collidable>> _collidableObjects;
};

