#pragma once

#include "../ACRE Files/ACREngine.h"
#include "../ACRE Files/ACRE_Fonts.h"
#include "../ACRE Files/ACRE_Transform.h"

#define MENU_H 72
#define NUM_OPS 4
#define NUM_CLDS 10

#define DW 240
#define DH 240


typedef struct option {
	char* text;
	float colorR, colorG, colorB;
	bool fading;
} option;

typedef struct cloud {
	Area sprite;
	float x, y;
	float vx;
} cloud;

class MenuData {

public:
	AreaTrans tv;

	int selectedOption;
	char* title;

	cloud clouds[NUM_CLDS];
	Area pointer;

	option ops[NUM_OPS];
	Area dune;
	Area dune2;

public:
	void optionCalculations();
	void cloudsCalculations();
	void menuCalculations(Area surface);

	MenuData();
};