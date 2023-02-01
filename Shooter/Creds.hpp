#pragma once

class Creds : acre::State
{
private:
	acre::Fade f;
	Font currFont;
	acre::Menu m;

public:
	Creds(acre::Renderer* r) : f(r), m(Pzim, calcSpace(ScreenSpace, Centered, Height(Screen)-30, 80, 20), false)
	{ 
		currFont = Pzim; currFont.spacingY = 2;
		m.addOption("Go back", Centered, Default);
	}
	void initalizer() override {}
	
	void runState() override
	{
		f.fadeOutIfNecessary();
		if (f.fadeInFinished())
			setState("menu");
		
		m.draw();
		m.calculations();

		if (m.pressed() && f.notFading())
			f.fadeIn();

		drawRect(Centered, Centered, Width(Screen) - 4, Height(Screen) - 4, DarkGrey);

		drawText(Centered, Height(Screen) - 10, "ACREngineV3.0", Pzim, Grey);
		drawText(Centered, 20, "Credits!", Five, White);
		drawText(Centered, 40, "This Game is a demo game\nmade by AMZG on github.\nFor more information...\n\n         go to:", 
		currFont, White);

		Space s = drawText(Centered, 80, "https://github.com/AMZGstudio/ACREngine", Pzim, Blue);
		if (pointSpaceCollide(Mouse.x, Mouse.y, s))
		{
			drawText(Centered, 80, "https://github.com/AMZGstudio/ACREngine", Pzim, LightBlue);
			if (key(LeftM).held)
				ShellExecuteA(0, 0, "https://github.com/AMZGstudio/ACREngine", 0, 0, SW_SHOW);
		}

	}
};

