#define ACRE_START
#define SHOW_FPS
#include "ACREngine.h"

int main()
{
	initalize("Demo", 320, 240, 3,3, White, Blue);
	bool startCounting = false;
	float allTime = 0;
	int amntFrames = 0;

	while (true)
	{
		drawPoint(Mouse.x, Mouse.y, Yellow);

		if (startCounting == true)
			allTime += deltaTime, amntFrames++;

		if (amntFrames > 0)
			drawNumber(Centered, Centered, 1 / (allTime / (float)amntFrames), EightBit, Default);
		
		if (key(S).pressed)
			startCounting = true;
		if (key(T).pressed)
			startCounting = false;

		render(true);
	}
	return terminate();
}
