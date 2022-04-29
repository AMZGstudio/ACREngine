#pragma once
//could be used, arent for now
#define cursorXY(x,y) printf("\033[%d;%dH",(y),(x))
#define hideCursor() printf("\033[?25l")
//ignore
#define WIDTHESCAPE 9
#define WAIT_BETWEEN_PRESS 50
#define singl 1
#define doubl 2

#ifndef WAIT
#define WAIT 0
#endif

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define CLEAR_AFTER_RENDER false
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

enum names { X, Y, Right, Left, Up, Down, Yes, No};
enum keys { upArrow = VK_UP, downArrow = VK_DOWN, leftArrow = VK_LEFT, rightArrow = VK_RIGHT, enterKey = VK_RETURN, escapeKey = VK_ESCAPE};
enum colors {Default, Black, Red, Green, Yellow, Blue, Magenta, Cyan, White};
enum special {LightShade = 176, MediumShade = 177, DarkShade = 178, FullBlock = 219, LowerHalfBlock = 220, LeftHalfBlock = 221, RightHalfBlock = 222, UpperHalfBlock = 223};

typedef struct Menu {
	char** options;
	int amountOptions;
	int menuWidth;
	int* selected;
	int menuSpacing;
	bool centered;
	bool allowMouse;
} Menu;

typedef struct Window {
	int x1, x2, y1, y2;
	int heightMin, widthMin;
	int colorFront, colorBack;
	int singleDoubleThick;
	int connected[4];
	bool resizeable, hasMenu;
	Menu* optionMenu;
} Window;
//windows handles
HANDLE hConsoleOutput, hConsoleInput;
HWND ConsoleWindow;

bool terminated = false;
char* screenBuffer = NULL;
int bufferWidth = 120, bufferHeight = 80;
int fontWidth = 7, fontHeight = 14;
int cursorPosX = 0, cursorPosY = 0;
int defaultFrontColor = White, defaultBackColor = Black;
int waitBetweenRender = 0;

clock_t time1 = 0, time2 = 0, startTime = 0;
clock_t current_ticks;
COORD mousePos;

