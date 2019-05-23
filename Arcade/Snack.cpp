#include "Snack.h"

#include "Scene.h"
#include "SnakeSegment.h"
#include "Snake.h"

Snack::Snack(std::weak_ptr<Scene> scene, Vector2Int position, wchar_t repr) : CollidableGameObject(scene, position)
{
	_repr = repr;
}

Snack::~Snack() { }

void Snack::draw()
{
	getScene().lock()->getGraphics()->draw(getPosition(), _repr);
}

Rect Snack::getCollisionRect()
{
	return Rect(getPosition(), Vector2Int(1, 1));
}

void Snack::onCollision(std::shared_ptr<Collidable> collidable)
{
	auto segment = std::dynamic_pointer_cast<SnakeSegment>(collidable);
	if (segment == NULL) return;

	segment->getSnake().lock()->makeGrow();
	destroy();
}
