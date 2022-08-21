#pragma once
#include "../ACREngine.h"

#include "screen.h"
#include "ACRE_transform.h"

#define MENU_H 72
#define NUM_OPS 4
#define NUM_CLDS 10

#define DW 240
#define DH 240

typedef struct option {
	char* text;
	float colorR, colorG, colorB;
	bool fading;
} option;

typedef struct cloud {
	Image img;
	float x, y;
	float vx;
} cloud;

typedef struct menuData {
	AreaTrans tv;
	screenData* s;

	int selectedOption;
	//int menuHeight;
	char* title;
	cloud clouds[NUM_CLDS];
	Image pointer;
	option ops[NUM_OPS];
	
} menuData;

void optionCalculations(menuData* m)
{
	int y = m->tv.y + m->tv.area.height*m->tv.zoom+5;
	Area ar = m->s->area;
	for (int i = 0; i < NUM_OPS; i++)
	{
		int strLen = (stringLength(m->ops[i].text, EightBit) + 1);

		sysDrawText(Width(ar) / 2 - (strLen / 2), y + i * 10, ar, m->ops[i].text, EightBit, Default, DarkGrey);
		sysDrawText(Width(ar) / 2 - (strLen / 2) - 1, (y + i * 10) - 1, ar, m->ops[i].text, EightBit, Default, Color(m->ops[i].colorR, m->ops[i].colorG, m->ops[i].colorB));

		if (i == m->selectedOption)
		{
			sysDrawImage(Width(ar) / 2 - (strLen / 2) - 10, y + i * 10, ar, m->pointer);
			flipImage(m->pointer);
			sysDrawImage(Width(ar) / 2 + (strLen / 2) + 3,y + i * 10, ar, m->pointer);
			flipImage(m->pointer);
		}
	}
	int selB = m->selectedOption;
	if (key(S).pressed && m->selectedOption < NUM_OPS - 1) m->selectedOption += 1;
	if (key(W).pressed && m->selectedOption > 0) m->selectedOption -= 1;

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

void cloudsCalculations(menuData* m) 
{
	for (int i = 0; i < NUM_CLDS; i++)
	{
		float rcx = m->clouds[i].x >= 0 ? map(m->clouds[i].x, 0, 240, 0, Width(Screen)) : m->clouds[i].x;
		float rcy = m->clouds[i].y >= 0 ? map(m->clouds[i].y, 0, 135, 0, Height(Screen)) : m->clouds[i].y;

		sysDrawImage(rcx, rcy, m->s->area, m->clouds[i].img);
		m->clouds[i].x += timePerSec(m->clouds[i].vx);
		
		if (m->clouds[i].x > Width(m->s->area)) m->clouds[i].x = 0 - m->clouds[i].img.imgData.width;
	}
}

menuData initalizeMenu(screenData* screenOn)
{
	menuData m;
	m.s = screenOn;

	m.selectedOption = 0;
	m.pointer = loadImage("pointer.acre");

	option op1 = { "Start", 255, 255, 255, false };
	option op2 = { "Options", 255, 255, 255, false };
	option op3 = { "Credits", 255, 255, 255, false };
	option op4 = { "Exit", 255, 255, 255, false };
	option ops[NUM_OPS] = { op1, op2, op3, op4 };

	Image cl1 = loadImage("cloud1.acre");
	Image cl2 = loadImage("cloud2.acre");

	cloud c1 = { cl1, -5, 0, 7 }, c2 = { cl2, 50, 34, 9 }, c3 = { cl1, 64, 102, 6 };
	cloud c4 = { cl1, 14, 70,10}, c5 = { cl2, 160, 24, 5 }, c6 = { cl1, 149, 69, 7 };
	cloud c7 = { cl2, 207, 95, 10 }, c8 = { cl2, 220, -2, 4 }, c9 = { cl1, 145, 125, 7 };
	cloud c10 = { cl2, 225, 58, 5 };

	cloud clouds[NUM_CLDS] = { c1, c2, c3, c4, c5, c6, c7, c8, c9, c10 };
	
	for (int i = 0; i < NUM_CLDS; i++)
		m.clouds[i] = clouds[i];
	for (int i = 0; i < NUM_OPS; i++)
		m.ops[i] = ops[i];

	m.title = "DORK";
	Area splashScreen = createArea(stringLength(m.title, EightBit), 8, Default, Default);
	AreaTrans tv = createAreaTrans(splashScreen);

	sysDrawText(1, 1, splashScreen, m.title, EightBit, Default, DarkGrey);
	sysDrawText(0, 0, splashScreen, m.title, EightBit, Default, White);
	
	tv.zoom = 3, tv.x = 0, tv.y = 0;
	m.tv = tv;
	return m;
}

void menuCalculations(menuData* m)
{
	m->tv.x = Width(Screen) / 2 - (stringLength(m->title, EightBit) * m->tv.zoom) / 2;
	m->tv.y = Height(Screen) / 2 - MENU_H / 2;
	cloudsCalculations(m);
	optionCalculations(m);
	drawAreaTransformed(m->tv, m->s->area);
}