#include "ManualSnakeManipulator.h"

#include <Windows.h>

#include "Time.h"
#include "Utility.h"

ManualSnakeManipulator::ManualSnakeManipulator(std::weak_ptr<Scene> scene, std::shared_ptr<Snake> snake, float stepDuration) : GameObject(scene, Vector2Int())
{
	_snake = snake;
	_stepDuration = stepDuration;
	_timePassed = 0;
	_newDirection = _snake->getDirection();
}

ManualSnakeManipulator::~ManualSnakeManipulator() { }

void ManualSnakeManipulator::update()
{
	updateDirection();

	_timePassed += Time::deltaTime;
	if (_timePassed >= _stepDuration) {
		_timePassed = 0;
		_snake->setDirection(_newDirection);
		_snake->move();
	}
}

void ManualSnakeManipulator::updateDirection()
{
	Direction newDirection;
	if (Utility::IsKeyPressed(VK_UP))
		newDirection = NORTH;
	else if (Utility::IsKeyPressed(VK_DOWN))
		newDirection = SOUTH;
	else if (Utility::IsKeyPressed(VK_RIGHT))
		newDirection = EAST;
	else if (Utility::IsKeyPressed(VK_LEFT))
		newDirection = WEST;
	else return;

	Direction snakeDirection = _snake->getDirection();
	if ((snakeDirection == NORTH || snakeDirection == SOUTH) && newDirection != NORTH && newDirection != SOUTH ||
		(snakeDirection == EAST || snakeDirection == WEST) && newDirection != EAST && newDirection != WEST)
		_newDirection = newDirection;
}
