#pragma once

#include "Vector2Int.h"

class Rect
{
public:
	Rect();
	Rect(Vector2Int);
	Rect(Vector2Int, Vector2Int);
	~Rect();

	Vector2Int getPosition();
	Vector2Int getSize();

	bool intersects(Rect);
	bool contains(Vector2Int);

private:
	Vector2Int _position;
	Vector2Int _size;
};

