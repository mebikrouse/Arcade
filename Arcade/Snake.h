#pragma once

#include "GameObject.h"
#include "Direction.h"
#include "SnakeSegment.h"
#include "DyingSnakeSegment.h"

struct SnakeNode 
{
	SnakeNode* next;
	SnakeNode* prev;
	std::shared_ptr<SnakeSegment> segment;
};

class Snake : public GameObject
{
public:
	Snake(std::weak_ptr<Scene>, Vector2Int, int, Direction, wchar_t, wchar_t);
	~Snake();

	void init();

	Direction getDirection();
	void setDirection(Direction);

	void move();
	void makeGrow();

protected:
	void preDestroy();

private:
	Vector2Int _headPosition;
	Vector2Int _prevTailPosition;

	Direction _headDirection;

	int _length;
	int _growth;

	wchar_t _headRepr;
	wchar_t _repr;

	SnakeNode* _head;
	SnakeNode* _tail;

	std::shared_ptr<SnakeSegment> createSegment(Vector2Int, wchar_t);
	std::shared_ptr<DyingSnakeSegment> createDyingSegment(Vector2Int, wchar_t);

	void grow();

	Vector2Int getDiff(Direction);
};

