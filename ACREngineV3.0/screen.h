#pragma once
#include "../ACREngine.h"

typedef struct screenData {
	float fadeProgress;
	float fadeIncrement;
	float fadeEndTime;
	float fadeStartTime;
	bool doFade;
	bool fadeEnd;
	Area area;
} screenData;

screenData initalizeScreen();
void drawScreen(screenData* s);
void startFade(screenData* s);
void startReverseFade(screenData* s);
