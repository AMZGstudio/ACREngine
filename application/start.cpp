#define ACRE_START
#define ACRE_SHOW_FPS
#include "../acre files/ACREngine.h"

// This is the entry point -- have fun! :)
void start()
{
	initialize("Demo", 150, 80, 4, 4, Default, Default);

	while (true)
	{
		drawText(Centered, Centered, "ACREngine!", EightBit, White);
		
		drawPixel(Mouse.x, Mouse.y, Red);

		render(true);
	}
}
