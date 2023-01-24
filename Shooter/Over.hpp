#pragma once
#include "State.hpp"

class Over : State
{
private:

public:
	void runState(std::string& state) override
	{
		drawText(Centered, 30, "GAME OVER!", EightBit, Red);
		drawText(Centered, 50, std::format("Score: {}", Game::score).c_str(), Pzim, White);

		if (key(Enter).pressed)
			state = "game";
	}
};

