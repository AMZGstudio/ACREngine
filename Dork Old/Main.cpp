//#define FULLSCREEN
#define SHOW_FPS

#include "gameState.h"

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"


int main()
{
	GameState gd = GameState();

	initialize("Dork", 180, 110, 6, 6, Default, 234);
	setDefaultDrawArea(&gd.surface);

	while (gd.getLoop())
	{
		gd.runStateActions();
		
		drawNumber(0, 0, fps, EightBit, Red);

		gd.sd.drawScreen(gd.surface);
		if (key(Esc).pressed) gd.stopLoop();

		render(false);
	}
	return terminateACRE();
}










/*
When resizing occurs, it needs to be shown by a function like OnResize(), so i can resize the newArea buffer.

*/