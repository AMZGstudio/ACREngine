#pragma once
#include "../ACREngine.h"

Area surface;

typedef struct screenData {
	float fadeProgress;
	float fadeIncrement;
	float fadeEndTime;
	float fadeStartTime;
	bool doFade;
	bool fadeEnd;
} screenData;

screenData sd;

int cmSpace(float cameraPos, float pos);
void initalizeScreen(screenData* s);
void drawScreen(screenData* s);
void startFade(screenData* s);
void startReverseFade(screenData* s);