#ifndef TIMER
#define TIMER

#include <windows.h>

class timer{
public:
	timer();

	void Init();
	double GetTime();
	double GetLastTime();

	void PauseTimer();
	void StartTimer();

private:

	bool timerType;
	double frequency;
	double lastTime;

	bool pause;
};

extern timer g_Timer;

#endif