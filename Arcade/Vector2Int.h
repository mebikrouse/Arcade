#pragma once
class Vector2Int
{
public:
	Vector2Int();
	Vector2Int(int, int);
	~Vector2Int();

	int getX() const;
	int getY() const;

	friend Vector2Int operator+(Vector2Int const&, Vector2Int const&);
	friend Vector2Int operator-(Vector2Int const&, Vector2Int const&);
	friend Vector2Int operator/(Vector2Int const&, int const&);
	friend bool operator>=(Vector2Int const&, Vector2Int const&);
	friend bool operator<(Vector2Int const&, Vector2Int const&);

private:
	int _x;
	int _y;
};

