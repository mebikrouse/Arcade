#pragma once

#include <memory>

#include "Object.h"
#include "Rect.h"

class Collidable : public virtual Object
{
public:
	Collidable();
	virtual ~Collidable();

	virtual Rect getCollisionRect() = 0;
	virtual void onCollision(std::shared_ptr<Collidable>);

	bool isInside(Vector2Int);
};

