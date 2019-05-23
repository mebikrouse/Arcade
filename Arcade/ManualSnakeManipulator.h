#pragma once

#include "GameObject.h"
#include "Snake.h"

class ManualSnakeManipulator : public GameObject
{
public:
	ManualSnakeManipulator(std::weak_ptr<Scene>, std::shared_ptr<Snake>, float);
	~ManualSnakeManipulator();

	void update();

private:
	std::shared_ptr<Snake> _snake;
	float _stepDuration;
	float _timePassed;
	Direction _newDirection;

	void updateDirection();
};

