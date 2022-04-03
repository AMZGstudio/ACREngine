#pragma once
#define cursorXY(x,y) printf("\033[%d;%dH",(y),(x))
#define hideCursor() printf("\033[?25l")

#include <stdio.h>
#include <windows.h>
#include <time.h>

enum names { X, Y, Yes, No, Right, Left, Up, Down};
enum keys { upArrow = VK_UP, downArrow = VK_DOWN, leftArrow = VK_LEFT, rightArrow = VK_RIGHT};

enum colors {
	Default, None,
	Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, BrightBlack, BrightRed, BrightGreen, BrightYellow, BrightBlue, BrightMagenta, BrightCyan, BrightWhite
};

#define WIDTHESCAPE 9

char* screenBuffer = NULL;
int bufferWidth = 0;
int bufferHeight = 0;

int defaultFrontColor = White;
int defaultBackColor = Black;

time_t time1 = 0;
time_t time2 = 0;
float elapsedTime = 0;
time_t timeLength;

char intChr(int number)
{
	char numbers[] = "0123456789";
	return numbers[number];
}

int chrInt(char letter)
{
	int number = 0;
	switch (letter)
	{
	case '1': number = 1; break;
	case '2': number = 2; break;
	case '3': number = 3; break;
	case '4': number = 4; break;
	case '5': number = 5; break;
	case '6': number = 6; break;
	case '7': number = 7; break;
	case '8': number = 8; break;
	case '9': number = 9; break;

	}
	return number;
}

int xyLoc(int x, int y)
{
	x -= 1;
	y -= 1;
	return ((y * bufferWidth) + x) * WIDTHESCAPE + WIDTHESCAPE - 1;
}

int central(int length, int mode)
{
	if(mode == X)
		return (bufferWidth / 2) - (length / 2) + 1;
	else if(mode == Y)
		return (bufferHeight / 2) - (length / 2) - 1;
}

int thirds(int firstOrSecond, int mode, int roundUp)
{
	int lengthOfBuffer;
	if (mode == X) lengthOfBuffer = bufferWidth;
	if (mode == Y) lengthOfBuffer = bufferHeight;
	float location;
	if (firstOrSecond == 1) location = (float)lengthOfBuffer / 3.0;
	else if (firstOrSecond == 2) location = (float)lengthOfBuffer / 3.0 + (float)lengthOfBuffer / 3.0;
		

	if (roundUp == Yes)
		location = (int)(location + 0.9);
	return (int)location;
}
//0000000000

void fillArrayWithColor(int colorFront, int colorBack, int slot)
{
	char slot1 = '0', slot2 = '0', slot3 = '0', slot4 = '0';
	if (colorFront == Default) colorFront = defaultFrontColor;
	if (colorBack == Default) colorBack = defaultBackColor;

	switch (colorFront)
	{
	case Black: slot1 = '3', slot2 = '0'; break;
	case Red:   slot1 = '3', slot2 = '1'; break;
	case Green: slot1 = '3', slot2 = '2'; break;
	case Yellow:slot1 = '3', slot2 = '3'; break;
	case Blue:  slot1 = '3', slot2 = '4'; break;
	case Magenta:slot1 = '3', slot2 = '5'; break;
	case Cyan:  slot1 = '3', slot2 = '6'; break;
	case White: slot1 = '3', slot2 = '7'; break;
	}
	
	switch (colorBack)
	{
	case Black:   slot3 = '4', slot4 = '0'; break;
	case Red:     slot3 = '4', slot4 = '1'; break;
	case Green:   slot3 = '4', slot4 = '2'; break;
	case Yellow:  slot3 = '4', slot4 = '3'; break;
	case Blue:    slot3 = '4', slot4 = '4'; break;
	case Magenta: slot3 = '4', slot4 = '5'; break;
	case Cyan:    slot3 = '4', slot4 = '6'; break;
	case White:   slot3 = '4', slot4 = '7'; break;
	}

	//if (colorFront != None && colorFront != Default) defaultFrontColor = colorFront;
	//if (colorBack  != None && colorBack  != Default) defaultBackColor  = colorBack;
	
	screenBuffer[slot - 6] = slot1;
	screenBuffer[slot - 5] = slot2;
	screenBuffer[slot - 3] = slot3;
	screenBuffer[slot - 2] = slot4;
}
void drawText(char* text, int x, int y, int colorFront, int colorBack)
{
	int xStart = x, slot = 0;
	for (x; x < xStart + (signed)strlen(text); x++)
	{
		slot = xyLoc(x, y);
		screenBuffer[slot] = text[x - xStart];
		fillArrayWithColor(colorFront, colorBack, slot);
	}
}

