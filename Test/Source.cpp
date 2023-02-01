#define SHOW_FPS
#define ALL_FONTS

#define ACRE_START
#include "../ACRE Files/ACREngine.h"


int main()
{
	initialize("Shooter Game!", 300, 200, 3, 3, Default, Default);

	while (true)
	{
		if (key(W).held)
			drawPixel(Mouse.x, Mouse.y, Red);

		if (key(R).held)
			sysDrawPoint(Mouse.x, Mouse.y, Screen, Default, Default, Default);
			//drawPixel(Mouse.x, Mouse.y, defaultBackColor);

		render(false);
	}
	return terminateACRE();
}

