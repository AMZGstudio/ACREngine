#define SHOW_FPS
#define FULLSCREEN

#define ACRE_START
#include "ACREngine.h"

#define ACRE_TRANSFORM
#include "ACRE_transform.h"

int main()
{
	initalize("New Version!", 280, 160, 6, 6, Default, DarkGrey);
	Image img = loadImage("C:/Uriel/harry.acre");
	
	AreaTrans a = createAreaTrans(img.imgData);
	a.x = Width(Screen) / 2, a.y = Height(Screen) / 2;

	while (!key(Esc).pressed)
	{
		drawAreaTransformed(a, Screen);
		areaCalculations(&a);

		drawNumber(0, 0, fps, EightBit, White);
		render(true);
	}
	deleteArea(&img.imgData);
	return terminate();
}