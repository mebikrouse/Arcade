#pragma once

#include "GameObject.h"

class DyingSnakeSegment : public GameObject
{
public:
	DyingSnakeSegment(std::weak_ptr<Scene>, Vector2Int, wchar_t, float);
	~DyingSnakeSegment();

	void update();
	void draw();

private:
	wchar_t _repr;
	wchar_t _prevRepr;

	float _stepDuration;
	float _timePassed;

	int _togglesCount;
};

