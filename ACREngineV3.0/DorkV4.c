#define FULLSCREEN
#define SHOW_FPS
#define ACRE_START
//#define ALLOW_WINDOW_RESIZE
#include "../ACREngine.h"

#define ACRE_FONTS
#include "../ACRE_Fonts.h"

#define ACRE_TRANSFORM
#include "../ACRE_Transform.h"

#include "screen.h"
#include "menu.h"

int main()
{
	initalize("Dork", 200, 110, 8, 8, Default, Blue);
	
	screenData sd = initalizeScreen();
	menuData md = initalizeMenu(&sd);

	while (!key(Esc).pressed)
	{
		clear(sd.area);
		menuCalculations(&md);

		if (key(Enter).pressed) sd.doFade = true, sd.fadeProgress = 0;
		
		drawScreen(&sd);
		drawNumber(0, 0, fps, EightBit, Red);
		render(true);
	}
	return terminate();
}

/*
When resizing occurs, it needs to be shown by a function like OnResize(), so i can resize the newArea buffer.

*/