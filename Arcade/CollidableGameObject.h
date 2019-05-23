#pragma once

#include "GameObject.h"
#include "Collidable.h"

class CollidableGameObject : public GameObject, public Collidable
{
public:
	CollidableGameObject(std::weak_ptr<Scene>, Vector2Int);
	virtual ~CollidableGameObject() = 0;

	virtual void destroy();
};

