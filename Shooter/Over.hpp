#pragma once
#include "Leaderboard.hpp"

class Over : acre::State
{
private:
	Leaderboard lb;
	acre::Fade f;
	acre::Menu m;
	Area area;

	std::string title = "Game Over!";

	char output[100] = { 0 };
	bool enterInput = true;

	float timePassed = -2;
	bool inc = true;

public:
	Over(acre::Renderer* r) : f(r), m(Pzim, calcSpace(ScreenSpace, Centered, Height(Screen)-20, 80, 20)), lb(calcSpace(ScreenSpace, Centered, 60, 80, 40))
	{
		area = createArea(txtWidth(title.c_str(), FONT_USED) + 1, FONT_USED.height + 1, Default, Default);
		sysDrawText(1, 1, area, title.c_str(), FONT_USED, Default, DarkGrey);		
		
		m.setArea(area, Centered, 20, 3);
		m.addOption("Go back", Centered, Default);
	}

	void initalizer() override
	{
		for (int i = 0; i < 100; i++)
			output[i] = 0;

		enterInput = true;
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

		timePassed += inc ? timePerSec(5) : -timePerSec(5);

		if (timePassed > 1) inc = false;
		if (timePassed < 0) inc = true;

		int col = map(timePassed, 0, 1, 0, 255);
		sysDrawText(0, 0, area, title.c_str(), FONT_USED, Default, Color(clamp(128 + col, 0, 255), clamp(col, 0, 255), clamp(col, 0, 255)));

		m.drawArea();

		drawRect(Centered, Centered, Width(Screen) - 4, Height(Screen) - 4, DarkGrey);
		drawText(Centered, 40, std::format("Score: {}", Game::score).c_str(), Pzim, White);

		if (enterInput)
			if (textBoxInput(output, 100))
			{
				drawText(Centered, 60, "Enter your name: ", Pzim, White);
				drawText(Centered, 70, output, Pzim, White);
			}
			else
			{
				enterInput = false;

				if (strlen(output) <= 0) return;

				lb.leaderboard.insert(std::pair<std::string, int>(output, Game::score));
				lb.saveLeaderboard();
			}

		else
		{
			lb.draw();
			m.drawOptions();
			m.calculations();

			if (m.pressed())
				f.fadeIn();
		}
		
		if (key(Esc).pressed)
			f.fadeIn();
	}
};

