#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

#include "ConsoleGraphics.h"
#include "SceneManager.h"
#include "SnakeMainMenuScene.h"
#include "Time.h"

int wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	auto out = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(out, &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	auto graphics = std::shared_ptr<ConsoleGraphics>(new ConsoleGraphics(columns, rows));
	auto sceneManager = std::shared_ptr<SceneManager>(new SceneManager(graphics));

	auto scene = std::shared_ptr<SnakeMainMenuScene>(new SnakeMainMenuScene(sceneManager));
	sceneManager->setScene(scene);
}