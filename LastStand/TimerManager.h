#pragma once

#include <unordered_map>
#include <functional>

#include "Timer.h"

class FEngine;

//Class that manage and updates all the timers of the engine.
class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	static unsigned int getTotalExecutionTime();

	//Creates a new timer given a member function, a duration of the timer and a boolean that is true if the timer loops
	template <class T, class U>
	Timer* addTimer(void* functClass, T&& function, U&& functionClass, float timerDuration, bool loop)
	{
		Timer* t = new Timer(_nextId, std::bind(function, functionClass), timerDuration, loop);

		_timersList.insert(std::make_pair(_nextId, t));
		_nextId++;

		return t;
	}
	//Deletes a timer
	void deleteTimer(Timer* timer);

private:
	friend class FEngine; //Let FEngine access tick function

	//Updates the tick of all timers
	///TODO make this function eficient (with a queue with only the unpaused timers etc)
	void tick(int deltaTime);

	//Container of all the created timers. ID/TIMER
	std::unordered_map<unsigned short int, Timer*> _timersList;
	unsigned short int _nextId; //Next id that will be given to a new timer
};

