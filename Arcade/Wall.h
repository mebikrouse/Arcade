#pragma once

#include "CollidableGameObject.h"

class Wall : public CollidableGameObject
{
public:
	Wall(std::weak_ptr<Scene>, Vector2Int, Vector2Int, wchar_t);
	~Wall();

	void draw();

	virtual Rect getCollisionRect();
	virtual void onCollision(std::shared_ptr<Collidable>);

private:
	Vector2Int _size;
	wchar_t _repr;
};

