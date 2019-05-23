#pragma once

#include <string>

#include "GameObject.h"
#include "Event.h"

class Button : public GameObject
{
public:
	Button(std::shared_ptr<Scene>, Vector2Int, Vector2Int, std::wstring);
	~Button();

	void draw();

	void select();
	void deselect();
	bool isSelected();

	void activate();

	Event OnActivate;

private:
	Vector2Int _size;
	Vector2Int _labelStart;
	int _labelLength;
	std::wstring _labelContents;
	bool _selected;

	wchar_t getLTCorner();
	wchar_t getLBCorner();
	wchar_t getRTCorner();
	wchar_t getRBCorner();
	wchar_t getVertLine();
	wchar_t getHorLine();
};

