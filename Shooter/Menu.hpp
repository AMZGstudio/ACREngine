#pragma once
#include "State.hpp"

class Menu : public State
{
public:
	void runState(std::string& state) override
	{
		drawText(Centered, 20, "Zombie Shooter!", EightBit, White);

		if (key(Enter).pressed)
			state = "game";
	}
};

