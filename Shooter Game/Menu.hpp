#pragma once

#define FONT_USED Five
class Menu : public acre::State
{
private:
	acre::Menu menu;
	acre::Fade f;

	int index;
	
public:
	Menu(acre::Renderer* ar) : f(ar), menu(FONT_USED, calcSpace(ScreenSpace, Centered, Centered, 100, 60))
	{
		menu.addOption("Play Game", Centered, Default);
		menu.addOption("Leaderboard", Centered, Default);
		menu.addOption("Credits", Centered, Default);
		menu.addOption("Exit", Centered, Default);

		std::string title = "Zombie Shooter";

		Area area = createArea(txtWidth(title.c_str(), FONT_USED) + 1, FONT_USED.height + 1, Default, Default);
		sysDrawText(1, 1, area, title.c_str(), FONT_USED, Default, DarkGrey);
		sysDrawText(0, 0, area, title.c_str(), FONT_USED, Default, White);

		menu.setArea(area, Centered, 20, 3);
		index = -1;
	}

	void initalizer() override {}

	void runState() override
	{
		drawRect(Centered, Centered, Width(Screen) - 4, Height(Screen) - 4, DarkGrey);

		menu.draw();
		menu.calculations();

		f.fadeOutIfNecessary();
		if (f.fadeInFinished())
		{
			switch (index)
			{
			case 0: setState("game"); break;
			case 1: setState("board"); break;
			case 2: setState("creds"); break;
			case 3: _currState->stopRunning(); break;
			}
			menu.deselectOptions();
		}
		
		if (menu.pressed() && f.notFading())
		{
			index = menu.indexPressed();
			f.fadeIn();
		}
	}
};

