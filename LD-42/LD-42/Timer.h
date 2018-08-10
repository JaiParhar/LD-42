#pragma once
#include <SDL.h>
#include <stdio.h>

class Timer
{
public:
	unsigned int endTimeMS;
	unsigned int startedTime;
	unsigned int pausedTime;
	bool timerStarted;
	bool timerPaused;
	bool done;

	bool initTimer(int endTMS, bool startDone = false);
	void setEndTime(int endTMS);
	void startTimer();
	void playTimer();
	void pauseTimer();
	Uint32 getTime();
	void checkTimer();
	bool isTimerDone();
	void timerReset();
};

