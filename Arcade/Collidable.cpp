#include "Collidable.h"

Collidable::Collidable() { }

Collidable::~Collidable() { }

void Collidable::onCollision(std::shared_ptr<Collidable> other) { }

bool Collidable::isInside(Vector2Int point)
{
	return getCollisionRect().contains(point);
}
