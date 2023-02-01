#pragma once

#include "../ACRE Files/ACREngine.h"
#include "../ACRE Files/ACRE_Fonts.h"
#include "../ACRE Files/ACRE_Transform.h"
#include "../ACRE Files/ACRE_Gameplay.h"

#include <vector>
#include <string>

#define DW 240
#define DH 240
#define MENU_H 72

struct Option {
	std::string text;
	float r = 255, g = 255, b = 255;
	bool fading = false;
};

struct Cloud {
	Area& sprite;
	float x, y, vx;
};

class Menu {

private:
	std::vector<Cloud> clouds;
	std::vector<Option> options;

	AreaTrans tv;

	int selectedOption = 0;
	std::string title = "DORK";

	Area pointer;
	Area cloud1, cloud2;
	Area splashScreen;

public:
	void optionCalculations(Area surface);
	void cloudsCalculations(Area surface);
	void menuCalculations(Area surface);

	Menu(Area surface);
};