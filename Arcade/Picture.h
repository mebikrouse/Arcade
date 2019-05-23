#pragma once

#include "GameObject.h"

class Picture : public GameObject
{
public:
	Picture(std::weak_ptr<Scene>, Vector2Int, Vector2Int, const wchar_t*);
	~Picture();

	void draw();

private:
	wchar_t** _contents;
	Vector2Int _size;
};

