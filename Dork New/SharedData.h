#pragma once

#include "../ACRE Files/ACREngine.h"

enum states { MENU_STATE, GAME_STATE, OPTIONS_STATE, CREDITS_STATE, EXIT_STATE };

class SharedData
{
private:
	unsigned int state = MENU_STATE;
	bool runLoop = true;

public:
	Area surface;
	unsigned int getState() const;
	void setState(unsigned int state);

	bool isRunning() const;
	void setRunning(bool run);

	SharedData();

};