/**************************************************************************************************
Screen Dimension Functions
**************************************************************************************************/
int central(int length, int start, int end)
{
	return start + ((end - start) / 2) - (length / 2) + 1;
}
int thirds(int firstOrSecond, int mode, int roundUp)
{
	int lengthOfBuffer;
	if (mode == X) lengthOfBuffer = bufferWidth;
	if (mode == Y) lengthOfBuffer = bufferHeight;
	float location = 0;

	if (firstOrSecond == 1) location = (float)lengthOfBuffer / (float)3.0;
	else if (firstOrSecond == 2) location = (float)lengthOfBuffer / (float)3.0 + (float)lengthOfBuffer / (float)3.0;		

	if (roundUp == Yes) location = (int)(location + (float)0.9);
		
	return (int)location;
}
void fillArrayWithColor(int colorFront, int colorBack, int slot)
{
	char slot1 = '0', slot2 = '0', slot3 = '0', slot4 = '0';

	if (colorFront == Black)  slot1 = '3', slot2 = '0';
	else if (colorFront == Red)    slot1 = '3', slot2 = '1';
	else if (colorFront == Green)  slot1 = '3', slot2 = '2';
	else if (colorFront == Yellow) slot1 = '3', slot2 = '3';
	else if (colorFront == Blue)   slot1 = '3', slot2 = '4';
	else if (colorFront == Magenta)slot1 = '3', slot2 = '5';
	else if (colorFront == Cyan)   slot1 = '3', slot2 = '6';
	else if (colorFront == White)  slot1 = '3', slot2 = '7';

	if (colorBack == Black)  slot3 = '4', slot4 = '0';
	else if (colorBack == Red)    slot3 = '4', slot4 = '1';
	else if (colorBack == Green)  slot3 = '4', slot4 = '2';
	else if (colorBack == Yellow) slot3 = '4', slot4 = '3';
	else if (colorBack == Blue)   slot3 = '4', slot4 = '4';
	else if (colorBack == Magenta)slot3 = '4', slot4 = '5';
	else if (colorBack == Cyan)   slot3 = '4', slot4 = '6';
	else if (colorBack == White)  slot3 = '4', slot4 = '7';

	if (colorFront != Default && slot != -1)
	{
		screenBuffer[slot - 6] = slot1;
		screenBuffer[slot - 5] = slot2;
	}
	if (colorBack != Default && slot != -1)
	{
		screenBuffer[slot - 3] = slot3;
		screenBuffer[slot - 2] = slot4;
	}
}
int xyLoc(int x, int y)
{
	x -= 1, y -= 1;
	
	if (x < bufferWidth && x >= 0 && y < bufferHeight && y >= 0)
		return ((y * bufferWidth) + x) * WIDTHESCAPE + WIDTHESCAPE - 1;
	else return -1;
}
/**************************************************************************************************
Windows Functions
**************************************************************************************************/
bool checkActiveWindow()
{
	if (GetConsoleWindow() == GetForegroundWindow()) return true;
	else return false;
}
int SetFont(int fontSizeX, int fontSizeY, UINT codePage)
{
	int returnValue = 0; //0 means ok
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.X = fontSizeX;
	info.dwFontSize.Y = fontSizeY; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, 9, L"Consolas");
	if (SetCurrentConsoleFontEx(hConsoleOutput, 0, &info) == 0) returnValue = -1;
	//char text[500] = { 0 }GetLastError();
	if (SetConsoleOutputCP(codePage) == 0) returnValue = -2;
	return returnValue;
}
int SetConsoleWindowSize(int x, int y)
{
	int returnValue = 0; //0 means ok

	if (hConsoleOutput == INVALID_HANDLE_VALUE) while(1) printf("Unable to get stdout handle.");
	{
		COORD largestSize = GetLargestConsoleWindowSize(hConsoleOutput);
		if (x > largestSize.X) while(1) printf("The x dimension is too large.\n");
		if (y > largestSize.Y) while(1) printf("The y dimension is too large.\n");
	}
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(hConsoleOutput, &bufferInfo)) printf("Unable to retrieve screen buffer info.");

	SMALL_RECT winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info = { 0,0,x < windowSize.X ? x - 1 : windowSize.X - 1,y < windowSize.Y ? y - 1 : windowSize.Y - 1 };
		if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info)) returnValue = FALSE;
	}
	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(hConsoleOutput, size)) returnValue = -1;//printf("Unable to resize screen buffer.");

	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info)) returnValue = -2; //printf("Unable to resize window after resizing buffer.");

	return returnValue;
}
/**************************************************************************************************
Input Functions (also related to windows, wont work cross platform)
**************************************************************************************************/
char getArrowKeys(int arrow1, int arrow2)
{
	int key = 0;
	int currentPrevTime = time1;
	int currentTime = clock();

	if (currentTime > currentPrevTime + WAIT_BETWEEN_PRESS && checkActiveWindow() == 1)
	{
		if (GetAsyncKeyState(arrow1) & 0x8000) key = arrow1;
		if (GetAsyncKeyState(arrow2) & 0x8000) key = arrow2;
		if (key != 0) time1 = clock();
	}
	return key;
}
int key(int key, int waitBetween)
{
	int currentPrevTime = time2;
	int currentTime = clock();
	int returnValue = 0;
	if ((currentTime >= currentPrevTime + waitBetween) && GetConsoleWindow() == GetForegroundWindow())
	{
		if (GetAsyncKeyState(key) & 0x8000) returnValue = 1, time2 = clock();
	}
	return returnValue;
}
void arrowInput(int* number, int numberMax, int numberMin, int mode)
{
	int input = 0;
	if (mode == Y)
	{
		input = getArrowKeys(upArrow, downArrow);
		if (input == upArrow && *number > numberMin) *number -= 1;
		if (input == downArrow && *number < numberMax) *number += 1;
	}

	else if (mode == X)
	{
		input = getArrowKeys(rightArrow, leftArrow);
		if (input == leftArrow && *number > numberMin) *number -= 1;
		if (input == rightArrow && *number < numberMax) *number += 1;
	}
}
/*******************************
create functions
*********************************/
Menu* createMenu(char options[][100], int numOptions, int width, int seperation, int* selected, bool centered, bool allowMouse, Window* windowToCling)
{
	int* selectedTemp = (int*)malloc(sizeof(int));

	Menu* menu = (Menu*)malloc(sizeof(Menu));

	menu->amountOptions = numOptions, menu->menuWidth = width, menu->menuSpacing = seperation, menu->centered = centered, menu->allowMouse = allowMouse;
	menu->options = (char**)malloc(sizeof(char*) * numOptions);
	if (selected == 0)
	{
		*selectedTemp = 0;
	}
	else *selectedTemp = *selected;
	menu->selected = selectedTemp;

	for (int i = 0; i < numOptions; i++)
		menu->options[i] = options[i];

	if (windowToCling != NULL)
		windowToCling->optionMenu = menu;

	return menu;
}
Window* createWindow(int xStart, int yStart, int xEnd, int yEnd, int singleDoubleThick, bool resizable, int colorFront, int colorBack)
{
	Window* createdWindow = (Window*)malloc(sizeof(Window));
	if (createdWindow == NULL) while (1) printf("Error creating windows sizes failed\n");

	createdWindow->x1 = xStart, createdWindow->x2 = xEnd;
	createdWindow->y1 = yStart, createdWindow->y2 = yEnd;

	createdWindow->resizeable = resizable, createdWindow->colorFront = colorFront;
	createdWindow->colorBack = colorBack, createdWindow->singleDoubleThick = singleDoubleThick;
	createdWindow->optionMenu = NULL;

	for (int i = 0; i < 4; i++)
		createdWindow->connected[i] = 0;

	return createdWindow;
}

