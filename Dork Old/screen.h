#pragma once

#include "../ACRE Files/ACREngine.h"

class ScreenData
{
public:
	float fadeProgress;
	float fadeIncrement;
	float fadeEndTime;
	float fadeStartTime;
	bool doFade;
	bool fadeEnd;
	
	ScreenData(Area& surface);

	int cmSpace(float cameraPos, float pos);
	
	void drawScreen(Area surface);
	void startFade();
	void startReverseFade();
};


