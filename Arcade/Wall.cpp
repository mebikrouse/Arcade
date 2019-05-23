#include "Wall.h"

#include "Scene.h"
#include "Snake.h"

Wall::Wall(std::weak_ptr<Scene> scene, Vector2Int position, Vector2Int size, wchar_t repr) : CollidableGameObject(scene, position)
{
	_size = size;
	_repr = repr;
}

Wall::~Wall() { }

void Wall::draw()
{
	for (int x = getPosition().getX(); x < getPosition().getX() + _size.getX(); x++)
		for (int y = getPosition().getY(); y < getPosition().getY() + _size.getY(); y++)
			getScene().lock()->getGraphics()->draw(Vector2Int(x, y), _repr);
}

Rect Wall::getCollisionRect()
{
	return Rect(getPosition(), _size);
}

void Wall::onCollision(std::shared_ptr<Collidable> collidable)
{
	auto segment = std::dynamic_pointer_cast<SnakeSegment>(collidable);
	if (segment == NULL) return;

	segment->getSnake().lock()->destroy();
}