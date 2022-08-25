//#define FULLSCREEN
#define SHOW_FPS
#define ACRE_START
//#define ALLOW_WINDOW_RESIZE
#include "../ACREngine.h"

#define ACRE_FONTS
#include "../ACRE_Fonts.h"

#define ACRE_TRANSFORM
#include "../ACRE_Transform.h"

#include "gameState.h"
#include "screen.h"

int main()
{
	initalize("Dork", 200, 110, 6, 6, Default, Blue);
	
	gameState gd = { MENU_STATE };
	screenData sd = initalizeScreen();
	menuData md = initalizeMenu(&sd);

	bool gameStart = false;
	while (!key(Esc).pressed)
	{
		clear(sd.area);

		switch (gd.state)
		{
		case MENU_STATE: menuStateActions(&gd, &md); break;
		case GAME_STATE: sysDrawText(40, 40, sd.area, "TEXT HERE", EightBit, Default, Yellow); break;
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