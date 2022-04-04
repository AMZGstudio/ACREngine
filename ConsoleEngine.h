#pragma once
//could be used, arent for now
#define cursorXY(x,y) printf("\033[%d;%dH",(y),(x))
#define hideCursor() printf("\033[?25l")
//ignore
#define WIDTHESCAPE 9
#define WAIT_BETWEEN_PRESS 200
#define WAIT_BETWEEN_RENDER 50 //milliseconds
#include <stdio.h>
#include <windows.h>
#include <time.h>

enum names { X, Y, Right, Left, Up, Down, Yes, No};
enum keys { upArrow = VK_UP, downArrow = VK_DOWN, leftArrow = VK_LEFT, rightArrow = VK_RIGHT, enterKey = VK_RETURN};
enum colors {Default, None, Black, Red, Green, Yellow, Blue, Magenta, Cyan, White};
enum special {LightShade = 176, MediumShade = 177, DarkShade = 178, FullBlock = 219, LowerHalfBlock = 220, LeftHalfBlock = 221, RightHalfBlock = 222, UpperHalfBlock = 223};

char* screenBuffer = NULL;
int bufferWidth = 0, bufferHeight = 0;
int defaultFrontColor = White, defaultBackColor = Black;

time_t time1 = 0;
time_t startTime = 0;

/**************************************************************************************************
Screen Dimension Functions
**************************************************************************************************/
int central(int length, int mode)
{
	if (mode == X) return (bufferWidth / 2) - (length / 2) + 1;
		
	else if (mode == Y) return (bufferHeight / 2) - (length / 2) - 1;
		
	else return -1;
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
	x -= 1;
	y -= 1;
	if (x < bufferWidth && x >= 0 && y < bufferHeight && y >= 0)
		return ((y * bufferWidth) + x) * WIDTHESCAPE + WIDTHESCAPE - 1;
	else return -1;
}

