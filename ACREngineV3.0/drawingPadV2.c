#define ACRE_START
#include "ACREngine.h"

int main()
{
	initalize("Drawing Pad", 50, 30, 8, 16, White, Cyan);

	float x = 0, y = 0;
	short color = Blue;

	Area pad = createArea(48, 20, Default, White);

	while (true)
	{
		drawArea(1, 1, pad);
		
		if (key(Up).held) y -= timePerSec(5);
		if (key(Down).held) y += timePerSec(5);
		if (key(Left).held) x -= timePerSec(5);
		if (key(Right).held) x += timePerSec(5);
		if (key(E).held) sysDrawPoint(x, y, pad, Default, Default, color);

		x = clamp(x, 0, Width(pad)-1);
		y = clamp(y, 0, Height(pad)-1);

		for (int k = Num1; k < Num9; k++)
			if (key(k).pressed) color = k - Num1;

		drawPixel(x + 1, y + 1, Yellow);
		drawText(1, 22, "Welcome to the drawing Pad!\nUse WASD keys to move, and press E to draw!\nThese are the colors you can use:\n\n  1    2    3    4    5    6    7", DefaultFont, White);
		drawChar(38, 26, '8', Black);

		for (int x = 0; x < 8; x++)
			drawRectFilled(map(x, 0, 7, 1, 40), 25, map(x, 0, 7, 1, 40) + 5, 28, Black + x);

		render(true);
	}
	return terminate();
}

// 22 less lines than in v1.