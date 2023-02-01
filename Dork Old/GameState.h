#pragma once

#include "screen.h"
//#include "menu.h"
//#include "game.cpp"

#include "../ACRE Files/ACREngine.h"

enum states {MENU_STATE, GAME_STATE, OPTIONS_STATE, CREDITS_STATE, EXIT_STATE};

class GameState
{
private:
	unsigned int state;
	bool runLoop;

	//MenuData md;
	//gameData gd;

	//void menuStateActions();
	//void gameStateActions();

public:
	Area surface;
	ScreenData sd;

	GameState();
	void runStateActions();

	void startLoop();
	void stopLoop();
	bool getLoop();
};
