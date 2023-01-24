#pragma once
#include "State.hpp"

class Over : State
{
private:

public:
	int runState() override
	{
		drawText(Centered, 30, "GAME OVER!", EightBit, Red);
		drawText(Centered, 50, std::format("Score: {}", Game::score).c_str(), Pzim, White);

		if (key(Spacebar).pressed)
			return game;

		return over;
	}
};

