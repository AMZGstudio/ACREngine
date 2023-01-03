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
	initalize("New Version!", 190, 105, 6, 6, Default, VeryDarkGrey);

	Window* w = createWindow(2, 2, 40, 60, "Properties", true);
	
	Option* b = createButton(w, 2, 2, 10, 6, "But");

	// load sprite
	Area spr = loadSprite("../ACRE Sprites/harry.acre");

	// create AreaTrans (in ACRE_Transform), with the loaded sprite, and center x, y coords.
	AreaTrans at = createAT(spr, Width(Screen) / 2, Height(Screen) / 2);

	while (!key(Esc).pressed)
	{
		if(!calculateWindow(w))
			calculateAT(&at);

		calculateButton(b);

		drawAT(at);
		drawWindow(w, true);
		drawButton(b, true);

		render(true);
	}
	deleteArea(spr);

	return terminateACRE();
}