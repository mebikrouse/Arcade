#pragma once

#include "CollidableGameObject.h"
#include "Scene.h"

class Snake;

class SnakeSegment : public CollidableGameObject
{
public:
	SnakeSegment(std::weak_ptr<Scene>, std::weak_ptr<Snake>, Vector2Int, wchar_t);
	~SnakeSegment();

	void draw();

	wchar_t getRepr();
	void setRepr(wchar_t);

	Rect getCollisionRect();
	void onCollision(std::shared_ptr<Collidable>);

	std::weak_ptr<Snake> getSnake();

private:
	std::weak_ptr<Snake> _snake;
	wchar_t _repr;
};

