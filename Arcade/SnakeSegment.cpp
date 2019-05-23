#include "SnakeSegment.h"

#include "Snake.h"

SnakeSegment::SnakeSegment(std::weak_ptr<Scene> scene, std::weak_ptr<Snake> snake, Vector2Int position, wchar_t repr) : CollidableGameObject(scene, position)
{
	_snake = snake;
	_repr = repr;
}

SnakeSegment::~SnakeSegment() { }

void SnakeSegment::draw()
{
	getScene().lock()->getGraphics()->draw(getPosition(), _repr);
}

wchar_t SnakeSegment::getRepr()
{
	return _repr;
}

void SnakeSegment::setRepr(wchar_t repr)
{
	_repr = repr;
}

Rect SnakeSegment::getCollisionRect() 
{
	return Rect(getPosition(), Vector2Int(1, 1));
}

void SnakeSegment::onCollision(std::shared_ptr<Collidable> collidable)
{
	auto segment = std::dynamic_pointer_cast<SnakeSegment>(collidable);
	if (segment == NULL) return;

	segment->getSnake().lock()->destroy();
}

std::weak_ptr<Snake> SnakeSegment::getSnake()
{
	return _snake;
}
