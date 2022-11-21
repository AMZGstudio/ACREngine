//#define FULLSCREEN
#define SHOW_FPS

#include "screen.h"
#include "gameState.h"

#define ACRE_START
#include "../ACREngine.h"

#define ACRE_FONTS
#include "../ACRE_Fonts.h"

//#define ACRE_TRANSFORM
//#include "../ACRE_Transform.h"


int main()
{
	initalize("Dork", 180, 110, 6, 6, Default, 234);
	setDefaultDrawArea(&surface);

	gameState gs = { MENU_STATE };

	initalizeScreen(&sd);
	menuData md = initalizeMenu();
	gameData gd = initalizeGame();

	bool runGame = true;
	while (runGame)
	{
		clear(surface);

		switch (gs.state)
		{
		case MENU_STATE: menuStateActions(&gs, &md); break;
		case GAME_STATE: gameStateActions(&gd); break;
		case OPTIONS_STATE: sysDrawText(40, 40, surface, "OPTIONS", EightBit, Default, Yellow); break;
		case CREDITS_STATE: sysDrawText(40, 40, surface, "CREDS", EightBit, Default, Yellow); break;
		case EXIT_STATE: runGame = false;
		}
		drawNumber(0, 0, fps, EightBit, Red);

		drawScreen(&sd);
		if (key(Esc).pressed) runGame = false;
		render(false);
	}
	return terminateACRE();
}

/*
When resizing occurs, it needs to be shown by a function like OnResize(), so i can resize the newArea buffer.

*/