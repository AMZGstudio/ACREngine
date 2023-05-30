#define ACRE_START
#define SHOW_FPS
#include "ACREngine.h"

int main()
{
	initalize("Test", 200, 100, 6, 6, Default, Default);

	Image img = loadImage("C:/Uriel/thing.acre");
	float x = 0;
	while (true)
	{
		drawImage(x, Centered, img);

		x += timePerSec(50);

		if (x > Width(Screen)) x = 0;

		render(true);
	}
	return terminate();
}