/**************************************************************************************************
Drawing to the screen functions
**************************************************************************************************/
void drawText(char* text, int x, int y, int colorFront, int colorBack)
{
	int xStart = x, slot = 0;
	for (x; x < xStart + (signed)strlen(text); x++)
	{
		slot = xyLoc(x, y);
		if (slot != -1)
		{
			screenBuffer[slot] = text[x - xStart];
			fillArrayWithColor(colorFront, colorBack, slot);
		}
	}
}
void drawNumber(int number, int x, int y, int colorFront, int colorBack)
{
	int numLength = 0, numCpy = number;
	//find length
	while (numCpy >= 9)
	{
		numCpy = numCpy / 10;
		numLength++;
	}
	numLength+=2;
	char text[50] = { 0 };

	_itoa_s(number, text, 50, 10);
	drawText(text, x, y, colorFront, colorBack);
}
void drawChar(char letter, int x, int y, int colorFront, int colorBack)
{
	int slot = xyLoc(x, y);
	if(slot != -1) screenBuffer[slot] = letter;
	fillArrayWithColor(colorFront, colorBack, slot);
}
void drawSquare(int xStart, int yStart, int xEnd, int yEnd, int colorFront, int colorBack)
{
	for (int x = xStart; x <= xEnd; x++)
		for (int y = yStart; y <= yEnd; y++)
			fillArrayWithColor(colorFront, colorBack, xyLoc(x, y));
}
void drawLine(int xStart, int yStart, int xEnd, int yEnd, int colorFront, int colorBack)
{
	int changeX = xEnd - xStart;
	int changeY = yEnd - yStart;
	float slope = (float)changeY / (float)changeX;
	int b = yStart;

	for (int i = xStart; i <= xEnd; i++)
	{
		int slot = xyLoc(i, slope * i + b);
		if (slot != -1) fillArrayWithColor(colorFront, colorBack, slot);
	}
}
void drawMenu(Menu* whichOne, int x, int y)
{
	int amountOptions = whichOne->amountOptions;
	int menuWidth = whichOne->menuWidth;
	int menuSpacing = whichOne->menuSpacing;

	// check if the mouse is click one of the buttons, and change the corrsepoding selected value.
	if (whichOne->allowMouse == true)
	{
		for(int i = 0; i < amountOptions * (menuSpacing + 1); i+= menuSpacing + 1)
			if (cursorPosX >= x && cursorPosX <= x + whichOne->menuWidth && cursorPosY == (i + y) && key(VK_LBUTTON, 0))
				*(whichOne->selected) = i / (menuSpacing + 1);
	}
	int longestOption = 0;

	for (int i = 0; i < amountOptions; i++)
		if ((signed)strlen(whichOne->options[i]) >= longestOption)
			longestOption = strlen(whichOne->options[i]);

	int menuPadding = (menuWidth - longestOption) / 2;

	for (int i = 0; i < amountOptions; i++)
	{
		if (i == *(whichOne->selected)) drawSquare(x, y, x + menuWidth, y, defaultBackColor, White);
		else drawSquare(x, y, x + menuWidth, y, defaultFrontColor, defaultBackColor);

		drawText(whichOne->options[i], x + menuPadding, y, Default, Default);
		y += 1 + menuSpacing;
	}
}
void drawWindow(Window* whichWindow)
{
	int xStart = whichWindow->x1, xEnd = whichWindow->x2;
	int yStart = whichWindow->y1, yEnd = whichWindow->y2;
	int singleDoubleThick = whichWindow->singleDoubleThick;
	int colorFront = whichWindow->colorFront, colorBack = whichWindow->colorBack;
	int xMenu = 1, yMenu = 1, connected[4];
	int xWidthMin = 0, yWidthMin = 0;
	for (int i = 0; i < 4; i++) connected[i] = whichWindow->connected[i];
	
	if (whichWindow->resizeable == true)
	{
		if ((cursorPosX <= xEnd && cursorPosX >= xStart && cursorPosY == yStart || connected[0] == 1) && key(VK_LBUTTON, 0))
			whichWindow->connected[0] = 1, whichWindow->y1 = cursorPosY;
		else whichWindow->connected[0] = 0;

		if ((cursorPosY <= yEnd && cursorPosY >= yStart && cursorPosX == xStart || connected[1] == 1) && key(VK_LBUTTON, 0))
			whichWindow->connected[1] = 1, whichWindow->x1 = cursorPosX;
		else whichWindow->connected[1] = 0;

		if ((cursorPosX <= xEnd && cursorPosX >= xStart && cursorPosY == yEnd || connected[2] == 1) && key(VK_LBUTTON, 0))
			whichWindow->connected[2] = 1, whichWindow->y2 = cursorPosY;
		else whichWindow->connected[2] = 0;

		if ((cursorPosY <= yEnd && cursorPosY >= yStart && cursorPosX == xEnd || connected[3] == 1) && key(VK_LBUTTON, 0))
			whichWindow->connected[3] = 1, whichWindow->x2 = cursorPosX;
		else whichWindow->connected[3] = 0;
	}
	//draw it
	int tr, tl, rl, l, br, bl, tb;
	if (singleDoubleThick == 2) tl = 201, tr = 187, bl = 200, br = 188, rl = 186, tb = 205;
	if (singleDoubleThick == 1) tl = 218, tr = 191, bl = 192, br = 217, rl = 179, tb = 196;

	for (int x = xStart; x <= xEnd; x++)
		for (int y = yStart; y <= yEnd; y++)
		{
			//if we are in the first column or the last column.
			if (y == yStart || y == yEnd)
			{
				if (y == yStart && x == xStart) drawChar(tl, x, y, colorFront, colorBack);
				else if (y == yStart && x == xEnd) drawChar(tr, x, y, colorFront, colorBack);
				else if (y == yEnd && x == xStart) drawChar(bl, x, y, colorFront, colorBack);
				else if (y == yEnd && x == xEnd) drawChar(br, x, y, colorFront, colorBack);
				else drawChar(tb, x, y, colorFront, colorBack);
			}
			else if (x == xStart || x == xEnd)
				drawChar(rl, x, y, colorFront, colorBack);
		}
	//draw the background of the window
	drawSquare(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, colorFront, colorBack);

	//draw the menu
	if (whichWindow->optionMenu != NULL)
	{
		if (whichWindow->optionMenu->centered == true)
		{
			xMenu = central(whichWindow->optionMenu->menuWidth, xStart, xEnd);
			yMenu = central(whichWindow->optionMenu->amountOptions + whichWindow->optionMenu->menuSpacing + 1, yStart, yEnd);
		}
		drawMenu(whichWindow->optionMenu, xMenu, yMenu);
		xWidthMin = whichWindow->optionMenu->menuWidth + 4;
	}
}
void drawBuffer(char buffer[][8], int bufferHeight, int x, int y, int colorFront, int colorBack)
{
	for (int i = 0; i < bufferHeight; i++)
		drawText(buffer[i], x, y + i, colorFront, colorBack);
}
void clearScreen()
{
	for (int x = 1; x <= bufferWidth; x++)
		for (int y = 1; y <= bufferHeight; y++)
			drawChar(' ', x, y, defaultFrontColor, defaultBackColor);
}
/**************************************************************************************************
Handing console (creating buffers, destroying buffers, rendering buffers, etc).
**************************************************************************************************/
int width()
{
	return bufferWidth;
}
int height()
{
	return bufferHeight;
}
int terminate(void)
{
	terminated = true;
	if (SetConsoleOutputCP(65001) == 0) while (1) printf("Changing codepage back to default failed.\n");
	free(screenBuffer);
	screenBuffer = NULL;
	//check leaks
	//printf("\033[0;0mleaks: %d", _CrtDumpMemoryLeaks());
	//while (!key(escapeKey, 0));
	return 0;
}
void initalize(const char* title,int width, int height, int bufferFontWidth, int bufferFontHeight, int defaultFront, int defaultBack)
{
	if (terminated == false) terminate();

	terminated = false;
	//set default values
	if (bufferWidth != Default) bufferWidth = width;
	if (bufferHeight != Default) bufferHeight = height;
	if (bufferFontWidth != Default) fontWidth = bufferFontWidth;
	if (bufferFontHeight != Default) fontHeight = bufferFontHeight;

	waitBetweenRender = WAIT;

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput == 0) while (1) printf("Getting console output handle didnt work.\n");
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	ConsoleWindow = GetConsoleWindow();

	if (SetFont(fontWidth, fontHeight, 437) != 0) while(1) printf("Setting console font failed\n");
	
	if (SetConsoleWindowSize(bufferWidth, bufferHeight) != 0) while (1) printf("Console resizing failed\n");
	SetConsoleTitleA(title);
	//makes window not resizbale

	ConsoleWindow = GetConsoleWindow();
	SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	hideCursor();
	cursorXY(0, 0);

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	// Set flags to allow mouse input, and disable selecting, and support for ANSI escape sequences.	
	if (!SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		while(1) printf("Setting The consoles Input modes did not work.\n");
	if (!SetConsoleMode(hConsoleOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_WRAP_AT_EOL_OUTPUT))
		while (1) printf("Setting The consoles Output modes did not work.\n");
	
	if (defaultFront != Default) defaultFrontColor = defaultFront;
	if (defaultBack != Default) defaultBackColor = defaultBack;

	screenBuffer = (char*)malloc(sizeof(char) * ((bufferWidth * bufferHeight) * WIDTHESCAPE + 1));

	for (int i = 0; i < (bufferWidth * bufferHeight) * WIDTHESCAPE; i += WIDTHESCAPE)
	{
		screenBuffer[i] = '\033', screenBuffer[i + 1] = '[', screenBuffer[i + 2] = '0';
		screenBuffer[i + 3] = '0', screenBuffer[i + 4] = ';', screenBuffer[i + 5] = '0';
		screenBuffer[i + 6] = '0', screenBuffer[i + 7] = 'm', screenBuffer[i + 8] = ' ';
	}
	clearScreen();
}
void deleteWindow(Window* window)
{
	free(window);
}
void deleteMenu(Menu* menu)
{
	free(menu->selected);
	free(menu);
}
void render(bool clear)
{
	//get mouse location
	POINT cursor_pos;

	if (GetCursorPos(&cursor_pos))
	{
		if (ConsoleWindow && ScreenToClient(ConsoleWindow, &cursor_pos));
		{
			cursorPosX = ((cursor_pos.x) / (fontWidth)) + 1;
			cursorPosY = ((cursor_pos.y) / (fontHeight)) + 1;
		}
	}
	startTime = clock();
	//render
	if (!WriteConsoleA(hConsoleOutput, screenBuffer, (bufferWidth * bufferHeight) * WIDTHESCAPE, NULL, NULL)) while (1) printf("Rendering failed.\n");
	
	if (clear == true) clearScreen();
	while (!((int)clock() > (int)startTime + WAIT));
}

int map(int numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd)
{
	int output = numberMapStart + ((numberMapEnd - numberMapStart) / (numberEnd - numberBegin)) * (numberToMap - numberBegin);
	return output; 
}