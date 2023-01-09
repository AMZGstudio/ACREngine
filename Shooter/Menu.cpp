#include "Menu.h"

int Menu::runState()
{
	drawCircleFilled(50, 50, 3, Red);
	drawText(Centered, 20, "my game", EightBit, White);

	if (key(Enter).pressed)
		return game;

	return menu;
}
