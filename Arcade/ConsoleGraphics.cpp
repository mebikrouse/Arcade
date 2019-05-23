#include "ConsoleGraphics.h"

#include <iostream>
#include <Windows.h>

ConsoleGraphics::ConsoleGraphics(int width, int height)
{
	_width = width;
	_height = height;

	_prevFrame = new wchar_t*[width];
	_nextFrame = new wchar_t*[width];
	for (int i = 0; i < width; i++)
	{
		_prevFrame[i] = new wchar_t[height];
		_nextFrame[i] = new wchar_t[height];
	}
}

ConsoleGraphics::~ConsoleGraphics()
{
	for (int i = 0; i < _width; i++) 
	{
		delete[] _prevFrame[i];
		delete[] _nextFrame[i];
	}

	delete[] _prevFrame;
	delete[] _nextFrame;
}

bool ConsoleGraphics::draw(Vector2Int position, wchar_t c)
{
	if (position.getX() < 0 || position.getX() >= _width || position.getY() < 0 || position.getY() >= _height)
		return false;

	_nextFrame[position.getX()][position.getY()] = c;

	return true;
}

void ConsoleGraphics::update()
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			if (_prevFrame[x][y] == _nextFrame[x][y])
			{
				_nextFrame[x][y] = L' ';
				continue;
			}

			setCursorPosition(x, y);
			std::wcout << _nextFrame[x][y];

			_prevFrame[x][y] = _nextFrame[x][y];
			_nextFrame[x][y] = L' ';
		}
	}

	std::cout.flush();
}

int ConsoleGraphics::getWidth()
{
	return _width;
}

int ConsoleGraphics::getHeight()
{
	return _height;
}

void ConsoleGraphics::setCursorPosition(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}