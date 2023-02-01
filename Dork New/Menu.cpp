#include "Menu.h"

void Menu::optionCalculations(Area surface)
{
	int round = 0, y = tv.y + tv.area.height * tv.zoom + 5;
	bool leftMPressed = key(LeftM).pressed;

	for(Option o : options)
	{
		int strLen = (stringWidth(o.text.c_str(), EightBit) + 1);

		Space s = drawText(Centered, y, o.text.c_str(), EightBit, DarkGrey);
		drawText(s.startX - 1, s.startY - 1, o.text.c_str(), EightBit, Color(o.r, o.g, o.b));

		if (leftMPressed && pointSpaceCollide(Mouse.x, Mouse.y, s))
		{
			//if (selectedOption == round)
				//startFade(&sd);

			selectedOption = round, options[selectedOption].b = 120, options[selectedOption].g = 120, options[selectedOption].fading = true;
		}

		if (round == selectedOption)
		{
			drawArea(s.startX - 10, y, pointer);
			flipArea(pointer);
			drawArea(s.endX + 2, y, pointer);
			flipArea(pointer);
		}
		y += 10, round++;
	}

	int selB = selectedOption;
	if ((key(S).pressed || key(Down).pressed) && selectedOption < options.size() - 1) selectedOption += 1;
	if ((key(W).pressed || key(Up).pressed) && selectedOption > 0) selectedOption -= 1;

	if (selB != selectedOption)
	{
		options[selectedOption].b = 120; options[selectedOption].g = 120;
		options[selectedOption].fading = true;
	}

	for (Option& o : options)
	{
		o.b += timePerSec(630);
		o.g += timePerSec(630);

		o.b = clamp(o.b, 0, 255);
		o.g = clamp(o.b, 0, 255);
	}
}

void Menu::cloudsCalculations(Area surface)
{
	for(Cloud& c : clouds)
	{
		float rcx = c.x >= 0 ? map(c.x, 0, 240, 0, Width(Screen)) : c.x;
		float rcy = c.y >= 0 ? map(c.y, 0, 135, 0, Height(Screen)) : c.y;

		drawArea(rcx, rcy, c.sprite);
		c.x += timePerSec(c.vx);

		if (map(c.x, 0, 240, 0, Width(surface)) > Width(surface))
			c.x = 0 - c.sprite.width;
	}
}

void Menu::menuCalculations(Area surface)
{
	tv.x = Width(Screen) / 2 - (stringWidth(title.c_str(), EightBit) * tv.zoom) / 2;
	tv.y = Height(Screen) / 2 - MENU_H / 2;

	cloudsCalculations(surface);
	optionCalculations(surface);

	drawAT(tv);
}

Menu::Menu(Area surface)
{
	pointer = loadSprite("../ACRE Sprites/pointer.acre");
	cloud1 = loadSprite("../ACRE Sprites/cloud1.acre");
	cloud2 = loadSprite("../ACRE Sprites/cloud2.acre");

	options.push_back({ "Start" });
	options.push_back({ "Options" });
	options.push_back({ "Credits" });
	options.push_back({ "Exit" });

	clouds.push_back({ cloud1, -5, 0,  7 });
	clouds.push_back({ cloud1, 64, 102,6 });
	clouds.push_back({ cloud1, 149,69, 7 });
	clouds.push_back({ cloud1, 14, 70,10 });
	clouds.push_back({ cloud1, 145,125,7 });

	clouds.push_back({ cloud2, 50, 34, 9 });
	clouds.push_back({ cloud2, 160,24, 5 });
	clouds.push_back({ cloud2, 207,95,10 });
	clouds.push_back({ cloud2, 220,-2, 4 });
	clouds.push_back({ cloud2, 225,58, 5 });

	splashScreen = createArea(stringWidth(title.c_str(), EightBit), 8, Default, Default);
	tv = createAT(splashScreen, 0, 0);

	sysDrawText(1, 1, splashScreen, title.c_str(), EightBit, Default, VeryDarkGrey);
	sysDrawText(0, 0, splashScreen, title.c_str(), EightBit, Default, White);

	tv.zoom = 3;
	tv = tv;
}