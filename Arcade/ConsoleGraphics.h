#pragma once

#include "Vector2Int.h"

class ConsoleGraphics
{
public:
	ConsoleGraphics(int, int);
	~ConsoleGraphics();

	bool draw(Vector2Int, wchar_t);
	void update();

	int getWidth();
	int getHeight();
private:
	int _width;
	int _height;

	wchar_t** _prevFrame;
	wchar_t** _nextFrame;

	void setCursorPosition(int, int);
};

