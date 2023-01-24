#pragma once
#include "State.h"

class Over : State
{
	int runState() override
	{
		drawText(Centered, 30, "GAME OVER!", EightBit, Red);

		if (key(Spacebar).pressed)
			return game;

		return over;
	}
};