void drawChar(char letter, int x, int y, int colorFront, int colorBack)
{
	int slot = xyLoc(x, y);
	screenBuffer[slot] = letter;
	fillArrayWithColor(colorFront, colorBack, slot);
}

void drawSquare(int xStart, int yStart, int xEnd, int yEnd, int colorFront, int colorBack)
{
	for (int x = xStart; x <= xEnd; x++)
		for (int y = yStart; y <= yEnd; y++)
			fillArrayWithColor(colorFront, colorBack, xyLoc(x, y));
}

void drawLine(int xStart, int yStart, int length, int direction, int colorFront, int colorBack)
{
	int xEnd = xStart, yEnd = yStart;
	switch (direction)
	{
	case Right: xEnd += length - 1; break;
	case Left: xEnd -= length - 1; break;
	case Up: yEnd -= length - 1; break;
	case Down: yEnd += length - 1; break;
	}
	
	drawSquare(xStart, yStart, xEnd, yEnd, colorFront, colorBack);
}

void drawMenu(int selected, char menuOptions[][100], int amountOptions, int menuPadding, int menuXLoc, int menuYLoc)
{
	for (int i = 0; i < amountOptions; i++)
	{
		if (i == selected) drawSquare(menuXLoc, menuYLoc, menuXLoc + 10, menuYLoc, Black, White);
		else drawSquare(menuXLoc, menuYLoc, menuXLoc + 10, menuYLoc, White, Black);

		drawText(menuOptions[i], menuXLoc + menuPadding, menuYLoc, Default, Default);
		menuYLoc += 1;
	}
}

void drawBuffer(char buffer[][8], int bufferHeight, int x, int y, int colorFront, int colorBack)
{
	for (int i = 0; i < bufferHeight; i++)
	{
		drawText(buffer[i], x, y + i, colorFront, colorBack);
	}
}

void clearScreen()
{
	timeLength = clock();
	for (int x = 1; x <= bufferWidth; x++)
		for (int y = 1; y <= bufferHeight; y++)
			drawChar(' ', x, y, Default, Default);
}

char* initalize(int width, int height, int defaultFront, int defaultBack)
{
	bufferWidth = width;
	bufferHeight = height;

	if (defaultFront != NULL) defaultFrontColor = defaultFront;
	if (defaultBack != NULL) defaultBackColor = defaultBack;

	hideCursor();
	screenBuffer = malloc(sizeof(char) * ((bufferWidth * bufferHeight) * WIDTHESCAPE + 1));

	for (int i = 0; i < (bufferWidth * bufferHeight) * WIDTHESCAPE; i += WIDTHESCAPE)
	{
		screenBuffer[i] = '\033';
		screenBuffer[i + 1] = '[';
		screenBuffer[i + 2] = '0';
		screenBuffer[i + 3] = '0';
		screenBuffer[i + 4] = ';';
		screenBuffer[i + 5] = '0';
		screenBuffer[i + 6] = '0';
		screenBuffer[i + 7] = 'm';
		screenBuffer[i + 8] = ' ';
	}
	clearScreen();
	return screenBuffer;
}

void render()
{
	elapsedTime = (float)clock() - (float)timeLength;
	timeLength = 0;

	fwrite("\033[0;0H", 6, 1, stdout);
	fwrite(screenBuffer, (bufferWidth * bufferHeight) * WIDTHESCAPE, 1, stderr);
	Sleep(10);
}

char getArrowKeys(int arrow1, int arrow2, time_t timeSelected)
{
	int key = 0;
	if (clock() > timeSelected)
	{
		if (GetAsyncKeyState(arrow1) & 0x8000) key = arrow1;
		if (GetAsyncKeyState(arrow2) & 0x8000) key = arrow2;
		if (key != 0 ) timeSelected = clock();
	}
	return key;
}

int getKeyInput(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return 1;
		time1 = clock();
	}
	return 0;
}

void input(int* number, int numberMax, int numberMin, int mode)
{
	int input = 0;
	if (mode == Y)
	{
		input = getArrowKeys(upArrow, downArrow, time1);
		if (input == upArrow && *number > numberMin) *number -= 1;
		if (input == downArrow && *number < numberMax) *number += 1;
	}

	else if (mode == X)
	{
		input = getArrowKeys(rightArrow, leftArrow, time2);
		if (input == leftArrow && *number > numberMin) *number -= 1;
		if (input == rightArrow && *number < numberMax) *number += 1;
	}
}