/**************************************************************************************************
Windows Functions
**************************************************************************************************/
int checkActiveWindow()
{
	if (GetConsoleWindow() == GetForegroundWindow()) return 1;
	else return 0;
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
	if (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info) == 0) returnValue = -1;

	if (SetConsoleOutputCP(codePage) == 0) returnValue = -2;
	return returnValue;
}
void dontAllowResizeWindow()
{
	//makes window not resizbale
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
int SetConsoleWindowSize(int x, int y)
{
	int returnValue = 0; //0 means ok
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (h == INVALID_HANDLE_VALUE) printf("Unable to get stdout handle.");
	{
		COORD largestSize = GetLargestConsoleWindowSize(h);
		if (x > largestSize.X) printf("The x dimension is too large.");
		if (y > largestSize.Y) printf("The y dimension is too large.");
	}
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(h, &bufferInfo)) printf("Unable to retrieve screen buffer info.");

	SMALL_RECT winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info = { 0,0,x < windowSize.X ? x - 1 : windowSize.X - 1,y < windowSize.Y ? y - 1 : windowSize.Y - 1 };
		if (!SetConsoleWindowInfo(h, TRUE, &info)) returnValue = FALSE;
	}
	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(h, size)) returnValue = -1;//printf("Unable to resize screen buffer.");

	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(h, TRUE, &info)) returnValue = -2; //printf("Unable to resize window after resizing buffer.");
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
int getKeyInput(int key)
{
	int currentPrevTime = time1;
	int currentTime = clock();
	int returnValue = 0;
	if (currentTime > currentPrevTime + WAIT_BETWEEN_PRESS && GetConsoleWindow() == GetForegroundWindow())
	{
		if (GetAsyncKeyState(key) & 0x8000) returnValue = 1, time1 = clock();
	}
	return returnValue;
}
void keyInput(int* number, int numberMax, int numberMin, int mode)
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
void wordInput(char* string, int stringLength, int x, int y)
{
	Sleep(100);
	cursorXY(x - 1, y - 1);
	fgets(string, stringLength, stdin);
	string[strcspn(string, "\n")] = 0;
	while (!getKeyInput(enterKey));
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
	char* text = malloc(numLength * sizeof(char));

	_itoa_s(number, text, numLength, 10);
	drawText(text, x, y, colorFront, colorBack);
	free(text);
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
void drawWindow(int xStart, int yStart, int xEnd, int yEnd, int singleDoubleThick, int colorFront, int colorBack)
{
	int tr, tl, rl, l, br, bl, tb;
	if (singleDoubleThick == 2) tl = 201, tr = 187, bl = 200, br = 188, rl = 186, tb = 205;
	if (singleDoubleThick == 1) tl = 218, tr = 191, bl = 192, br = 217, rl = 179, tb = 196;

	for(int x = xStart; x<=xEnd; x++)
		for (int y = yStart; y <= yEnd; y++)
		{
			//if we are in the first column or the last column.
			if (y == yStart || y == yEnd)
			{
				if (y == yStart && x == xStart) drawChar(tl, x, y, colorFront, colorBack);
				else if (y == yStart && x == xEnd) drawChar(tr , x, y, colorFront, colorBack);
				else if (y == yEnd && x == xStart) drawChar(bl, x, y, colorFront, colorBack);
				else if (y == yEnd && x == xEnd) drawChar(br, x, y, colorFront, colorBack);
				else drawChar(tb, x, y, colorFront, colorBack);
			}
			else if(x == xStart || x == xEnd)
			{
				drawChar(rl, x, y, colorFront, colorBack);
			}
		}
}
void drawMenu(int selected, char menuOptions[][100], int amountOptions, int menuWidth, int menuSpacing, int menuXLoc, int menuYLoc)
{
	int longestOption = 0;
	for (int i = 0; i < amountOptions; i++)
		if ((signed)strlen(menuOptions[i]) >= longestOption) longestOption = strlen(menuOptions[i]);

	int menuPadding = (menuWidth - longestOption) / 2;

	for (int i = 0; i < amountOptions; i++)
	{
		if (i == selected) drawSquare(menuXLoc, menuYLoc, menuXLoc + menuWidth, menuYLoc, defaultBackColor, defaultFrontColor);
		else drawSquare(menuXLoc, menuYLoc, menuXLoc + menuWidth, menuYLoc, defaultFrontColor, defaultBackColor);

		drawText(menuOptions[i], menuXLoc + menuPadding, menuYLoc, Default, Default);
		menuYLoc += 1 + menuSpacing;
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
void startRender()
{
	startTime = clock();
}
void initalize(char* title, int width, int height, int fontWidth, int fontHeight, int defaultFront, int defaultBack)
{
	bufferWidth = width;
	bufferHeight = height;

	if (SetFont(fontWidth, fontHeight, 437) != 0) while(1) printf("Setting console font failed\n");
	
	if (SetConsoleWindowSize(bufferWidth, bufferHeight) == 0) while (1) printf("Console resizing failed\n");
	SetConsoleTitleA(title);

	dontAllowResizeWindow();

	hideCursor();

	if (defaultFront != None) defaultFrontColor = defaultFront;
	if (defaultBack != None) defaultBackColor = defaultBack;

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
}
void render()
{
	while (!((int)clock() > (int)startTime + WAIT_BETWEEN_RENDER));

	//float fps = (float)1 / (((float)clock() - (float)startTime) / CLOCKS_PER_SEC);
	//int nFps = (int)(fps + 0.5);
	//startTime = clock();
	
	//drawNumber((int)fps, 1, 15, White, Default);
	fwrite("\033[0;0H", 6, 1, stdout);
	fwrite(screenBuffer, (bufferWidth * bufferHeight) * WIDTHESCAPE, 1, stdout);
}
void terminate()
{
	while (!getKeyInput(enterKey));
	free(screenBuffer);
}
