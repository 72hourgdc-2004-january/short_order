#include "timer.h"
 
timer g_Timer; //global timer... should be a singleton or something, whatever

timer::timer()
{
	frequency = 0.0;
	lastTime = 0.0;

	timerType = false;
	pause = false;
}

void timer::Init()
{
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&frequency))
		timerType = true;
}

double timer::GetTime()
{
	if(!pause)
	{
		if(timerType)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
			lastTime/=frequency; 
		}
		else 
		{
			lastTime = (double)timeGetTime();
			lastTime/=1000.0;
		}
	}
	return lastTime;
}

double timer::GetLastTime()
{
	return lastTime;
}

void timer::PauseTimer()
{
	pause = true;
}

void timer::StartTimer()
{
	pause = false;
}