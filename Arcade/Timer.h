#pragma once

#include <functional>
#include <vector>

struct Timeout {
	float timeout;
	std::function<void()> delegate;
};

class Timer
{
public:
	Timer();
	~Timer();

	void setTimeout(std::function<void()>, float);

	void update();

private:
	std::vector<Timeout> _timeouts;
};

