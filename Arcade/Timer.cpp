#include "Timer.h"

#include "Time.h"

Timer::Timer() { }

Timer::~Timer() { }

void Timer::setTimeout(std::function<void()> delegate, float timeout)
{
	_timeouts.push_back({ timeout, delegate });
}

void Timer::update()
{
	for (auto it = _timeouts.begin(); it != _timeouts.end(); ) {
		(*it).timeout -= Time::deltaTime;
		if ((*it).timeout < 0)
		{
			(*it).delegate();
			it = _timeouts.erase(it);
		}
		else it++;
	}
}
