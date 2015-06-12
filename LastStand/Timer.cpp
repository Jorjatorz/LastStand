#include "Timer.h"

#include "TimerManager.h"

Timer::Timer(unsigned short int id, const std::function<void(void)>& funcToCall, float timerDuration, bool loop)
	:_deltaTime(0),
	_id(id),
	_funcToCall(funcToCall),
	_timerDuration(timerDuration),
	_loop(loop),
	_paused(false)
{
}


Timer::~Timer()
{
}

bool Timer::tick(int deltaTime)
{
	//Update delta time if the clock is not paused
	if (!_paused)
		_deltaTime += deltaTime;

	if (_deltaTime >= _timerDuration)
	{
		_funcToCall();

		//If we want to loop just reset timer
		if (_loop)
		{
			reset();
		}
		else
		{
			return true;
		}
	}

	return false;
}

void Timer::reset()
{
	_deltaTime = 0.0f;
	_paused = false;
}

void Timer::pause()
{
	_paused = true;
}

void Timer::resume()
{
	_paused = false;
}
