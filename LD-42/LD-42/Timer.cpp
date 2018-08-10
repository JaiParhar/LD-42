#include "Timer.h"

bool Timer::initTimer(int endTMS, bool startDone) 
{
	endTimeMS = endTMS;
	startedTime = 0;
	pausedTime = 0;
	timerStarted = false;
	timerPaused = false;
	done = startDone;
	return true;
}

void Timer::startTimer()
{
	timerStarted = true;
	timerPaused = false;
	startedTime = SDL_GetTicks();
	pausedTime = 0;
}

void Timer::playTimer() 
{
	if (timerStarted && timerPaused) 
	{
		timerPaused = false;
		startedTime = SDL_GetTicks() - pausedTime; 
		pausedTime = 0; 
	}
}

Uint32 Timer::getTime() 
{
	Uint32 time = 0; 
	if(timerStarted) 
	{
		if(timerPaused) 
		{
			time = pausedTime;
		}
		else 
		{
			time = SDL_GetTicks() - startedTime; 
		} 
	}
	return time; 
}

void Timer::pauseTimer()
{
	if (timerStarted && !timerPaused)
	{
		timerPaused = true; 
		pausedTime = SDL_GetTicks() - timerPaused; 
		startedTime = 0;
	}
}

void Timer::checkTimer()
{
	if (getTime() > endTimeMS)
	{
		done = true;
	}
}

bool Timer::isTimerDone()
{
	return done;
}

void Timer::timerReset()
{
	timerStarted = false;
	timerPaused = false;
	startedTime = 0;
	pausedTime = 0;
	done = false;
}

void Timer::setEndTime(int endTMS) 
{
	endTimeMS = endTMS;
}