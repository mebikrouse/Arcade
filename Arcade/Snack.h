#pragma once

#include "CollidableGameObject.h"

class Snack : public CollidableGameObject
{
public:
	Snack(std::weak_ptr<Scene>, Vector2Int, wchar_t);
	~Snack();

	void draw();

	Rect getCollisionRect();
	void onCollision(std::shared_ptr<Collidable>);

private:
	wchar_t _repr;
};

