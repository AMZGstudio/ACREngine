#include "menu.h"

void MenuData::optionCalculations()
{
	int y = tv.y + tv.area.height * tv.zoom + 5;
	Area ar = surface;
	bool leftMPressed = key(LeftM).pressed;

	for (int i = 0; i < NUM_OPS; i++)
	{
		int strLen = (stringWidth(m->ops[i].text, EightBit) + 1);

		Space s = drawText(Centered, y + i * 10, m->ops[i].text, EightBit, DarkGrey);
		drawText(s.startX - 1, s.startY - 1, m->ops[i].text, EightBit, Color(m->ops[i].colorR, m->ops[i].colorG, m->ops[i].colorB));

		if (leftMPressed && pointSpaceCollide(Mouse.x, Mouse.y, s))
		{
			if (m->selectedOption == i)
				startFade(&sd);

			m->selectedOption = i, m->ops[m->selectedOption].colorB = 120, m->ops[m->selectedOption].colorG = 120, m->ops[m->selectedOption].fading = true;
		}

		if (i == m->selectedOption)
		{
			drawArea(s.startX - 10, y + i * 10, m->pointer);
			flipArea(m->pointer);
			drawArea(s.endX + 2, y + i * 10, m->pointer);
			flipArea(m->pointer);
		}
	}
	int selB = m->selectedOption;
	if ((key(S).pressed || key(Down).pressed) && m->selectedOption < NUM_OPS - 1) m->selectedOption += 1;
	if ((key(W).pressed || key(Up).pressed) && m->selectedOption > 0) m->selectedOption -= 1;

	if (selB != m->selectedOption)
	{
		m->ops[m->selectedOption].colorB = 120; m->ops[m->selectedOption].colorG = 120;
		m->ops[m->selectedOption].fading = true;
	}

	for (int i = 0; i < NUM_OPS; i++)
	{
		m->ops[i].colorB += timePerSec(630);
		m->ops[i].colorG += timePerSec(630);

		m->ops[i].colorB = clamp(m->ops[i].colorB, 0, 255);
		m->ops[i].colorG = clamp(m->ops[i].colorG, 0, 255);
	}
}

void MenuData::cloudsCalculations()
{
	for (int i = 0; i < NUM_CLDS; i++)
	{
		float rcx = m->clouds[i].x >= 0 ? map(m->clouds[i].x, 0, 240, 0, Width(Screen)) : m->clouds[i].x;
		float rcy = m->clouds[i].y >= 0 ? map(m->clouds[i].y, 0, 135, 0, Height(Screen)) : m->clouds[i].y;

		drawArea(rcx, rcy, m->clouds[i].sprite);
		m->clouds[i].x += timePerSec(m->clouds[i].vx);

		if (map(m->clouds[i].x, 0, 240, 0, Width(surface)) > Width(surface))
			m->clouds[i].x = 0 - m->clouds[i].sprite.width;
	}
}

void MenuData::menuCalculations(Area surface)
{
	tv.x = Width(Screen) / 2 - (stringWidth(title, EightBit) * tv.zoom) / 2;
	tv.y = Height(Screen) / 2 - MENU_H / 2;

	drawArea(0, Height(Screen) - Height(dune2), dune2);
	drawArea(Width(dune2), Height(Screen) - Height(dune2), dune2);

	optionCalculations(); 	//cloudsCalculations(m);

	drawAreaTransformed(tv, surface);
}

MenuData::MenuData()
{
	dune = loadSprite("../Sprites/dunes2.acre");
	dune2 = loadSprite("../Sprites/dunes3.acre");

	selectedOption = 0;
	pointer = loadSprite("../Sprites/pointer.acre");

	option op1 = { (char*)"Start", 255, 255, 255, false };
	option op2 = { (char*)"Options", 255, 255, 255, false };
	option op3 = { (char*)"Credits", 255, 255, 255, false };
	option op4 = { (char*)"Exit", 255, 255, 255, false };
	option ops[NUM_OPS] = { op1, op2, op3, op4 };

	Area cl1 = loadSprite("../Sprites/cloud1.acre");
	Area cl2 = loadSprite("../Sprites/cloud2.acre");

	cloud c1 = { cl1, -5, 0, 7 }, c2 = { cl2, 50, 34, 9 }, c3 = { cl1, 64, 102, 6 };
	cloud c4 = { cl1, 14, 70,10 }, c5 = { cl2, 160, 24, 5 }, c6 = { cl1, 149, 69, 7 };
	cloud c7 = { cl2, 207, 95, 10 }, c8 = { cl2, 220, -2, 4 }, c9 = { cl1, 145, 125, 7 };
	cloud c10 = { cl2, 225, 58, 5 };

	cloud clouds[NUM_CLDS] = { c1, c2, c3, c4, c5, c6, c7, c8, c9, c10 };

	for (int i = 0; i < NUM_CLDS; i++)
		clouds[i] = clouds[i];
	for (int i = 0; i < NUM_OPS; i++)
		ops[i] = ops[i];

	title = (char*)"DORK";
	Area splashScreen = createArea(stringWidth(title, EightBit), 8, Default, Default);
	AreaTrans tv = createAreaTrans(splashScreen);

	sysDrawText(1, 1, splashScreen, title, EightBit, Default, VeryDarkGrey);
	sysDrawText(0, 0, splashScreen, title, EightBit, Default, White);

	tv.zoom = 3, tv.x = 0, tv.y = 0;
	tv = tv;
}

