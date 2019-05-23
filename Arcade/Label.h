#pragma once

#include <string>

#include "GameObject.h"

class Label : public GameObject
{
public:
	Label(std::weak_ptr<Scene>, Vector2Int, std::wstring);
	~Label();

	void draw();

	void setContents(std::wstring);

private:
	std::wstring _contents;
	int _length;
};

