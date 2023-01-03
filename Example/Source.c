#define SHOW_FPS
#define FULLSCREEN

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"

#define ACRE_GUI
#include "../ACRE Files/ACRE_Gui.h"

int main()
{
	// start ACRE engine
	initalize("New Version!", 190, 105, 7, 7, Default, VeryDarkGrey);

	Window* w = createWindow(2, 2, 25, 60, "Controls", true);
	Option* b1 = createButton(w, Centered, 3, 13, 8, "Zoom In");
	Option* b2 = createButton(w, Centered, 10, 13, 15, "Zoom Out");

	// create AreaTrans (in ACRE_Transform), with a loaded sprite, and center x, y coords.
	Area spr = loadSprite("../ACRE Sprites/harry.acre");
	AreaTrans at = createAT(spr, Width(Screen) / 2 - Width(spr) / 2, Height(Screen) / 2 - Height(spr) / 2);

	while (!key(Esc).pressed)
	{		
		if(!calculateWindow(w))
			calculateAT(&at);

		if (calculateButton(b1))
			changeZoom(&at, Width(Screen)/2, Height(Screen)/2, 1.02);
		if(calculateButton(b2))
			changeZoom(&at, Width(Screen)/2, Height(Screen)/2, 0.98);

		drawAT(at);
		drawWindow(w, true);
		drawButton(b1, true);
		drawButton(b2, true);

		render(true);
	}
	deleteArea(spr);

	return terminateACRE();
}