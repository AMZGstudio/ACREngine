#define SHOW_FPS
//#define FULLSCREEN

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"

#define ACRE_GUI
#include "../ACRE Files/ACRE_Gui.h"

int main()
{
	// start ACRE engine
	initalize("New Version!", 280, 160, 4, 4, Default, DarkGrey

	// load sprite
	Area spr = loadSprite("../ACRE Sprites/harry.acre");

	// create AreaTrans (in ACRE_Transform), with the loaded sprite, and center x, y coords.
	AreaTrans at = createAT(spr, Width(Screen) / 2, Height(Screen) / 2);

	while (!key(Esc).pressed)
	{
		// draw the area, on the screen
		drawAT(at);
		calculateAT(&at);

		drawNumber(0, 0, fps, EightBit, White);
		render(true);
	}
	deleteArea(spr);

	return terminateACRE();
}