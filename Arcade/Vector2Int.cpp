#include "Vector2Int.h"

Vector2Int::Vector2Int() : Vector2Int(0, 0) { }

Vector2Int::Vector2Int(int x, int y)
{
	_x = x;
	_y = y;
}

Vector2Int::~Vector2Int() { }

int Vector2Int::getX() const
{
	return _x;
}

int Vector2Int::getY() const
{
	return _y;
}

Vector2Int operator+(Vector2Int const &a, Vector2Int const &b)
{
	return Vector2Int(a.getX() + b.getX(), a.getY() + b.getY());
}

Vector2Int operator-(Vector2Int const& a, Vector2Int const& b)
{
	return Vector2Int(a.getX() - b.getX(), a.getY() - b.getY());
}

Vector2Int operator/(Vector2Int const& a, int const& b)
{
	return Vector2Int(a.getX() / b, a.getY() / b);
}

bool operator>=(Vector2Int const& a, Vector2Int const& b)
{
	return a.getX() >= b.getX() && a.getY() >= b.getY();
}

bool operator<(Vector2Int const& a, Vector2Int const& b)
{
	return a.getX() < b.getX() && a.getY() < b.getY();
}