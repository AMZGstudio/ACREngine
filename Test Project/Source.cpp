#define ACRE_START
#include "../ACREngine.h"

int main()
{
	initalize("Demo", 200, 100, 5, 5, Default, Default);

	while (true)
	{
		drawText(Centered, 2, "Hello!", EightBit, White);
		drawRect(Mouse.x, Mouse.y, Mouse.x + 20, Mouse.y + 20, Red);

		render(true);
	}

	terminateACRE();
}