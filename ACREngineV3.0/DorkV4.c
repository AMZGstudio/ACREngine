//#define FULLSCREEN
#define SHOW_FPS
#define ACRE_START
#include "../ACREngine.h"

#define ACRE_FONTS
#include "../ACRE_Fonts.h"

#define ACRE_TRANSFORM
#include "../ACRE_Transform.h"

#include "gameState.h"
#include "screen.h"

int main()
{
	initalize("Dork", 180, 110, 6, 6, Default, Blue);
	
	gameState gs = { MENU_STATE };

	screenData sd = initalizeScreen();
	menuData md = initalizeMenu(&sd);
	gameData gd = initalizeGame(&sd);

	bool runGame = true;
	while (runGame)
	{
		clear(sd.area);

		switch (gs.state)
		{
		case MENU_STATE: menuStateActions(&gs, &md); break;
		case GAME_STATE: gameStateActions(&gd); break;
		case OPTIONS_STATE: sysDrawText(40, 40, sd.area, "OPTIONS", EightBit, Default, Yellow); break;
		case CREDITS_STATE: sysDrawText(40, 40, sd.area, "CREDS", EightBit, Default, Yellow); break;
		case EXIT_STATE: runGame = false;
		}
		
		drawScreen(&sd);
		//drawNumber(0, 0, fps, EightBit, Red);
		render(true);
	}
	return terminate();
}

/*
When resizing occurs, it needs to be shown by a function like OnResize(), so i can resize the newArea buffer.

*/