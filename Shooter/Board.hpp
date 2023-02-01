#pragma once

#include "Leaderboard.hpp"

class Board : public acre::State
{
private:
	Leaderboard lb;
	acre::Fade f;

public:
	Board(acre::Renderer* r) : f(r), lb(calcSpace(ScreenSpace, Centered, 30, 80, 40)) {}

	void initalizer() override
	{
		lb.loadLeaderboard();
	}

	void runState() override
	{
		f.fadeOutIfNecessary();
		if (f.fadeInFinished())
		{
			setState("menu");
			reset();
		}

		if (key(Esc).held && f.notFading())
			f.fadeIn();

		drawRect(Centered, Centered, Width(Screen) - 4, Height(Screen) - 4, DarkGrey);
		lb.draw();
	}
};