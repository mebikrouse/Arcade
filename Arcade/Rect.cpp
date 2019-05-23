#include "Rect.h"

Rect::Rect() : Rect(Vector2Int()) { }

Rect::Rect(Vector2Int size) : Rect(Vector2Int(), size) { }

Rect::Rect(Vector2Int position, Vector2Int size)
{
	_position = position;
	_size = size;
}

Rect::~Rect() { }

Vector2Int Rect::getPosition()
{
	return _position;
}

Vector2Int Rect::getSize()
{
	return _size;
}

bool Rect::intersects(Rect other)
{
	if (getPosition().getX() > other.getPosition().getX() + other.getSize().getX() - 1 || 
		other.getPosition().getX() > getPosition().getX() + getSize().getX() - 1)
		return false;
	
	if (getPosition().getY() > other.getPosition().getY() + other.getSize().getY() - 1 ||
		other.getPosition().getY() > getPosition().getY() + getSize().getY() - 1)
		return false;

	return true;
}

bool Rect::contains(Vector2Int point)
{
	return point >= _position && point < _position + _size;
}