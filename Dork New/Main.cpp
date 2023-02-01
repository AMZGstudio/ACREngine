//#define FULLSCREEN
#define SHOW_FPS

#include "SharedData.h"

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"

#include "Menu.h"


int main()
{
	initialize("Dork", 180, 110, 6, 6, Default, Blue);

	SharedData s = SharedData();
	Menu m = Menu(s.surface);

	setDefaultDrawArea(&s.surface);

	while (s.isRunning())
	{
		switch (s.getState())
		{
			case MENU_STATE: m.menuCalculations(s.surface); break;
			case GAME_STATE: /*gameStateActions();*/ break;
			case OPTIONS_STATE: sysDrawText(40, 40, s.surface, "OPTIONS", EightBit, Default, Yellow); break;
			case CREDITS_STATE: sysDrawText(40, 40, s.surface, "CREDS", EightBit, Default, Yellow); break;
			case EXIT_STATE: s.setRunning(false);
		}
		if (key(Esc).pressed) s.setRunning(false);

		drawNumber(0, 0, fps, EightBit, Red);
		sysDrawArea(0, 0, Screen, s.surface);

		clear(s.surface);
		render(false);
	}

	return terminateACRE();
}










/*
When resizing occurs, it needs to be shown by a function like OnResize(), so i can resize the newArea buffer.

*/