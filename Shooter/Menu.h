#pragma once
#include "State.h"

class Menu : public State
{
public:
	int runState() override
	{
		drawText(Centered, 20, "Zombie Shooter!", EightBit, White);

		if (key(Enter).pressed)
			return game;

		return menu;
	}
};

