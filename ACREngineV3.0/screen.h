#pragma once
#include "../ACREngine.h"

typedef struct screenData {
	float fadeProgress;
	bool doFade;

	Area area;
} screenData;

screenData initalizeScreen();
void drawScreen(screenData* s);