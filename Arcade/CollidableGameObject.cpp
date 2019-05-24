#include "CollidableGameObject.h"

#include "Scene.h"

CollidableGameObject::CollidableGameObject(std::weak_ptr<Scene> scene, Vector2Int position) : GameObject(scene, position) { }

CollidableGameObject::~CollidableGameObject() { }

void CollidableGameObject::destroy()
{
	getScene().lock()->removeCollidable(shared_from_base<Collidable>());
	GameObject::destroy();
}