#define SHOW_FPS
#define FULLSCREEN
#define ACRE_START
#include "ACREngine.h"

int main()
{
	initalize("Eitan Game", 200, 120, 5, 5, Default, Default);
	Image img = loadImage("C:/Uriel/birdUp.acre");

	while (!key(Esc).pressed)
	{
		drawNumber(0, 0, fps, EightBit, Red);
		drawImage(Mouse.x, Mouse.y, img);
		render(true);
	}
	return terminate();
}