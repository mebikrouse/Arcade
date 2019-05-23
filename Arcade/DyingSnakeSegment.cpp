#include "DyingSnakeSegment.h"

#include "Scene.h"
#include "Time.h"

DyingSnakeSegment::DyingSnakeSegment(std::weak_ptr<Scene> scene, Vector2Int position, wchar_t repr, float stepDuration) : GameObject(scene, position)
{
	_repr = L' ';
	_prevRepr = repr;

	_stepDuration = stepDuration;
	_timePassed = 0;

	_togglesCount = 0;
}

DyingSnakeSegment::~DyingSnakeSegment() { }

void DyingSnakeSegment::update()
{
	_timePassed += Time::deltaTime;
	if (_timePassed < _stepDuration) return;

	_timePassed = 0;
	
	_togglesCount++;
	if (_togglesCount > 5) destroy();

	std::swap(_repr, _prevRepr);
}

void DyingSnakeSegment::draw() 
{
	getScene().lock()->getGraphics()->draw(getPosition(), _repr);
}
