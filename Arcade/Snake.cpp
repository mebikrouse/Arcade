#include "Snake.h"

Snake::Snake(std::weak_ptr<Scene> scene, Vector2Int headPosition, int length, Direction headDirection, wchar_t headRepr, wchar_t repr) : GameObject(scene, Vector2Int())
{
	_headPosition = headPosition;
	_headDirection = headDirection;

	_length = length;
	_growth = 0;

	_headRepr = headRepr;
	_repr = repr;

	_head = NULL;
	_tail = NULL;
}

Snake::~Snake()
{
	SnakeNode* node = _head;
	while (node != NULL)
	{
		SnakeNode* temp = node;
		node = node->next;

		delete(temp);
	}
}

void Snake::init()
{
	_head = new SnakeNode();
	_head->segment = createSegment(_headPosition, _headRepr);

	_tail = _head;

	for (int i = 0; i < _length; i++)
	{
		SnakeNode* newTail = new SnakeNode();
		newTail->segment = createSegment(_tail->segment->getPosition() - getDiff(_headDirection), _repr);
		_tail->next = newTail;
		newTail->prev = _tail;
		_tail = newTail;
	}
}

Direction Snake::getDirection()
{
	return _headDirection;
}

void Snake::setDirection(Direction direction)
{
	_headDirection = direction;
}

void Snake::move()
{
	Vector2Int headPosition = _head->segment->getPosition();
	Vector2Int newHeadPosition = headPosition + getDiff(_headDirection);

	_prevTailPosition = _tail->segment->getPosition();
	_tail->segment->setPosition(newHeadPosition);

	if (_head == _tail) return;

	SnakeNode* swapNode = _tail;

	_tail = _tail->prev;
	_tail->next = NULL;

	swapNode->prev = NULL;
	swapNode->next = _head;

	_head->prev = swapNode;
	_head->segment->setRepr(_repr);

	_head = swapNode;
	_head->segment->setRepr(_headRepr);

	if (_growth == 0) return;

	grow();
	_growth--;
}

void Snake::makeGrow()
{
	_growth++;
}

void Snake::preDestroy()
{
	SnakeNode* node = _head;
	while (node != NULL)
	{
		auto segment = node->segment;
		createDyingSegment(segment->getPosition(), segment->getRepr());

		node->segment->destroy();
		node = node->next;
	}
}

std::shared_ptr<SnakeSegment> Snake::createSegment(Vector2Int position, wchar_t repr)
{
	auto segment = std::shared_ptr<SnakeSegment>(new SnakeSegment(getScene(), shared_from_base<Snake>(), position, repr));
	getScene().lock()->addGameObject(segment);
	getScene().lock()->addCollidable(segment);

	return segment;
}

std::shared_ptr<DyingSnakeSegment> Snake::createDyingSegment(Vector2Int position, wchar_t repr)
{
	auto segment = std::shared_ptr<DyingSnakeSegment>(new DyingSnakeSegment(getScene(), position, repr, 0.25));
	getScene().lock()->addGameObject(segment);
	
	return segment;
}

void Snake::grow()
{
	SnakeNode * newTail = new SnakeNode();
	newTail->segment = createSegment(_prevTailPosition, _repr);

	_tail->next = newTail;
	newTail->prev = _tail;

	_tail = newTail;
}

Vector2Int Snake::getDiff(Direction direction)
{
	switch (direction)
	{
	case NORTH:
		return Vector2Int(0, -1);
	case SOUTH:
		return Vector2Int(0, 1);
	case EAST:
		return Vector2Int(1, 0);
	case WEST:
		return Vector2Int(-1, 0);
	}
}
