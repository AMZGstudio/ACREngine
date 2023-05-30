/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*	   ___  _____ ______ _____            _
*	  / _ \/  __ \| ___ \  ___|          (_)
*	 / /_\ \ /  \/| |_/ / |__ _ __   __ _ _ _ __   ___
*	 |  _  | |    |    /|  __| '_ \ / _` | | '_ \ / _ \
*	 | | | | \__/\| |\ \| |__| | | | (_| | | | | |  __/
*	 \_| |_/\____/\_| \_\____/_| |_|\__, |_|_| |_|\___|
*	                                 __/ |
*	                                |___/
*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ACREngine, a game engine that runs entirely in the console!
You can use this for whatever you would like, it would be nice if you
gave me credit, but you dont have to. ¯\_(ツ)_/¯

For information on how to use this, go to the github repo:
https://github.com/AMZGstudio/ACREngine

original creator:
AMZGstudio

BSD 2-Clause License

Copyright (c) 2022, AMZG
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef ACRE_INCLUDES
#define ACRE_INCLUDES
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		//#define _CRT_SECURE_NO_WARNINGS
		#define _WIN32_WINNT 0x0500

		#include <stdio.h>
		#include <windows.h>
		#include <stdbool.h>
		#include <stdarg.h>
	#else
		#error ACRE only supports windows
	#endif	
#endif

#ifndef ACRE_DECLARATIONS
#define ACRE_DECLARATIONS
	
	// all structs used by ACRE
	typedef struct Point { int x, y; } Point;
	typedef struct Space { int startX, startY, endX, endY; } Space;
	typedef struct MOUSE { int x, y, scrollH, scrollW; } MOUSE;

	typedef struct Key {
		bool pressed, held, released;
		int letter;} Key;

	typedef struct Image {
		char** characterArray;
		int width, height;
		int** colorArray;
		int** colorArrayBack;
		bool asciitext;} Image;

	Space Screen;
	MOUSE Mouse;
	// all enums
	enum KEYS {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Up, Down, Left, Right,
		Enter, Esc, LeftM, RightM, Spacebar, Shift, Comma, Period, Colon, Slash, QuestionMark, Backspace,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
	};
	enum ACRE_TYPES { EightBit = -503, Thirds = -502, Centered = -501, Default = -1 };
	enum COLORS { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Grey, DarkGrey = 237 };

	enum SPECIAL_CHARS {
		LightShade = 176, MediumShade = 177, DarkShade = 178, FullBlock = 219, LowerHalfBlock = 220,
		LeftHalfBlock = 221, RightHalfBlock = 222, UpperHalfBlock = 223
	};
	// function declarations
	Image loadImage(const char* imageFilePath);
	void saveImage(Image imgToSave, char* imageFilePath);
	int Width(Space screenSpace);
	int Height(Space screenSpace);
	int Random(int rangeStart, int rangeEnd);
	float timePerSec(float amount);
	Space getSpace(Space prevSpace, int xStart, int yStart, int xEnd, int yEnd);
	int map(int numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd);
	int strToInt(char* string);
	int Color(int r, int g, int b);
	bool pointSpaceCollide(int x, int y, Space screenSpace);
	bool rectangleCollide(int xStart1, int yStart1, int xEnd1, int yEnd1, int xStart2, int yStart2, int xEnd2, int yEnd2);
	bool spaceCollide(Space space1, Space space2);
	char getChar(int x, int y);
	int getPointFront(int x, int y);
	int getPointBack(int x, int y);
	Point sysDrawPoint(int x, int y, Space screenSpace, char character, int colorFront, int colorBack);
	Space sysDrawRect(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, char character, bool filled, int colorFront, int colorBack);
	Space sysDrawLine(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, char character, int colorFront, int colorBack);
	void sysDrawTriange(int x1, int y1, int x2, int y2, int x3, int y3, Space screenSpace, char character, bool filled, int colorFront, int colorBack);
	Space sysDrawCircle(int x, int y, Space screenSpace, int radius, char character, bool filled, int colorFront, int colorBack);
	Space sysDrawImage(int x, int y, Space screenSpace, Image inputImage);
	Space sysDrawFontChar(int x, int y, Space screenSpace, char character, int colorFront, int colorBack);
	Space sysDrawText(int x, int y, Space screenSpace, const char* text, int fontType, int colorFront, int colorBack);
	Space sysDrawInt(int x, int y, Space screenSpace, int number, int fontType, int colorFront, int colorBack);
	Space sysDrawOutline(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, int colorFront, int colorBack);
	Space sysDrawColorBuffer(int x, int y, Space screenSpace, int* buffer, int width, int height);
	void drawTriange(int x1, int y1, int x2, int y2, int x3, int y3, int color);
	void drawLine(int xStart, int yStart, int xEnd, int yEnd, int color);

	Space drawRect(int xStart, int yStart, int xEnd, int yEnd, int color);
	Space drawRectFilled(int xStart, int yStart, int xEnd, int yEnd, int color);
	Space drawCircle(int x, int y, int radius, int color);
	Space drawImage(int x, int y, Image img);
	Space drawText(int x, int y, const char* text, int fontType, int color);
	Point drawPoint(int x, int y, int colorBack);
	Point drawChar(int x, int y, char character, int colorFront);

	Space drawInt(int x, int y, int number, int fontType, int color);
	Space drawOutline(int xStart, int yStart, int xEnd, int yEnd, int color);
	Space drawColorBuffer(int x, int y, int* buffer, int width, int height);
	void clearScreen();
	Key key(int whichKey);
	bool textBoxInput(char* outputString, int outputStringLength);

	int terminate(void);
	void initalize(const char* title, int width, int height, int bufferFontWidth, int bufferFontHeight, int defaultFront, int defaultBack);
	void render(bool clear);
#endif

#ifdef ACRE_START
	#undef ACRE_START
	#ifndef ACRE_SYS_DEFS
		#define ACRE_SYS_DEFS
		#define ACRE_VER 2.2
		#define ANSI_STR_LEN 24
	#define AMOUNT_KEYS 52

	#ifndef FONT_WEIGHT
		#define FONT_WEIGHT 0
	#endif
	#ifndef DEFAULT_CHARACTER
		#define DEFAULT_CHARACTER ' '
	#endif
	#ifndef MOUSE_HWHEELED
		#define MOUSE_HWHEELED 0x0008
	#endif
	#ifndef FULLSCREEN
		#define FULLSCREEN false
	#endif
#endif
	char* screenBuffer = NULL, * screenBufferFull = NULL, windowTitle[200] = { 0 };
	int* backgroundBuffer = NULL, * foregroundBuffer = NULL;
	int nextOpenSlot = 0, buffW = 100, buffH = 50, fontWidth = 12, fontHeight = 12;
	int defaultFrontColor = White, defaultBackColor = Black;
	float fps = -1;
	bool checkActiveWindow = false, terminated = true;
	//windows handles
	HANDLE hConsoleOutput, hConsoleInput;
	HWND ConsoleWindow;

	//others
	MOUSE Mouse = { 0, 0, 0, 0 };
	Key allKeys[AMOUNT_KEYS] = { 0 };
	LARGE_INTEGER start = { 0 }, end = { 0 }, frequency = { 0 };

	float deltaTime = 0;

	// the eight bit font option in hex
	const unsigned char font8x8_basic[128][8] = {
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{ 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},{ 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},
		{ 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},{ 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},{ 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},
		{ 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},{ 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},
		{ 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},{ 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},
		{ 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},{ 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},
		{ 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},{ 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},{ 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},
		{ 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},{ 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},{ 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},
		{ 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},{ 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},{ 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},
		{ 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},
		{ 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},{ 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},{ 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},
		{ 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},{ 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},{ 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},
		{ 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},{ 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},{ 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},
		{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},{ 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},
		{ 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},{ 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},{ 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},
		{ 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},{ 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},{ 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},
		{ 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},{ 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},{ 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},
		{ 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},{ 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},{ 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},
		{ 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},
		{ 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},{ 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},{ 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},
		{ 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},{ 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},{ 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},
		{ 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},{ 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
		{ 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},{ 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},
		{ 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},{ 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},{ 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},
		{ 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},{ 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},
		{ 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},{ 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},{ 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},
		{ 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},{ 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},{ 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},
		{ 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},{ 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},
		{ 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},{ 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},{ 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},
		{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},{ 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},
		{ 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},{ 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},
		{ 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},{ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},{ 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},
		{ 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	};

	/**************************************************************************************************
	General functions
	******************************************************************************************************/
	void Error(const wchar_t* errorMsg)
	{
		MessageBoxW(NULL, (LPCWSTR)errorMsg, NULL, MB_OK);
		exit(EXIT_FAILURE);
	}

	int readColor(FILE* imageFile)
	{
		int selected = 0;
		char ch, color[5] = { 0 };
		while ((ch = fgetc(imageFile)) != ';' && ch != '\n')
			color[selected] = ch, selected++;

		return atoi(color);
	}

	Image loadImage(const char* imageFilePath)
	{
		char supportedVersion[] = "acrev2.0", ch, currentVersion[10] = { 0 }, width[5] = { 0 }, height[5] = { 0 };
		FILE* image = fopen(imageFilePath, "r");
		
		if (image == NULL) 
			Error(L"Opening image file failed!");

		Image image1;

		while ((ch = fgetc(image)) != ';');
		int nWidth = readColor(image), nHeight = readColor(image);
		image1.width = nWidth, image1.height = nHeight;

		image1.colorArray = (int**)malloc(sizeof(int*) * nWidth);
		for (int i = 0; i < nWidth; i++)
		{
			image1.colorArray[i] = (int*)malloc(sizeof(int) * nHeight);
			for (int j = 0; j < nHeight; j++)
				image1.colorArray[i][j] = 0;
		}
		for (int j = 0; j < nHeight; j++)
		{
			for (int i = 0; i < nWidth; i++)
			{
				image1.colorArray[i][j] = readColor(image);
				char letter = fgetc(image);
			}
			fgetc(image);
		}
		return image1;
	}

	void saveImage(Image imgToSave, char* imageFilePath)
	{

	}

	int Width(Space screenSpace)
	{
		return screenSpace.endX - screenSpace.startX;
	}

	int Height(Space screenSpace)
	{
		return screenSpace.endY - screenSpace.startY;
	}

	int xyLoc(int x, int y)
	{
		if (x < buffW && x >= 0 && y < buffH && y >= 0)
			return ((y * buffW) + x);
		return -1;
	}

	int Random(int rangeStart, int rangeEnd)
	{
		return (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;
	}

	int center(int length, Space screenSpace, int mode)
	{
		if (mode == X)
		{
			int screenSpaceWidth = screenSpace.endX - screenSpace.startX + 1; // include the other end.
			float halfWayThrough = (float)screenSpaceWidth / 2.0f;
			float halfText = (float)length / 2.0f;

			return (int)(halfWayThrough - halfText);
		}
		else if (mode == Y)
		{
			int screenSpaceWidth = screenSpace.endY - screenSpace.startY + 1; // include the other end.
			float halfWayThrough = (float)screenSpaceWidth / 2.0f;
			float halfText = (float)length / 2.0f;

			return (int)(halfWayThrough - halfText);
		}
		return -1;
	}

	int thirds(int firstOrSecond, int mode)
	{
		//TODO
		return 0;
	}

	float timePerSec(float amount)
	{
		return amount * deltaTime;
	}

	Space getSpace(Space prevSpace, int xStart, int yStart, int xEnd, int yEnd)
	{
		Space Location = { 0, 0, 0, 0 };

		if (xStart == Centered)
		{
			Location.startX = prevSpace.startX + center(xEnd, prevSpace, X);
			Location.endX = Location.startX + xEnd;
		}
		else
		{
			Location.startX = prevSpace.startX + xStart;
			Location.endX = prevSpace.startX + xEnd;
		}
		if (yStart == Centered)
		{
			Location.startY = prevSpace.startY + center(yEnd, prevSpace, Y);
			Location.endY = Location.startY + yEnd;
		}
		else
		{
			Location.startY = prevSpace.startY + yStart;
			Location.endY = prevSpace.startY + yEnd;
		}
		return Location;
	}

	int map(int numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd)
	{
		int output = numberMapStart + ((numberMapEnd - numberMapStart) / (numberEnd - numberBegin)) * (numberToMap - numberBegin);
		return output;
	}
	int strToInt(char* string)
	{
		return atoi(string);
	}

	int Color(int r, int g, int b)
	{
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		if (r < 0)
			r = 0;
		if (b < 0)
			b = 0;
		if (g < 0)
			g = 0;
		#define v2ci(v) (v < 48 ? 0 : v < 115 ? 1 : (v - 35) / 40)
		int ir = v2ci(r), ig = v2ci(g), ib = v2ci(b);   // 0..5 each
		#define color_index() (36 * ir + 6 * ig + ib)  /* 0..215, lazy evaluation */

		int average = (r + g + b) / 3;
		int gray_index = average > 238 ? 23 : (average - 3) / 10;  // 0..23

		static const int i2cv[6] = { 0, 0x5f, 0x87, 0xaf, 0xd7, 0xff };
		int cr = i2cv[ir], cg = i2cv[ig], cb = i2cv[ib];  // r/g/b, 0..255 each
		int gv = 8 + 10 * gray_index;  // same value for r/g/b, 0..255

		#define dist_square(A,B,C, a,b,c) ((A-a)*(A-a) + (B-b)*(B-b) + (C-c)*(C-c))
		int color_err = dist_square(cr, cg, cb, r, g, b);
		int gray_err = dist_square(gv, gv, gv, r, g, b);
		return color_err <= gray_err ? 16 + color_index() : 232 + gray_index; // this code is not mine
	} // removed static int, and replaced with int

	bool pointSpaceCollide(int x, int y, Space screenSpace)
	{
		if (x < screenSpace.startX || x >= screenSpace.endX || y < screenSpace.startY || y >= screenSpace.endY)
			return false;
		return true;
	}
	bool rectangleCollide(int xStart1, int yStart1, int xEnd1, int yEnd1, int xStart2, int yStart2, int xEnd2, int yEnd2)
	{
		if ((yStart1 > yEnd2 || yEnd1 < yStart2) || (xStart1 > xEnd2 || xEnd1 < xStart2))
			return false;
		return true;
	}

	bool spaceCollide(Space space1, Space space2)
	{
		return(rectangleCollide(space1.startX, space1.startY, space1.endX, space1.endY, space2.startX, space2.startY, space2.endX, space2.endY));
	}

	/**************************************************************************************************
	Windows Functions
	**************************************************************************************************/
	void SetFont(int fontSizeX, int fontSizeY, int fontWeight, UINT codePage)
	{
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.X = fontSizeX;
		info.dwFontSize.Y = fontSizeY; // leave X as zero
		info.FontWeight = FW_NORMAL;
		info.FontFamily = FF_DONTCARE;
		wcscpy(info.FaceName, L"Consolas");
		if (!SetConsoleOutputCP(codePage)) Error(L"Setting consoles codepage failed.");

		if (!SetCurrentConsoleFontEx(hConsoleOutput, 0, &info)) Error(L"Setting console font failed.");

	}

	void SetConsoleWindowSize(int* x, int* y)
	{
		if (FULLSCREEN) SetConsoleDisplayMode(hConsoleOutput, CONSOLE_FULLSCREEN_MODE, 0);
		if (hConsoleOutput == INVALID_HANDLE_VALUE) Error(L"Unable to get stdout handle.");
		{
			COORD largestSize = GetLargestConsoleWindowSize(hConsoleOutput);
			if (FULLSCREEN)
			{
				(*x) = largestSize.X;
				(*y) = largestSize.Y;
			}
			if ((*x) > largestSize.X)
			{
				wchar_t errMsg[200] = { 0 };
				swprintf_s(errMsg, 200, L"Error: X dimension too big (%d > %d)", (*x), largestSize.X);
				Error(errMsg);
			}
			if ((*y) > largestSize.Y)
			{
				wchar_t errMsg[200] = { 0 };
				swprintf_s(errMsg, 200, L"Error: Y dimension too big (%d > %d)", (*y), largestSize.Y);
				Error(errMsg);
			}
		}
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		if (!GetConsoleScreenBufferInfo(hConsoleOutput, &bufferInfo))
			Error(L"Unable to retrieve screen buffer info");

		SMALL_RECT winInfo = bufferInfo.srWindow;
		COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

		if (windowSize.X > (*x) || windowSize.Y > (*y))
		{
			// window size needs to be adjusted before the buffer size can be reduced.
			SMALL_RECT info = { 0,0,(short)(*x) < windowSize.X ? (short)(*x) - 1 : windowSize.X - 1,(short)(*y) < windowSize.Y ? (short)(*y) - 1 : windowSize.Y - 1 };
			if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info))
				Error(L"Resizing window failed!");
		}
		COORD size = { (short)(*x), (short)(*y) };
		if (!SetConsoleScreenBufferSize(hConsoleOutput, size))
			Error(L"Unable to resize screen buffer!");

		SMALL_RECT info = { 0, 0, (short)(*x) - (short)1, (short)(*y) - (short)1 };
		if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info))
			Error(L"Unable to resize window after resizing buffer!");
	}

	void setMouse(bool visible) {
		if (!visible)
			while (ShowCursor(false) >= 0);
	}
	void mouseSpace()
	{
		
	}

	bool windowActive()
	{
		if (!checkActiveWindow) return true;
		if (ConsoleWindow == GetForegroundWindow()) return true;
		else return false;
	}

	void setRequiredModes()
	{
		SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //makes window not resizbale
		// Set flags to allow mouse input, and disable selecting, and support for ANSI escape sequences.	
		if (!SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
			Error(L"Setting The consoles Input modes did not work.");
		if (!SetConsoleMode(hConsoleOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN))
			Error(L"Setting The consoles Output modes did not work.");
	}

	/**************************************************************************************************
	Drawing to the screen functions (draw functions
	**************************************************************************************************/

	int* sysGetPoint(int x, int y, int data[3])
	{
		int slot = xyLoc(x, y);
		data[0] = screenBuffer[slot];
		data[1] = foregroundBuffer[slot];
		data[2] = backgroundBuffer[slot];
	}
	char getChar(int x, int y)
	{
		int data[3] = { 0 };
		sysGetPoint(x, y, data);
		return data[0];
	}
	int getPointFront(int x, int y)
	{
		int data[3] = { 0 };
		sysGetPoint(x, y, data);
		return data[1];
	}
	int getPointBack(int x, int y)
	{
		int data[3] = { 0 };
		sysGetPoint(x, y, data);
		return data[2];
	}
	Point sysDrawPoint(int x, int y, Space screenSpace, char character, int colorFront, int colorBack)
	{
		if (character == '\n' || character == 0)
			Error(L"Error: tried to add newline (\'\\n\') or 0 to screen buffer!");

		int slot = xyLoc(screenSpace.startX + x, screenSpace.startY + y);
		if (character != Default) screenBuffer[slot] = character;
		if (colorFront != Default) foregroundBuffer[slot] = colorFront;
		if (colorBack != Default) backgroundBuffer[slot] = colorBack;
		Point loc = { x, y };
		return loc;
	}
	Space sysDrawRect(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, char character, bool filled, int colorFront, int colorBack)
	{
		Space rectLocation = getSpace(screenSpace, xStart, yStart, xEnd, yEnd);

		for (int x = rectLocation.startX; x <= rectLocation.endX; x++)
			for (int y = rectLocation.startY; y <= rectLocation.endY; y++)
				if (filled || ((x == rectLocation.startX || x == rectLocation.endX) || (y == rectLocation.startY || y == rectLocation.endY)))
					sysDrawPoint(x, y, Screen, character, colorFront, colorBack);

		return rectLocation;
	}
	Space sysDrawLine(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, char character, int colorFront, int colorBack)
	{
		Space line = { xStart, yStart, xEnd, yEnd };
		// this code is a variation of code written by oneLoneCoder
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = xEnd - xStart; dy = yEnd - yStart;
		dx1 = abs(dx); dy1 = abs(dy);
		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
				x = xStart, y = yStart, xe = xEnd;

			else
				x = xEnd, y = yEnd, xe = xStart;

			sysDrawPoint(x, y, screenSpace, character, colorFront, colorBack);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				sysDrawPoint(x, y, screenSpace, character, colorFront, colorBack);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = xStart; y = yStart; ye = yEnd;
			}
			else
			{
				x = xEnd; y = yEnd; ye = yStart;
			}
			sysDrawPoint(x, y, screenSpace, character, colorFront, colorBack);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				sysDrawPoint(x, y, screenSpace, character, colorFront, colorBack);
			}
		}
		return line;
	}
	void sysDrawTriange(int x1, int y1, int x2, int y2, int x3, int y3, Space screenSpace, char character, bool filled, int colorFront, int colorBack)
	{
		sysDrawLine(x1, y1, x2, y2, screenSpace, character, colorFront, colorBack);
		sysDrawLine(x2, y2, x3, y3, screenSpace, character, colorFront, colorBack);
		sysDrawLine(x1, y1, x3, y3, screenSpace, character, colorFront, colorBack);
	}
	Space sysDrawCircle(int x, int y, Space screenSpace, int radius, char character, bool filled, int colorFront, int colorBack)
	{
		Space circleSpace = { 0, 0, 0, 0 };
		if (x == Centered) x = center(1, screenSpace, X), circleSpace.startX = x - radius, circleSpace.endX = x + radius;
		else x = screenSpace.startX + x - 1, circleSpace.startX = x, circleSpace.endX = x + radius * 2;

		if (y == Centered) y = center(1, screenSpace, Y), circleSpace.startY = y - radius, circleSpace.endY = y + radius;
		else y = screenSpace.startY + y - 1, circleSpace.startY = y, circleSpace.endY = y + radius * 2;
		// this code was modified from the olcConsoleGameEngine on github
		int xVAR = 0, yVAR = radius;
		int p = 3 - 2 * radius;
		if (!radius) return circleSpace;

		while (yVAR >= xVAR) // only formulate 1/8 of circle
		{
			sysDrawPoint(x - xVAR, y - yVAR, Screen, character, colorFront, colorBack);
			sysDrawPoint(x - xVAR, y - yVAR, Screen, character, colorFront, colorBack);//upper left left
			sysDrawPoint(x - yVAR, y - xVAR, Screen, character, colorFront, colorBack);//upper upper left
			sysDrawPoint(x + yVAR, y - xVAR, Screen, character, colorFront, colorBack);//upper upper right
			sysDrawPoint(x + xVAR, y - yVAR, Screen, character, colorFront, colorBack);//upper right right
			sysDrawPoint(x - xVAR, y + yVAR, Screen, character, colorFront, colorBack);//lower left left
			sysDrawPoint(x - yVAR, y + xVAR, Screen, character, colorFront, colorBack);//lower lower left
			sysDrawPoint(x + yVAR, y + xVAR, Screen, character, colorFront, colorBack);//lower lower right
			sysDrawPoint(x + xVAR, y + yVAR, Screen, character, colorFront, colorBack);//lower right right
			if (p < 0) p += 4 * xVAR++ + 6;
			else p += 4 * (xVAR++ - yVAR--) + 10;
		}
		/*
		if (filled)
		{
			// Taken from wikipedia
			int xVAR = 0;
			int yVAR = radius;
			int p = 3 - 2 * radius;

			auto drawline = [&](int sx, int ex, int ny)
			{
				for (int i = sx; i <= ex; i++)
					Draw(i, ny, c, col);
			};

			while (y >= x)
			{
				// Modified to draw scan-lines instead of edges
				drawline(xc - x, xc + x, yc - y);
				drawline(xc - y, xc + y, yc - x);
				drawline(xc - x, xc + x, yc + y);
				drawline(xc - y, xc + y, yc + x);
				if (p < 0) p += 4 * x++ + 6;
				else p += 4 * (x++ - y--) + 10;
			}
		}*/
		return circleSpace;
	}
	Space sysDrawImage(int x, int y, Space screenSpace, Image inputImage)
	{
		Space rectLocation = getSpace(screenSpace, x, y, (x == Centered) ? inputImage.width : x + inputImage.width - 1,
			(y == Centered) ? inputImage.height : y + inputImage.height - 1);

		int colorx = 0, colory = 0, y2, x2;
		for (x2 = rectLocation.startX; x2 <= rectLocation.endX; x2++)
		{
			for (y2 = rectLocation.startY; y2 < rectLocation.endY; y2++)
			{
				int color = inputImage.colorArray[colorx][colory];
				if (color == -1) color = Default;
				sysDrawPoint(x2, y2, Screen, Default, Default, color);
				colory++;
			}
			colory = 0, colorx++;
		}
		return rectLocation;
	}
	Space sysDrawFontChar(int x, int y, Space screenSpace, char character, int colorFront, int colorBack)
	{
		Space letterSpace = { x, y, x + 8, y + 8 };
		const unsigned char* letter = font8x8_basic[character];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				int set = letter[i] & 1 << j;
				sysDrawPoint(x + j, y + i, screenSpace, Default, colorFront, set ? colorBack : Default);
			}
		}
		return letterSpace;
	}
	Space sysDrawText(int x, int y, Space screenSpace, const char* text, int fontType, int colorFront, int colorBack)
	{
		int i = 0;
		while (text[i] != '\n' && text[i] != 0)
			i++;

		int textWidth = i * ((fontType == EightBit) ? 8 : 1);
		if (fontType == EightBit)
			textWidth -= 2;

		Space textSpace = getSpace(screenSpace, x, y, (x == Centered) ? textWidth : x + textWidth, (fontType == EightBit) ? 8 : 1);

		int slot = 0;
		x = textSpace.startX, y = textSpace.startY;

		int xPrev = textSpace.startX;
		while (text[slot] != 0)
		{
			if (text[slot] == '\n')
				x = xPrev, y += (fontType == EightBit) ? 8 : 1;

			else
			{
				if (fontType == EightBit) sysDrawFontChar(x, y, Screen, text[slot], colorFront, colorBack);
				else sysDrawPoint(x, y, Screen, text[slot], colorFront, colorBack);
				x += (fontType == EightBit) ? 8 : 1;
			}
			slot++;
		}
		return textSpace;
	}
	Space sysDrawInt(int x, int y, Space screenSpace, int number, int fontType, int colorFront, int colorBack)
	{
		int numLength = 0, numCpy = number;
		char text[30] = { 0 };
		while (numCpy != 0)
		{
			numCpy = numCpy / 10;
			numLength++;
		}
		_itoa(number, text, 10);
		return sysDrawText(x, y, screenSpace, text, fontType, colorFront, colorBack);
	}
	Space sysDrawOutline(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, int colorFront, int colorBack)
	{
		Space windowSpace = { 0,0,0,0 };
		if (xStart == Centered) windowSpace.startX = center(xEnd, screenSpace, X), windowSpace.endX = windowSpace.startX + xEnd - 1;
		else windowSpace.startX = xStart, windowSpace.endX = xEnd;

		if (yStart == Centered) windowSpace.startY = center(yEnd, screenSpace, Y), windowSpace.endY = windowSpace.startY + yEnd - 1;
		else windowSpace.startY = yStart, windowSpace.endY = yEnd;

		//draw it
		int tl = 218, tr = 191, bl = 192, br = 217, rl = 179, tb = 196;

		for (int x = windowSpace.startX; x <= windowSpace.endX; x++)
			for (int y = windowSpace.startY; y <= windowSpace.endY; y++)
			{
				//if we are in the first column or the last column.
				if (y == windowSpace.startY || y == windowSpace.endY)
				{
					if (y == windowSpace.startY && x == windowSpace.startX) sysDrawPoint(x, y, screenSpace, tl, colorFront, colorBack);
					else if (y == windowSpace.startY && x == windowSpace.endX) sysDrawPoint(x, y, screenSpace, tr, colorFront, colorBack);
					else if (y == windowSpace.endY && x == windowSpace.startX) sysDrawPoint(x, y, screenSpace, bl, colorFront, colorBack);
					else if (y == windowSpace.endY && x == windowSpace.endX) sysDrawPoint(x, y, screenSpace, br, colorFront, colorBack);
					else sysDrawPoint(x, y, screenSpace, tb, colorFront, colorBack);
				}
				else if (x == windowSpace.startX || x == windowSpace.endX)
					sysDrawPoint(x, y, screenSpace, rl, colorFront, colorBack);
			}
		return windowSpace;
	}
	Space sysDrawColorBuffer(int x, int y, Space screenSpace, int* buffer, int width, int height)
	{
		Space buffSpace = getSpace(screenSpace, x, y, (x == Centered) ? width: x + width, (y == Centered) ? height : y + height);

		int realX = 0, realY = 0;
		for (int xi = buffSpace.startX; xi < buffSpace.endX; xi++)
		{
			for (int yi = buffSpace.startY; yi < buffSpace.endY; yi++)
			{
				sysDrawPoint(xi, yi, Screen, Default, Default, buffer[realY * width + realX]);
				realY++;
			}
			realY = 0;
			realX++;
		}
		return buffSpace;
	}

	void drawTriange(int x1, int y1, int x2, int y2, int x3, int y3, int color) { sysDrawTriange(x1, y1, x2, y2, x3, y3, Screen, Default, false, Default, color); }
	void drawLine(int xStart, int yStart, int xEnd, int yEnd, int color) { sysDrawLine(xStart, yStart, xEnd, yEnd, Screen, Default, Default, color); }

	Space drawRect(int xStart, int yStart, int xEnd, int yEnd, int color){return sysDrawRect(xStart, yStart, xEnd, yEnd, Screen, Default, false, Default, color);}
	Space drawRectFilled(int xStart, int yStart, int xEnd, int yEnd, int color){return sysDrawRect(xStart, yStart, xEnd, yEnd, Screen, Default, true, Default, color);}
	Space drawCircle(int x, int y, int radius, int color){return sysDrawCircle(x, y, Screen, radius, Default, false, Default, color);}
	Space drawImage(int x, int y, Image img){return sysDrawImage(x, y, Screen, img);}
	Space drawText(int x, int y, const char* text, int fontType, int color){return sysDrawText(x, y, Screen, text, fontType, (fontType == EightBit) ? defaultFrontColor : color, (fontType == EightBit) ? (color == Default) ? defaultFrontColor : color : defaultBackColor);}
	Point drawPoint(int x, int y, int colorBack){return sysDrawPoint(x, y, Screen, Default, Default, colorBack);}
	Point drawChar(int x, int y, char character, int colorFront){return sysDrawPoint(x, y, Screen, character, colorFront, Default);}

	Space drawInt(int x, int y, int number, int fontType, int color){return sysDrawInt(x,y,Screen,number,fontType,(fontType==EightBit)?defaultFrontColor:color,(fontType==EightBit)?(color==Default)?defaultFrontColor:color:defaultBackColor);}
	Space drawOutline(int xStart, int yStart, int xEnd, int yEnd, int color){return sysDrawOutline(xStart, yStart, xEnd, yEnd, Screen, color, Default);}
	Space drawColorBuffer(int x, int y, int* buffer, int width, int height){return sysDrawColorBuffer(x, y, Screen, buffer, width, height);}
	void clearScreen(){sysDrawRect(0, 0, Width(Screen), Height(Screen), Screen, DEFAULT_CHARACTER, true, defaultFrontColor, defaultBackColor);}

	/**************************************************************************************************
	Input Functions (also related to windows, wont work cross platform)
	**************************************************************************************************/
	Key key(int whichKey)
	{
		bool pressed = false;
		if ((GetAsyncKeyState(allKeys[whichKey].letter) & 0x8000) && windowActive())
			pressed = true;

		if (pressed == true && allKeys[whichKey].held == false)
		{
			allKeys[whichKey].pressed = true;
			allKeys[whichKey].released = false;
		}
		else if (pressed == false && allKeys[whichKey].held == true)
			allKeys[whichKey].released = true;

		else
		{
			allKeys[whichKey].pressed = false;
			allKeys[whichKey].released = false;
		}

		allKeys[whichKey].held = pressed;
		return allKeys[whichKey];
	}

	bool textBoxInput(char* outputString, int outputStringLength)
	{
		int nextSlot = strlen(outputString);
		for (int i = 0; i < AMOUNT_KEYS; i++)
			if (key(i).pressed && windowActive())
			{
				if (allKeys[i].letter == allKeys[Esc].letter || allKeys[i].letter == allKeys[Enter].letter)
				{
					allKeys[i].pressed = false;
					return false;
				}
				else if (allKeys[i].letter == allKeys[Spacebar].letter && (signed)strlen(outputString) < outputStringLength - 1)
				{
					outputString[nextSlot] = ' ';
					break;
				}
				else if (allKeys[i].letter == allKeys[Comma].letter)
					outputString[nextSlot] = ',';
				
				else if (allKeys[i].letter == allKeys[Period].letter)
					outputString[nextSlot] = '.';
				
				else if (allKeys[i].letter == allKeys[Colon].letter)
				{
					if (key(Shift).held)
						outputString[nextSlot] = ':';
					else
						outputString[nextSlot] = ';';
				}
				else if (allKeys[i].letter == allKeys[Slash].letter)
				{
					if (key(Shift).held)
						outputString[nextSlot] = '?';
					else
						outputString[nextSlot] = '/';
				}
				else if (allKeys[i].letter == allKeys[Backspace].letter)
					outputString[nextSlot - 1] = 0;

				else if ((signed)strlen(outputString) < outputStringLength - 1 && (allKeys[i].letter != allKeys[Shift].letter) && (allKeys[i].letter != allKeys[LeftM].letter) && (allKeys[i].letter != allKeys[RightM].letter))
				{
					if (!key(Shift).held)
						outputString[nextSlot] = tolower(key(i).letter);
					else 
						outputString[nextSlot] = key(i).letter;
				}
			}
		return true;
	}

	/**************************************************************************************************
	Handing console (creating buffers, destroying buffers, rendering buffers, etc).
	**************************************************************************************************/

	int terminate(void)
	{
		terminated = true;
		if (SetConsoleOutputCP(65001) == 0) Error(L"Changing codepage back to default failed.");

		//free(screenBufferFull);
		//free(backgroundBuffer);
		//free(foregroundBuffer);
		//free(screenBuffer);

		return 0;
	}
	void initalize(const char* title, int width, int height, int bufferFontWidth, int bufferFontHeight, int defaultFront, int defaultBack)
	{
		strcpy(windowTitle, title);
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		if (hConsoleOutput == 0) Error(L"Getting console output handle didnt work.\n");

		hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		ConsoleWindow = GetConsoleWindow();

		if (FULLSCREEN) checkActiveWindow = false;

		//set default values
		if (defaultFront != Default) defaultFrontColor = defaultFront;
		if (defaultBack != Default) defaultBackColor = defaultBack;
		if (width != Default) buffW = width;
		if (height != Default) buffH = height;
		if (bufferFontWidth != Default) fontWidth = bufferFontWidth;
		if (bufferFontHeight != Default) fontHeight = bufferFontHeight;

		SetFont(fontWidth, fontHeight, FONT_WEIGHT, 65001);
		SetConsoleWindowSize(&buffW, &buffH);

		Screen.startX = 0, Screen.startY = 0, Screen.endX = buffW, Screen.endY = buffH;

		printf("\x1b[?25l"); // hide the console cursor
		setRequiredModes();

		if ((int)title != Default) SetConsoleTitleA(title);
		else SetConsoleTitleA("AMZG Studio - ACREngine - Github");
		if (terminated == false) terminate();

		screenBufferFull = (char*)malloc(sizeof(char) * ((buffW * buffH) * ANSI_STR_LEN + 1));
		screenBuffer = (char*)malloc(sizeof(char) * ((buffW * buffH) + 1));
		foregroundBuffer = (int*)malloc(sizeof(int) * (buffW * buffH));
		backgroundBuffer = (int*)malloc(sizeof(int) * (buffW * buffH));

		for (int i = 0; i < ((buffW * buffH) * ANSI_STR_LEN + 1); i++) screenBufferFull[i] = 0;
		for (int i = 0; i < (buffW * buffH); i++)
		{
			foregroundBuffer[i] = defaultFrontColor;
			backgroundBuffer[i] = defaultBackColor;
			screenBuffer[i] = DEFAULT_CHARACTER;
		}
		for (int i = 0; i < AMOUNT_KEYS; i++)
		{
			allKeys[i].held = false;
			allKeys[i].pressed = false;
			allKeys[i].released = false;
			allKeys[i].letter = 0;
		}

		int select = 0;
		for (char letter = 'A'; letter <= 'Z'; letter++)
		{
			allKeys[select].letter = letter;
			select++;
		}
		allKeys[Up].letter = VK_UP, allKeys[Down].letter = VK_DOWN, allKeys[Left].letter = VK_LEFT, allKeys[Right].letter = VK_RIGHT;
		allKeys[Enter].letter = VK_RETURN, allKeys[Esc].letter = VK_ESCAPE, allKeys[LeftM].letter = VK_LBUTTON, allKeys[RightM].letter = VK_RBUTTON;
		allKeys[Spacebar].letter = VK_SPACE, allKeys[Shift].letter = VK_SHIFT, allKeys[Comma].letter = VK_OEM_COMMA, allKeys[Period].letter = VK_OEM_PERIOD, 
		allKeys[Colon].letter = VK_OEM_1, allKeys[Slash].letter = VK_OEM_2, allKeys[QuestionMark].letter = '?', allKeys[Backspace].letter = VK_BACK;
		
		allKeys[Num0].letter = '0', allKeys[Num1].letter = '1', allKeys[Num2].letter = '2', allKeys[Num3].letter = '3', allKeys[Num4].letter = '4';
		allKeys[Num5].letter = '5', allKeys[Num6].letter = '6', allKeys[Num7].letter = '7', allKeys[Num8].letter = '8', allKeys[Num9].letter = '9', 
		terminated = false;

		QueryPerformanceCounter(&start);
		srand((unsigned int)start.QuadPart);
	}

	void addColorToBuffer(int foregroundColor, int backgroundColor)
	{
		screenBufferFull[nextOpenSlot] = '\033', screenBufferFull[nextOpenSlot + 1] = '[';
		nextOpenSlot += 2;
		if (foregroundColor != -1)
		{
			screenBufferFull[nextOpenSlot] = '3', screenBufferFull[nextOpenSlot + 1] = '8';
			screenBufferFull[nextOpenSlot + 2] = ';', screenBufferFull[nextOpenSlot + 3] = '5';
			screenBufferFull[nextOpenSlot + 4] = ';';
			nextOpenSlot += 5;
			char buffer[4] = { 0 };
			_itoa(foregroundColor, buffer, 10);
			strncpy(screenBufferFull + nextOpenSlot, buffer, 3);
			nextOpenSlot += 3;
		}
		if (foregroundColor != -1 && backgroundColor != -1) screenBufferFull[nextOpenSlot] = ';', nextOpenSlot++;
		if (backgroundColor != -1)
		{
			screenBufferFull[nextOpenSlot] = '4', screenBufferFull[nextOpenSlot + 1] = '8';
			screenBufferFull[nextOpenSlot + 2] = ';', screenBufferFull[nextOpenSlot + 3] = '5';
			screenBufferFull[nextOpenSlot + 4] = ';';
			nextOpenSlot += 5;
			char buffer[4] = { 0 };
			_itoa(backgroundColor, buffer, 10);
			strncpy(screenBufferFull + nextOpenSlot, buffer, 3);
			nextOpenSlot += 3;
		}
		screenBufferFull[nextOpenSlot] = 'm';
		nextOpenSlot++;
	}

	void addCharToBuffer(char input)
	{
		screenBufferFull[nextOpenSlot] = input;
		nextOpenSlot++;
	}
	void render(bool clear)
	{
		//get mouse location
		POINT cursor_pos = { 0, 0 };
		INPUT_RECORD irInBuf[32];
		DWORD events = 0;

		// Wait for the events.
		GetNumberOfConsoleInputEvents(hConsoleInput, &events);
		if (events > 0)
			if (!ReadConsoleInput(hConsoleInput, irInBuf, events, &events))
				Error(L"failed reading console inputs\n");

		// get mouse events
		for (DWORD i = 0; i < events; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case MOUSE_EVENT:
			{
				switch (irInBuf[i].Event.MouseEvent.dwEventFlags)
				{
				case MOUSE_MOVED:
					Mouse.x = irInBuf[i].Event.MouseEvent.dwMousePosition.X;
					Mouse.y = irInBuf[i].Event.MouseEvent.dwMousePosition.Y;
					break;

				case MOUSE_HWHEELED:
					Mouse.scrollW = irInBuf[i].Event.MouseEvent.dwButtonState;
					break;

				case MOUSE_WHEELED:
					Mouse.scrollH = irInBuf[i].Event.MouseEvent.dwButtonState;
					break;

				default:
					break;
				}
			}
			break;

			default:
				break;
			}
		}
		// create buffer to render
		screenBufferFull[0] = '\033', screenBufferFull[1] = '[', screenBufferFull[2] = '0';
		screenBufferFull[3] = ';', screenBufferFull[4] = '0', screenBufferFull[5] = 'H';
		nextOpenSlot = 6;
		int currentForeground = -1, currentBackground = -1;
		for (int i = 0; i < buffW * buffH; i++)
		{
			if (foregroundBuffer[i] != currentForeground && backgroundBuffer[i] != currentBackground)
			{
				currentForeground = foregroundBuffer[i];
				currentBackground = backgroundBuffer[i];
				addColorToBuffer(foregroundBuffer[i], backgroundBuffer[i]);
			}
			else if (backgroundBuffer[i] != currentBackground)
			{
				currentBackground = backgroundBuffer[i];
				addColorToBuffer(-1, backgroundBuffer[i]);
			}
			else if (foregroundBuffer[i] != currentForeground)
			{
				currentForeground = foregroundBuffer[i];
				addColorToBuffer(foregroundBuffer[i], -1);
			}
			addCharToBuffer(screenBuffer[i]);
		}

		//render	
		if (!WriteConsoleA(hConsoleOutput, screenBufferFull, nextOpenSlot, NULL, NULL))
			Error(L"Rendering failed.");

		if (clear == true) 
			clearScreen();

		if (!QueryPerformanceFrequency(&frequency))
			Error(L"Getting Performance Frequency Failed!");

		if (!QueryPerformanceCounter(&end))
			Error(L"Getting Performace Counter Failed!");

		deltaTime = (float)(end.QuadPart - start.QuadPart) / (float)frequency.QuadPart;
		
		start = end;
		fps = 1.0f / deltaTime;

		char currentTitle[200] = { 0 };
		
	#if defined(SHOW_FPS) && !defined(NO_ACRE_WATERMARK)
		sprintf(currentTitle, "%s - ACREngine - %.2f fps", windowTitle, fps);
		
	#elif defined(SHOW_FPS) && defined(NO_ACRE_WATERMARK)
		sprintf(currentTitle, "%s - %.2f fps", windowTitle, fps);

	#elif !defined(NO_ACRE_WATERMARK)
		sprintf(currentTitle, "%s - ACREngine", windowTitle);

	#else
		strcat(currentTitle, windowTitle);

	#endif
		SetConsoleTitleA(currentTitle);

		}
#endif