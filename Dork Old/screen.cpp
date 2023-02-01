#include "screen.h"

#define TIME_DEFAULT 3

ScreenData::ScreenData(Area& surface)
{
	surface = createArea(Width(Screen), Height(Screen), Default, Blue);
	fadeIncrement = TIME_DEFAULT;
	fadeEndTime = TIME_DEFAULT;
	fadeStartTime = 0;

	doFade = false;
	fadeEnd = false;
	fadeProgress = 0;
}


void ScreenData::drawScreen(Area surface)
{
	if (doFade)
	{
		if (fadeProgress < (fadeIncrement > 0) ? fadeEndTime: fadeStartTime)
			for (int i = 0; i < Width(Screen); i++)
				for (int j = 0; j < Height(Screen); j++)
				{
					short r, g, b;
					Xterm(surface.colBack[j * Width(Screen) + i], &r, &g, &b);
					sysDrawPoint(i, j, Screen, Default, Default, Color(clamp(r - map(fadeProgress, 0, 1, 0, 255), 0, 255), clamp(g - map(fadeProgress, 0, 1, 0, 255), 0, 255), clamp(b - map(fadeProgress, 0, 1, 0, 255), 0, 255)));
				}
		else
			drawRectFilled(0, 0, Width(surface), Height(surface), Black);

		fadeProgress += timePerSec(fadeIncrement);
		if (fadeProgress > (fadeIncrement > 0) ? fadeEndTime : fadeStartTime)
			doFade = false, fadeEnd = true, fadeProgress = 0;
	}
	else// if(!s->fadeEnd)
	{
		sysDrawArea(0, 0, Screen, surface);
		if (fadeEnd == true)
			fadeEnd = false;
	}
}

void ScreenData::startFade()
{
	fadeEnd = false;
	doFade = true, fadeProgress = 0;
	fadeStartTime = 0;

	fadeEndTime = TIME_DEFAULT;
	fadeIncrement = TIME_DEFAULT;
}

void ScreenData::startReverseFade()
{
	fadeEnd = false;
	doFade = true, fadeProgress = TIME_DEFAULT;
	fadeStartTime = TIME_DEFAULT;
	fadeEndTime = 0;
	fadeIncrement = -TIME_DEFAULT;
}

int ScreenData::cmSpace(float cameraPos, float pos) // can be used for x, or y
{
	float npos = pos - (int)cameraPos + (cameraPos < 0 ? 1 : 0);
	if (npos < 0 && npos < (int)npos) // if the value is in negative domain, then if there is any floating point numbers, add -1.
		return (int)npos - 1;
	return npos;
}