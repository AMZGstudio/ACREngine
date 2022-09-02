#include "screen.h"

#define TIME_DEFAULT 3

void initalizeScreen(screenData* s)
{
	surface = createArea(Width(Screen), Height(Screen), Default, Blue);
	s->fadeIncrement = TIME_DEFAULT;
	s->fadeEndTime = TIME_DEFAULT;
	s->fadeStartTime = 0;

	s->doFade = false;
	s->fadeEnd = false;
	s->fadeProgress = 0;

	return s;
}

void drawScreen(screenData* s)
{
	if (s->doFade)
	{
		if (s->fadeProgress < (s->fadeIncrement > 0) ? s->fadeEndTime: s->fadeStartTime)
			for (int i = 0; i < Width(Screen); i++)
				for (int j = 0; j < Height(Screen); j++)
				{
					short r, g, b;
					Xterm(surface.colBack[j * Width(Screen) + i], &r, &g, &b);
					sysDrawPoint(i, j, Screen, Default, Default, Color(clamp(r - map(s->fadeProgress, 0, 1, 0, 255), 0, 255), clamp(g - map(s->fadeProgress, 0, 1, 0, 255), 0, 255), clamp(b - map(s->fadeProgress, 0, 1, 0, 255), 0, 255)));
				}
		else
			drawRectFilled(0, 0, Width(surface), Height(surface), Black);

		s->fadeProgress += timePerSec(s->fadeIncrement);
		if (s->fadeProgress > (s->fadeIncrement > 0) ? s->fadeEndTime : s->fadeStartTime)
			s->doFade = false, s->fadeEnd = true, s->fadeProgress = 0;
	}
	else// if(!s->fadeEnd)
	{
		sysDrawArea(0, 0, Screen, surface);
		if (s->fadeEnd == true)
			s->fadeEnd = false;
	}
}

void startFade(screenData* s)
{
	s->fadeEnd = false;
	s->doFade = true, s->fadeProgress = 0;
	s->fadeEndTime = TIME_DEFAULT, s->fadeStartTime = 0;
	s->fadeIncrement = TIME_DEFAULT;
}

void startReverseFade(screenData* s)
{
	s->fadeEnd = false;
	s->doFade = true, s->fadeProgress = TIME_DEFAULT;
	s->fadeStartTime = TIME_DEFAULT;
	s->fadeEndTime = 0;
	s->fadeIncrement = -TIME_DEFAULT;
}