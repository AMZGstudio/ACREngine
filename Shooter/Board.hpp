#pragma once

#include "Leaderboard.hpp"

class Board : public acre::State
{
private:
	Leaderboard lb;
	acre::Fade f;

	acre::Menu m;

public:
	Board(acre::Renderer* r) : m(Pzim, calcSpace(ScreenSpace, Centered, Height(Screen) - 20, 80, 20)), f(r), lb(calcSpace(ScreenSpace, Centered, 30, 80, 40))
	{
		m.addOption("Go back", Centered, Default);
	}

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

		m.drawOptions();
		m.calculations();

		if (m.pressed() && f.notFading())
			f.fadeIn();

		drawRect(Centered, Centered, Width(Screen) - 4, Height(Screen) - 4, DarkGrey);
		lb.draw();
	}
};