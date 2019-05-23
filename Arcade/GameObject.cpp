#include "GameObject.h"

#include "Scene.h"

GameObject::GameObject(std::weak_ptr<Scene> scene, Vector2Int position)
{
	_scene = scene;
	_position = position;
	_destroyed = false;
}

GameObject::~GameObject() { }

void GameObject::init() { }

void GameObject::destroy()
{
	if (_destroyed) return;

	_destroyed = true;

	preDestroy();

	getScene().lock()->removeGameObject(shared_from_base<GameObject>());
	OnDestroy();
}

void GameObject::update() { }

void GameObject::draw() { }

std::weak_ptr<Scene> GameObject::getScene()
{
	return _scene;
}

Vector2Int GameObject::getPosition()
{
	return _position;
}

void GameObject::setPosition(Vector2Int position)
{
	_position = position;
}

void GameObject::preDestroy() { }