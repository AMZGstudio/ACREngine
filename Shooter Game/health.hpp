#pragma once

#include "../ACRE Files/ACREngine.h"

class HealthBar 
{
private:
	Area heart;
	Space bar;
	Space ammo;

	int ox = 3;
public:
	HealthBar()
	{
		heart = loadSprite("../ACRE Sprites/heart.acre");
		bar = calcSpace(ScreenSpace, Centered, Height(Screen) - 12, 52, 6);// { 9, 4, 61, 10 };
		ammo = { bar.startX-2, bar.startY-5, 2, 2 };
	}
	~HealthBar()
	{
		deleteArea(&heart);
	}

	void draw(float health, int ammunition)
	{
		// shadow
		drawRect(ox+bar.startX, bar.startY+1, ox+bar.endX+1, bar.endY+1, VeryDarkGrey);
		
		// border stuff
		drawRect(ox+bar.startX, bar.startY, ox+bar.endX, bar.endY, DarkGrey);
		drawRectFilled(ox+bar.startX+1, bar.startY+1, ox+bar.endX-1, bar.endY-1, VeryDarkGrey);

		// health bar itself
		int width = map(health, 0, 100, 1, 51);
		drawRect(ox+bar.startX + 1, bar.startY + 1, ox+bar.startX + width, bar.endY - 1, Red);
		drawRectFilled(ox+bar.startX + 1, bar.startY + 2, ox+bar.startX + width-1, bar.endY-1, DarkRed);
		drawRect(ox + bar.startX + 1, bar.endY-2, ox + bar.startX + width, bar.endY - 1, VeryDarkRed);

		// lines across health
		for(int i = 0; i <= 5; i++)
			drawRect(ox+bar.startX + i*9, bar.startY + 1, ox+bar.startX + i*9+1, bar.endY - 1, DarkGrey);

		drawArea(ox+bar.startX-6, bar.startY-1, heart);

		// draw ammo
		for (int i = 0; i < ammunition; i++)
		{
			spDrawPixel(i * 2, 0, ammo, Yellow);
			spDrawPixel(i * 2, 1, ammo, Yellow);
		}
	}
};