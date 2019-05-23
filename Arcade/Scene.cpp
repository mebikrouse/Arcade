#include "Scene.h"

#include <algorithm>
#include <tuple>

#include "SceneManager.h"

Scene::Scene(std::weak_ptr<SceneManager> sceneManager) 
{
	_sceneManager = sceneManager;
}

Scene::~Scene() { }

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto it = std::find_if(_gameObjects.begin(), _gameObjects.end(), [&](std::shared_ptr<GameObject> const& p) {
		return *p == *gameObject;
	});

	if (it == _gameObjects.end()) _gameObjects.push_back(gameObject);
}

void Scene::removeGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto it = std::find_if(_gameObjects.begin(), _gameObjects.end(), [&](std::shared_ptr<GameObject> const& p) {
		return *p == *gameObject;
	});

	if (it != _gameObjects.end()) _gameObjects.erase(it);
}

std::vector<std::shared_ptr<GameObject>> Scene::getGameObjects()
{
	return _gameObjects;
}

void Scene::addCollidable(std::shared_ptr<Collidable> collidable)
{
	auto it = std::find_if(_collidableObjects.begin(), _collidableObjects.end(), [&](std::shared_ptr<Collidable> const& p) {
		return *p == *collidable;
	});

	if (it == _collidableObjects.end()) _collidableObjects.push_back(collidable);
}

void Scene::removeCollidable(std::shared_ptr<Collidable> collidable)
{
	auto it = std::find_if(_collidableObjects.begin(), _collidableObjects.end(), [&](std::shared_ptr<Collidable> const& p) {
		return *p == *collidable;
	});

	if (it != _collidableObjects.end()) _collidableObjects.erase(it);
}

std::vector<std::shared_ptr<Collidable>> Scene::getCollidables()
{
	return _collidableObjects;
}

void Scene::draw()
{
	for (auto go : _gameObjects)
		go->draw();
}

void Scene::update()
{
	auto gameObjects = _gameObjects;

	for (auto go : gameObjects)
		go->update();

	auto collidableObjects = _collidableObjects;

	int size = collidableObjects.size();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			auto a = collidableObjects[i];
			auto b = collidableObjects[j];

			if (!a->getCollisionRect().intersects(b->getCollisionRect())) continue;

			a->onCollision(b);
			b->onCollision(a);
		}
	}
}

void Scene::init() { }

std::shared_ptr<ConsoleGraphics> Scene::getGraphics()
{
	return _sceneManager.lock()->getGraphics();
}

std::weak_ptr<SceneManager> Scene::getSceneManager()
{
	return _sceneManager;
}