#include "Utility.h"

#include <Windows.h>

Utility::Utility() { }

Utility::~Utility() { }

bool Utility::IsKeyPressed(int key)
{
	return GetKeyState(key) & 0x8000;
}
