/*		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		      _    ____ ____  _____             _          __     _______       
		     / \  / ___|  _ \| ____|_ __   __ _(_)_ __   __\ \   / /___ /   _   
		    / _ \| |   | |_) | |__ | '_ \ / _` | | '_ \ / _ \ \ / /  |_ \ _| |_ 
		   / ___ \ |___|  _ <| |___| | | | (_| | | | | |  __/\ V /  ___) |_   _|
		  /_/   \_\____|_| \_\_____|_| |_|\__, |_|_| |_|\___| \_/  |____/  |_|  
                                         |___/                                 
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		ACREngine, is an advanced game engine for beginners, that runs entirely in the 
		console! This can be used for anything. from making console applications with 
		colors and mouse/keyboard input, to creating fully fledged and advanced games. 
		The possiblities are endless! If you use ACREngine, I would appreciate you 
		giving me credit, but you don't have to. ¯\_(ツ)_/¯

		For information on what this is, and how to use it, go to the github repo:
		https://github.com/AMZGstudio/ACREngine

		|-------- Creator --------|
			AMZGstudio (solo)

		|------ Compilation ------|
			To use gcc, simply use the command:
			gcc -o example.exe example.c				

		|-------- License --------|
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

		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*/

#ifndef ACRE_INCLUDES
#define ACRE_INCLUDES
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		#define _CRT_SECURE_NO_WARNINGS 1
		
		#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
			#define _WIN32_WINNT 0x0601
		#else
		#define _WIN32_WINNT 0x0601
		#endif	

		#include <stdio.h>
		#include <windows.h>
		#include <winbase.h>
		#include <wincon.h>
		#include <stdbool.h>
		#include <ctype.h>

		#ifdef __GNUC__
		#ifdef __cplusplus
				extern "C" {
		#endif
				typedef struct _CONSOLE_FONT_INFOEX
				{
					ULONG cbSize;
					DWORD nFont;
					COORD dwFontSize;
					UINT  FontFamily;
					UINT  FontWeight;
					WCHAR FaceName[LF_FACESIZE];
				}CONSOLE_FONT_INFOEX, * PCONSOLE_FONT_INFOEX;
				BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
				BOOL WINAPI SetConsoleDisplayMode(HANDLE hConsoleOutput, DWORD  dwFlags, PCOORD lpNewScreenBufferDimensions);
		
		#ifdef __cplusplus
						}
		#endif

			#define CONSOLE_FULLSCREEN_MODE 1
			#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
			#define DISABLE_NEWLINE_AUTO_RETURN 0x0008
		#endif	
	#else
		#error ACRE only supports windows
	#endif	
#endif

#ifndef ACRE_DECLARATIONS
#define ACRE_DECLARATIONS
	#define ACRE_31_COMPATIBLE // its in here, because we only want it to be defined once, regardless of if ACRE_START is defined.

	// used for triangle drawing
	#define SWAP(x,y) do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)

	// all structs used by ACRE
	typedef struct Point { int x, y; } Point;
	typedef struct Space { int xStart, yStart, xEnd, yEnd; } Space;
	typedef struct MOUSE { int x, y; int scrollH, scrollW; } MOUSE;
	typedef struct Font { int _w, width, height, spacingX, spacingY; const unsigned char *data; } Font;
	typedef struct Area { int width, height; short* colFront, * colBack; char* characters; bool drawFront, drawBack, drawText; } Area;
	typedef struct Key { bool pressed, held, released; char character; int code; } Key;

	extern Area Screen;
	extern Space ScreenSpace;
	// all enums
	enum KEYS {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Up, Down, Left, Right,
		Enter, Esc, LMB, RMB, Spacebar, Shift, Alt, Tab, Comma, Period, Colon, Slash, QuestionMark, Backspace,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9
	};
	enum ACRE_TYPES {Thirds = -502, Centered = -501, Default = -1 };

	enum COLORS { 

		Black = 16, VeryDarkGrey = 234, DarkGrey = 237, Grey = 243, LightGrey = 247, White = 255,
		Red = 196,  VeryDarkRed = 52,   DarkRed = 124,  Pink = 218,
		Orange=202, Brown = 130,		DarkOrange=166, Tan = 180,
		Yellow=226, Olive=100,		    DarkYellow=184, LightYellow=228,
		Green=40,   VeryDarkGreen=22,   DarkGreen=34,   LightGreen=83, 
		Cyan=37,    VeryDarkCyan=24,    DarkCyan=31,    LightCyan=44,
		Blue=33,    Navy=17,		    DarkBlue=20,    LightBlue=75,
		Purple=93,  VeryDarkPurple=54,  DarkPurple=91,  LightPurple=129,
		
		Magenta=127
	};

	enum SPECIAL_CHARS {
		LightShade = 176, MediumShade = 177, DarkShade = 178, FullBlock = 219, LowerHalfBlock = 220,
		LeftHalfBlock = 221, RightHalfBlock = 222, UpperHalfBlock = 223
	};

	typedef unsigned char Color;
	// this must be overriden by the user, which acts as the main file.

	void start();
	// variable declarations
	extern Color defaultFrontColor, defaultBackColor;
	extern float fps;
	extern MOUSE Mouse;
	extern Font EightBit;

	// function declarations

	Area loadSprite(const char* spriteFilePath);
	void makeSprite(Area areaToMakeSprite, char* spriteFilePath);

	bool isWindowActive();
	int Width(Area area);
	int Height(Area area);
	int spWidth(Space space);
	int spHeight(Space space);
	int Center(int objLength, int worldLength);
	int Random(int rangeStart, int rangeEnd);

	float amntPerSec(float amount);
	Space calcSpace(Space prevSpace, int xStart, int yStart, int width, int height);
	void intToStr(char* string, int num);
	float map(float numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd);
	inline float clampFloat(float numToClamp, float min, float max);
	inline int clampInt(int numToClamp, int min, int max);

	void clampSpace(Space* space, Space spaceToClampTo);
	void calcXterm(Color color, Color* r, Color* g, Color* b);
	Color calcColor(int red, int green, int blue);
	int txtWidth(const char* string, Font fontType);
	int txtHeight(const char* string, Font fontType);
	void setDefaultDrawArea(Area* ar);
	bool legalArea(Area area);
	bool wasResized();

	// collision functions
	bool pointSpaceOverlap(int x, int y, Space screenSpace);
	bool spaceOverlap(Space space1, Space space2);
	
	void setFullscreen(bool fullscreen);

	Color sysGetFrontColor(int x, int y, Area area);
	Color sysGetBackColor(int x, int y, Area area);
	char sysGetChar(int x, int y, Area area);
	
	Color getFrontColor(int x, int y);
	Color getBackColor(int x, int y);
	char getChar(int x, int y);
	
	Point sysDrawPixel(int x, int y, Area area, char character, short front_color, short back_color);
	void sysDrawRect(int xStart, int yStart, int xEnd, int yEnd, Area area, bool filled, char character, short front_color, short back_color);
	void sysDrawCircle(int x, int y, Area area, int radius, bool filled, char character, short front_color, short back_color);
	void sysDrawLine(int xStart, int yStart, int xEnd, int yEnd, Area area, char character, short front_color, short back_color);
	void sysDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Area area, bool filled, char character, short front_color, short back_color);
	void sysDrawText(int x, int y, Area area, const char* text, Font fontType, short front_color, short back_color);
	void sysDrawNumber(int x, int y, Area area, double number, int numDecimal, Font fontType, short front_color, short back_color);
	void sysDrawArea(int x, int y, Area area, Area areaToDraw);
	void sysDrawPartialArea(int x, int y, Area area, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY);
	
	Space spDrawPixel(int x, int y, Space space, short color);
	Space spDrawChar(int x, int y, Space space, char character, short color);
	Space spDrawRect(int xStart, int yStart, int xEnd, int yEnd, Space space, bool filled, short color);
	Space spDrawCircle(int x, int y, Space space, int radius, bool filled, short color);
	Space spDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Space space, bool filled, short color);
	Space spDrawLine(int xStart, int yStart, int xEnd, int yEnd, Space space, short color);
	Space spDrawText(int x, int y, Space space, const char* text, Font fontType, short color);
	Space spDrawNumber(int x, int y, Space space, double number, int numDecimal, Font fontType, short color);
	Space spDrawArea(int x, int y, Space space, Area areaToDraw);
	Space spDrawPartialArea(int x, int y, Space space, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY);

	Space drawPixel(int x, int y, short color);
	Space drawChar(int x, int y, char character, short color);
	Space drawRect(int xStart, int yStart, int xEnd, int yEnd, short color);
	Space drawRectFilled(int xStart, int yStart, int xEnd, int yEnd, short color);
	Space drawCircle(int x, int y, int radius, short color);
	Space drawCircleFilled(int x, int y, int radius, short color);

	Space drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short color);
	Space drawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, short color);

	Space drawLine(int xStart, int yStart, int xEnd, int yEnd, short color);
	Space drawText(int x, int y, const char* text, Font fontType, short color);
	Space drawNumber(int x, int y, double number, Font fontType, short color);
	Space drawArea(int x, int y, Area areaToDraw);
	Space drawPartialArea(int x, int y, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY);

	void reset(Area area);
	Key key(int whichKey);
	bool textBoxInput(char* outputString, size_t length);

	Area createArea(int width, int height, short front_color, short back_color);
	void deleteArea(Area* area);
	void initialize(const char* title, int width, int height, int fontWidth, int fontHeight, short frontColor, short backColor);
	void render(bool clearScreen);
	void terminateACRE();

#endif

#ifdef ACRE_START
	#undef ACRE_START
	#ifndef ACRE_SYS_DEFS
		#define ACRE_SYS_DEFS
		#define ANSI_STR_LEN 24
		#define AMOUNT_KEYS 54

		#ifndef FPS_COUNTS
			#define FPS_COUNTS 100
		#endif
		#ifndef FONT_WEIGHT
			#define FONT_WEIGHT 500
		#endif
		#ifndef FRONT_COLOR
			#define FRONT_COLOR White
		#endif
		#ifndef BACK_COLOR
			#define BACK_COLOR Black
		#endif
	#ifndef DEFAULT_CHARACTER
		#define DEFAULT_CHARACTER ' '
	#endif
	#ifndef MOUSE_HWHEELED
		#define MOUSE_HWHEELED 0x0008
	#endif
#endif
	char* screenBufferFull = NULL, windowTitle[200] = { 0 };
	size_t nextSlot;

	int _consoleFontWidth = 8, _consoleFontHeight = 16;
	Color defaultFrontColor = FRONT_COLOR, defaultBackColor = BACK_COLOR;
	int defaultScreenWidth = 100, defaultScreenHeight = 30;

	float fps = 0;
	float _pastPerformance[FPS_COUNTS] = { 0 };
	unsigned int _countIndex = 0;

	bool _firstInitialize = true;
	bool _needsResizeCorrection = true;
	bool _hasBeenResized = false;
	bool _finishedFPSLoop = false;
	int _newWidth, _newHeight;
	int _oldWidth, _oldHeight; // the size of the console before setting it to fullscreen
	bool _to_be_fullscreen = false;
	bool _fullscreen = false;

	// windows handles
	HANDLE hConsoleOutput, hConsoleInput;
	HWND ConsoleWindow;

	Area* areaToDrawOn;
	Area Screen = { -1, -1 };
	Space ScreenSpace = { 0 };
	
	//others
	MOUSE Mouse = { 0, 0, 0, 0 };
	Key  allKeys[AMOUNT_KEYS] = { 0 };
	LARGE_INTEGER liStart = { 0 }, liEnd = { 0 }, frequency = { 0 };
	float deltaTime = 0;

	// the eight bit font option in hex
	const unsigned char font8x8_basic[96][8] = {
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},{0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00},{0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x36,0x36,0x7F,0x36,0x7F,0x36,0x36,0x00},{0x0C,0x3E,0x03,0x1E,0x30,0x1F,0x0C,0x00},{0x00,0x63,0x33,0x18,0x0C,0x66,0x63,0x00},
		{0x1C,0x36,0x1C,0x6E,0x3B,0x33,0x6E,0x00},{0x06,0x06,0x03,0x00,0x00,0x00,0x00,0x00},{0x18,0x0C,0x06,0x06,0x06,0x0C,0x18,0x00},
		{0x06,0x0C,0x18,0x18,0x18,0x0C,0x06,0x00},{0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00},{0x00,0x0C,0x0C,0x3F,0x0C,0x0C,0x00,0x00},
		{0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x06},{0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00},
		{0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x00},{0x3E,0x63,0x73,0x7B,0x6F,0x67,0x3E,0x00},{0x0C,0x0E,0x0C,0x0C,0x0C,0x0C,0x3F,0x00},
		{0x1E,0x33,0x30,0x1C,0x06,0x33,0x3F,0x00},{0x1E,0x33,0x30,0x1C,0x30,0x33,0x1E,0x00},{0x38,0x3C,0x36,0x33,0x7F,0x30,0x78,0x00},
		{0x3F,0x03,0x1F,0x30,0x30,0x33,0x1E,0x00},{0x1C,0x06,0x03,0x1F,0x33,0x33,0x1E,0x00},{0x3F,0x33,0x30,0x18,0x0C,0x0C,0x0C,0x00},
		{0x1E,0x33,0x33,0x1E,0x33,0x33,0x1E,0x00},{0x1E,0x33,0x33,0x3E,0x30,0x18,0x0E,0x00},{0x00,0x0C,0x0C,0x00,0x00,0x0C,0x0C,0x00},
		{0x00,0x0C,0x0C,0x00,0x00,0x0C,0x0C,0x06},{0x18,0x0C,0x06,0x03,0x06,0x0C,0x18,0x00},{0x00,0x00,0x3F,0x00,0x00,0x3F,0x00,0x00},
		{0x06,0x0C,0x18,0x30,0x18,0x0C,0x06,0x00},{0x1E,0x33,0x30,0x18,0x0C,0x00,0x0C,0x00},{0x3E,0x63,0x7B,0x7B,0x7B,0x03,0x1E,0x00},
		{0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0x00},{0x3F,0x66,0x66,0x3E,0x66,0x66,0x3F,0x00},{0x3C,0x66,0x03,0x03,0x03,0x66,0x3C,0x00},
		{0x1F,0x36,0x66,0x66,0x66,0x36,0x1F,0x00},{0x7F,0x46,0x16,0x1E,0x16,0x46,0x7F,0x00},{0x7F,0x46,0x16,0x1E,0x16,0x06,0x0F,0x00},
		{0x3C,0x66,0x03,0x03,0x73,0x66,0x7C,0x00},{0x33,0x33,0x33,0x3F,0x33,0x33,0x33,0x00},{0x1E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00},
		{0x78,0x30,0x30,0x30,0x33,0x33,0x1E,0x00},{0x67,0x66,0x36,0x1E,0x36,0x66,0x67,0x00},{0x0F,0x06,0x06,0x06,0x46,0x66,0x7F,0x00},
		{0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00},{0x63,0x67,0x6F,0x7B,0x73,0x63,0x63,0x00},{0x1C,0x36,0x63,0x63,0x63,0x36,0x1C,0x00},
		{0x3F,0x66,0x66,0x3E,0x06,0x06,0x0F,0x00},{0x1E,0x33,0x33,0x33,0x3B,0x1E,0x38,0x00},{0x3F,0x66,0x66,0x3E,0x36,0x66,0x67,0x00},
		{0x1E,0x33,0x07,0x0E,0x38,0x33,0x1E,0x00},{0x3F,0x2D,0x0C,0x0C,0x0C,0x0C,0x1E,0x00},{0x33,0x33,0x33,0x33,0x33,0x33,0x3F,0x00},
		{0x33,0x33,0x33,0x33,0x33,0x1E,0x0C,0x00},{0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00},{0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00},
		{0x33,0x33,0x33,0x1E,0x0C,0x0C,0x1E,0x00},{0x7F,0x63,0x31,0x18,0x4C,0x66,0x7F,0x00},{0x1E,0x06,0x06,0x06,0x06,0x06,0x1E,0x00},
		{0x03,0x06,0x0C,0x18,0x30,0x60,0x40,0x00},{0x1E,0x18,0x18,0x18,0x18,0x18,0x1E,0x00},{0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00},
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},{0x0C,0x0C,0x18,0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0x1E,0x30,0x3E,0x33,0x6E,0x00},
		{0x07,0x06,0x06,0x3E,0x66,0x66,0x3B,0x00},{0x00,0x00,0x1E,0x33,0x03,0x33,0x1E,0x00},{0x38,0x30,0x30,0x3e,0x33,0x33,0x6E,0x00},
		{0x00,0x00,0x1E,0x33,0x3f,0x03,0x1E,0x00},{0x1C,0x36,0x06,0x0f,0x06,0x06,0x0F,0x00},{0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x1F},
		{0x07,0x06,0x36,0x6E,0x66,0x66,0x67,0x00},{0x0C,0x00,0x0E,0x0C,0x0C,0x0C,0x1E,0x00},{0x30,0x00,0x30,0x30,0x30,0x33,0x33,0x1E},
		{0x07,0x06,0x66,0x36,0x1E,0x36,0x67,0x00},{0x0E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00},{0x00,0x00,0x33,0x7F,0x7F,0x6B,0x63,0x00},
		{0x00,0x00,0x1F,0x33,0x33,0x33,0x33,0x00},{0x00,0x00,0x1E,0x33,0x33,0x33,0x1E,0x00},{0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x0F},
		{0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x78},{0x00,0x00,0x3B,0x6E,0x66,0x06,0x0F,0x00},{0x00,0x00,0x3E,0x03,0x1E,0x30,0x1F,0x00},
		{0x08,0x0C,0x3E,0x0C,0x0C,0x2C,0x18,0x00},{0x00,0x00,0x33,0x33,0x33,0x33,0x6E,0x00},{0x00,0x00,0x33,0x33,0x33,0x1E,0x0C,0x00},
		{0x00,0x00,0x63,0x6B,0x7F,0x7F,0x36,0x00},{0x00,0x00,0x63,0x36,0x1C,0x36,0x63,0x00},{0x00,0x00,0x33,0x33,0x33,0x3E,0x30,0x1F},
		{0x00,0x00,0x3F,0x19,0x0C,0x26,0x3F,0x00},{0x38,0x0C,0x0C,0x07,0x0C,0x0C,0x38,0x00},{0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00},
		{0x07,0x0C,0x0C,0x38,0x0C,0x0C,0x07,0x00},{0x6E,0x3B,0x00,0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
	};
	Font EightBit = { 8, 8, 8, 1, 1, (const unsigned char*)font8x8_basic }; //sysDrawFontChar(x, y, Screen, EIGHT_BIT, text[slot], front_color, back_color);
	Font DefaultFont = { 0, 1, 1, 0, 0, NULL };

	/*-------------------------------------------*\
	|			 System Only Functions   		  |
	\*-------------------------------------------*/

	// used for sysDrawTri-angle
	void simple_draw_line(int x1, int x2, unsigned int y, Area area, char charater, short front_color, short back_color)
	{
		if (x1 >= x2) SWAP(x1, x2);
		for (; x1 <= x2; x1++) sysDrawPixel(x1, y, area, charater, front_color, back_color);
	}
	
	void _Error(const char* errorMsg, int line)
	{
		char thing[200] = { 0 };
		sprintf(thing, "ACRError: (LINE:%d): %s", line, errorMsg);
		MessageBoxA(NULL, thing, NULL, MB_OK);
		exit(EXIT_FAILURE);
	}

	inline Space calcSpace(Space prevSpace, int xStart, int yStart, int width, int height)
	{
		Space sp = { prevSpace.xStart, prevSpace.yStart, 0, 0 };

		if (xStart == Centered) sp.xStart += Center(width, spWidth(prevSpace));
		else sp.xStart += xStart;

		if (yStart == Centered) sp.yStart += Center(height, spHeight(prevSpace));
		else sp.yStart += yStart;

		sp.xEnd += sp.xStart + width;
		sp.yEnd += sp.yStart + height;
		return sp;
	}
	
	/*-------------------------------------------*\
	|		 General Functions / Miscelanous   	  |
	\*-------------------------------------------*/

	inline int Width(Area area) { return area.width; }
	inline int Height(Area area) { return area.height; }
	inline int spWidth(Space space) { return abs(space.xEnd - space.xStart); }
	inline int spHeight(Space space) { return abs(space.yEnd - space.yStart); }
	inline int Center(int objLength, int worldLength) { return (worldLength / 2.0f) - (objLength / 2.0f);}
	inline int Random(int rangeStart, int rangeEnd) { return (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;}

	int txtWidth(const char* string, Font fontType)
	{
		size_t maxWidth = 0;
		char stringCpy[1024] = { 0 };
		strcpy(stringCpy, string);

		char* token = strtok(stringCpy, "\n"); // Returns first token

		while (token != NULL) // Keep printing tokens while one of the delimiters present in str[].
		{
			size_t newSize = strlen(token);
			if (newSize > maxWidth)
				maxWidth = newSize;

			token = strtok(NULL, "\n");
		}

		return (int)maxWidth * (fontType.width + fontType.spacingX) - fontType.spacingX; // because last spacing is not existant.
	}

	int txtHeight(const char* string, Font fontType)
	{
		int rows = 1;

		for (int i = 0; string[i]; i++)
			if (string[i] == '\n')
				rows++;
			
		return rows * (fontType.height + 1) - 1;
	}

	bool wasResized()
	{
		if (_hasBeenResized)
		{
			_hasBeenResized = false;
			return true;
		}
		return false;
	}

	float amntPerSec(float amount)
	{
		return amount * deltaTime;
	}

	float map(float numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd)
	{
		float output = (float)numberMapStart + (((float)numberMapEnd - (float)numberMapStart) / ((float)numberEnd - (float)numberBegin)) * ((float)numberToMap - (float)numberBegin);
		return output;
	}
	inline float clampFloat(float numToClamp, float minimum, float maximum)
	{
		return min(max(minimum, numToClamp), maximum);
	}
	inline int clampInt(int numToClamp, int minimum, int maximum)
	{
		return min(max(minimum, numToClamp), maximum);
	}
	void clampSpace(Space* space, Space spaceToClampTo)
	{
		if (!spaceOverlap(*space, spaceToClampTo))
			return;

		space->xStart = clampInt(space->xStart, spaceToClampTo.xStart, spaceToClampTo.xEnd);
		space->yStart = clampInt(space->yStart, spaceToClampTo.yStart, spaceToClampTo.yEnd);
		space->xEnd = clampInt(space->xEnd, spaceToClampTo.xStart, spaceToClampTo.xEnd);
		space->yEnd = clampInt(space->yEnd, spaceToClampTo.yStart, spaceToClampTo.yEnd);
	}

	void intToStr(char* string, int num)
	{
		_itoa(num, string, 10);
	}
	
	void calcXterm(Color color, Color* r, Color* g, Color* b)
	{
		color = (Color)clampInt(color, 0, 255);
		Color vals[6] = { 0,95,135,175,215,255 };

		if (color < 16)
			switch(color)
			{
			case 0: *r = 0, *g = 0, *b = 0; break;
			case 1: *r = 128, *g = 0, *b = 0; break;
			case 2: *r = 0, *g = 128, *b = 0; break;
			case 3: *r = 128, *g = 128, *b = 0; break;
			case 4: *r = 0, *g = 0, *b = 128; break;
			case 5: *r = 128, *g = 0, *b = 128; break;
			case 6: *r = 0, *g = 128, *b = 128; break;
			case 7: *r = 192, *g = 192, *b = 192; break;
			case 8: *r = 128, *g = 128, *b = 128; break;
			case 9: *r = 255, *g = 0, *b = 0; break;
			case 10: *r = 0, *g = 255, *b = 0; break;
			case 11: *r = 255, *g = 255, *b = 0; break;
			case 12: *r = 0, *g = 0, *b = 255; break;
			case 13: *r = 255, *g = 255, *b = 255; break;
			case 14: *r = 0, *g = 255, *b = 255; break;
			case 15: *r = 255, *g = 255, *b = 255; break;
			}	
		else if (color >= 16 && color <= 231)
		{
			color -= 16;
			int num6s = (int)color / 6;
			*b = vals[color % 6];
			*r = (int)(num6s / 6.0f); // keep as a 0...5 number, to be used for green.
			*g = vals[num6s - ((*r) * 6)];
			*r = vals[*r]; // then convert it to 0...255;
		}
		else if (color > 231)
		{
			color -= 232;
			*r = 8 + color * 10;
			*g = 8 + color * 10;
			*b = 8 + color * 10;
		}
	}

	Color calcColor(int red, int green, int blue) // modified from internet
	{
		red = clampInt(red, 0, 255);
		green = clampInt(green, 0, 255);
		blue = clampInt(blue, 0, 255);

		#define v2ci(v) (v < 48 ? 0 : v < 115 ? 1 : (v - 35) / 40)
		int ir = v2ci(red), ig = v2ci(green), ib = v2ci(blue);   // 0..5 each
		#define color_index() (36 * ir + 6 * ig + ib)  /* 0..215, lazy evaluation */

		int average = (red + green + blue) / 3;
		int gray_index = average > 238 ? 23 : (average - 3) / 10;  // 0..23

		static const int i2cv[6] = { 0, 0x5f, 0x87, 0xaf, 0xd7, 0xff };
		int cr = i2cv[ir], cg = i2cv[ig], cb = i2cv[ib];  // r/g/b, 0..255 each
		int gv = 8 + 10 * gray_index;  // same value for r/g/b, 0..255

		#define dist_square(A,B,C, a,b,c) ((A-a)*(A-a) + (B-b)*(B-b) + (C-c)*(C-c))
		int color_err = dist_square(cr, cg, cb, red, green, blue);
		int gray_err = dist_square(gv, gv, gv, red, green, blue);
		return color_err <= gray_err ? 16 + color_index() : 232 + gray_index;
	}

	/*-------------------------------------------*\
	|		    Image Handling Functions		  |
	\*-------------------------------------------*/

	int readColor(FILE* spriteFile)
	{
		int selected = 0;
		char ch, color[5] = { 0 };
		while ((ch = fgetc(spriteFile)) != ';' && ch != '\n')
			color[selected] = ch, selected++;

		return atoi(color);
	}

	Area loadSprite(const char* spriteFilePath)
	{
		char ch;
		FILE* spriteFile = fopen(spriteFilePath, "r");
		bool includeText = false;

		if (spriteFile == NULL)
		{
			char msg[100] = "Opening ACRE file: ";
			sprintf(msg, "Opening ACRE file: %s", spriteFilePath);
			_Error(msg, __LINE__);
		}

		while ((ch = fgetc(spriteFile)) != ';')
		{
			if(ch == ':')
				if(fgetc(spriteFile) == 'T')
					includeText = true;
		}
		int nWidth = readColor(spriteFile), nHeight = readColor(spriteFile);

		Area sprite = createArea(nWidth, nHeight, Default, Default);
		sprite.drawText = includeText;

		for (int j = 0; j < nHeight; j++)
		{
			for (int i = 0; i < nWidth; i++)
			{
				sprite.colBack[j * nWidth + i] = readColor(spriteFile);
				sprite.characters[j * nWidth + i] = fgetc(spriteFile);
			}
			fgetc(spriteFile);
		}
		fclose(spriteFile);
		return sprite;
	}

	void makeSprite(Area areaToMakeSprite, char* spriteFilePath)
	{
		char newPath[200] = { 0 };
		strcat(newPath, spriteFilePath);

		// if .acre doesnt exist in the path, then append it to the end
		if (strstr(newPath, ".acre") == NULL)
			strcat(newPath, ".acre");
		
		char extraModes[5] = { 0 };

		if (areaToMakeSprite.drawText)
			strcat(extraModes, ":T");

		FILE* file = fopen(newPath, "w");
		fprintf(file, "acrev3.1%s;%d;%d\n", extraModes, areaToMakeSprite.width, areaToMakeSprite.height);
		
		for (int y = 0; y < areaToMakeSprite.height; y++)
		{
			for (int x = 0; x < areaToMakeSprite.width; x++)
				fprintf(file, "%d;%c", areaToMakeSprite.colBack[y * areaToMakeSprite.width + x], areaToMakeSprite.characters[y * areaToMakeSprite.width + x]);
			
			if (y != areaToMakeSprite.height - 1)
				fwrite("\n", 1, 1, file);
		}
		fclose(file);
	}

	void setDefaultDrawArea(Area* ar)
	{
		areaToDrawOn = ar;
	}
	bool legalArea(Area area)
	{
		return (area.width != -1 && area.height != -1);
	}

	/*-------------------------------------------*\
	|		       Collision Functions	     	  |
	\*-------------------------------------------*/

	bool pointSpaceOverlap(int x, int y, Space screenSpace)
	{
		return (x >= screenSpace.xStart && x < screenSpace.xEnd && y >= screenSpace.yStart && y < screenSpace.yEnd);
	}

	bool spaceOverlap(Space space1, Space space2)
	{
		return max(space1.xStart, space2.xStart) < min(space1.xEnd, space2.xEnd)
			&& max(space1.yStart, space2.yStart) < min(space1.yEnd, space2.yEnd);
	}

	inline void setFullscreen(bool fullscreen)
	{
		_to_be_fullscreen = fullscreen;
		_needsResizeCorrection = true;
	}

	/*-------------------------------------------*\
	|		       Getting Functions	     	  |
	\*-------------------------------------------*/

	Color sysGetFrontColor(int x, int y, Area area)
	{
		return area.colFront[y * area.width + x];
	}
	Color sysGetBackColor(int x, int y, Area area)
	{
		return area.colBack[y * area.width + x];
	}
	char sysGetChar(int x, int y, Area area)
	{
		return area.characters[y * area.width + x];
	}

	Color getFrontColor(int x, int y)
	{
		return areaToDrawOn->colFront[y * areaToDrawOn->width + x];
	}
	Color getBackColor(int x, int y)
	{
		return areaToDrawOn->colBack[y * areaToDrawOn->width + x];
	}
	char getChar(int x, int y)
	{
		return areaToDrawOn->characters[y * areaToDrawOn->width + x];
	}

	/*-------------------------------------------*\
	|		   System Drawing Functions			  |
	\*-------------------------------------------*/

	Point sysDrawPixel(int x, int y, Area area, char character, short front_color, short back_color)
	{
		Point loc = { x, y };
		if (x < 0 || y < 0 || x >= area.width || y >= area.height) return loc;

		int slot = y * (area.width) + x;

		if (character != Default)
			if (character == '\n' || character > 256 || character <= 0) // or invalid color
				_Error("Tried to add newline (\'\\n\'), or invalid character, to the screen buffer!", __LINE__);
			else area.characters[slot] = character;

		if (front_color != Default)
			if (front_color < 0 || front_color > 255)
				_Error("Tried to add invalid foreground color, to the screen buffer!", __LINE__);
			else area.colFront[slot] = front_color;

		if (back_color != Default)
			if (back_color < 0 || back_color  > 255)
				_Error("Tried to add invalid background color, to the screen buffer!", __LINE__);
			else area.colBack[slot] = back_color;
		
		return loc;
	}
	
	void sysDrawRect(int xStart, int yStart, int xEnd, int yEnd, Area area, bool filled, char character, short front_color, short back_color)
	{
		for (int x = xStart; x < xEnd; x++)
			for (int y = yStart; y < yEnd; y++)
				if (filled || ((x == xStart || x == xEnd - 1) || (y == yStart || y == yEnd - 1)))
					sysDrawPixel(x, y, area, character, front_color, back_color);
	}

	void sysDrawCircle(int x, int y, Area area, int radius, bool filled, char character, short front_color, short back_color)
	{
		// this code was modified from the olcConsoleGameEngine on github
		int xa = 0, ya = radius;
		int pa = 3 - 2 * radius;

		while (ya >= xa) // only formulate 1/8 of circle
		{
			if (filled)
			{
				// Modified to draw scan-lines instead of edges
				for (int ia = x - xa; ia <= x + xa; ia++)
				{
					sysDrawPixel(ia, y - ya, area, character, front_color, back_color);
					sysDrawPixel(ia, y + ya, area, character, front_color, back_color);
				}
				for (int ia = x - ya; ia <= x + ya; ia++)
				{
					sysDrawPixel(ia, y - xa, area, character, front_color, back_color);
					sysDrawPixel(ia, y + xa, area, character, front_color, back_color);
				}
			}
			else
			{
				sysDrawPixel(x - xa, y - ya, area, character, front_color, back_color);//upper left left
				sysDrawPixel(x - ya, y - xa, area, character, front_color, back_color);//upper upper left
				sysDrawPixel(x + ya, y - xa, area, character, front_color, back_color);//upper upper right
				sysDrawPixel(x + xa, y - ya, area, character, front_color, back_color);//upper right right
				sysDrawPixel(x - xa, y + ya, area, character, front_color, back_color);//lower left left
				sysDrawPixel(x - ya, y + xa, area, character, front_color, back_color);//lower lower left
				sysDrawPixel(x + ya, y + xa, area, character, front_color, back_color);//lower lower right
				sysDrawPixel(x + xa, y + ya, area, character, front_color, back_color);//lower right right
			}
			if (pa < 0) pa += 4 * xa++ + 6;
			else pa += 4 * (xa++ - ya--) + 10;
		}
	}

	void sysDrawLine(int xStart, int yStart, int xEnd, int yEnd, Area area, char character, short front_color, short back_color)
	{
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

			sysDrawPixel(x, y, area, character, front_color, back_color);

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
				sysDrawPixel(x, y, area, character, front_color, back_color);
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
			sysDrawPixel(x, y, area, character, front_color, back_color);

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
				sysDrawPixel(x, y, area, character, front_color, back_color);
			}
		}
	}

	void sysDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Area area, bool filled, char character, short front_color, short back_color)
	{
		if (!filled)
		{
			sysDrawLine(x1, y1, x2, y2, area, character, front_color, back_color);
			sysDrawLine(x2, y2, x3, y3, area, character, front_color, back_color);
			sysDrawLine(x1, y1, x3, y3, area, character, front_color, back_color);
		}

		else //https://www.avrfreaks.net/sites/default/files/triangles.c
		{
			unsigned int t1x, t2x, y, minx, maxx, t1xp, t2xp;
			bool changed1 = false;
			bool changed2 = false;
			int signx1, signx2, dx1, dy1, dx2, dy2;
			unsigned int e1, e2;
			// Sort vertices
			if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
			if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
			if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }

			t1x = t2x = x1; y = y1;   // Starting points

			dx1 = (int)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y2 - y1);

			dx2 = (int)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
			else signx2 = 1;
			dy2 = (int)(y3 - y1);

			if (dy1 > dx1) {   // swap values
				SWAP(dx1, dy1);
				changed1 = true;
			}
			if (dy2 > dx2) {   // swap values
				SWAP(dy2, dx2);
				changed2 = true;
			}

			e2 = (unsigned int)(dx2 >> 1);
			// Flat top, just process the second half
			if (y1 == y2) goto next;
			e1 = (unsigned int)(dx1 >> 1);

			for (unsigned int i = 0; i < (unsigned int)dx1;) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < (unsigned int)dx1) {
					i++;
					e1 += dy1;
					while (e1 >= (unsigned int)dx1) {
						e1 -= dx1;
						if (changed1) t1xp = signx1;//t1x += signx1;
						else goto next1;
					}
					if (changed1) break;
					else t1x += signx1;
				}
				// Move line
			next1:
				// process second line until y value is about to change
				while (1) {
					e2 += dy2;
					while (e2 >= (unsigned int)dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;//t2x += signx2;
						else          goto next2;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next2:
				if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
				simple_draw_line(minx, maxx, y, area, character, front_color, back_color);    // Draw line from min to max points found on the y
				// Now increase y
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y == y2) break;

			}
		next:
			// Second half
			dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y3 - y2);
			t1x = x2;

			if (dy1 > dx1) {   // swap values
				SWAP(dy1, dx1);
				changed1 = true;
			}
			else changed1 = false;

			e1 = (unsigned int)(dx1 >> 1);

			for (unsigned int i = 0; i <= (unsigned)dx1; i++) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < (unsigned)dx1) {
					e1 += dy1;
					while (e1 >= (unsigned int)dx1) {
						e1 -= dx1;
						if (changed1) { t1xp = signx1; break; }//t1x += signx1;
						else          goto next3;
					}
					if (changed1) break;
					else   	   	  t1x += signx1;
					if (i < (unsigned)dx1) i++;
				}
			next3:
				// process second line until y value is about to change
				while (t2x != x3) {
					e2 += dy2;
					while (e2 >= (unsigned int)dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;
						else          goto next4;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next4:

				if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
				simple_draw_line(minx, maxx, y, area, character, front_color, back_color);    // Draw line from min to max points found on the y
				// Now increase y
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y > (unsigned int)y3) return;
			}
		}
	}

	void sysDrawText(int x, int y, Area area, const char* text, Font fontType, short front_color, short back_color)
	{
		int xPrev = x;
		for (size_t i = 0; text[i] != 0; i++)
		{
			if (text[i] == '\n')
			{
				x = xPrev, y += fontType.height + fontType.spacingY;
				continue;
			}

			if (fontType.data == NULL)
				sysDrawPixel(x, y, area, text[i], front_color, back_color);
			
			else
			{
				const unsigned char* letter = (fontType.data + (((char)text[i]) - ' ') * fontType._w);

				#define NUM_BITS 8
				int yOffset = NUM_BITS - fontType.height - 1;

				// loop through x and y of data
				for (int py = yOffset; py < NUM_BITS; py++)
					for (int px = 0; px < fontType._w; px++)
					{
						bool set = letter[px] & 1 << py;
						int addX = (fontType.data == (const unsigned char*)font8x8_basic) ? py - yOffset : px; // here yOffset is not needed, because its 8 bit
						int addY = (fontType.data == (const unsigned char*)font8x8_basic) ? px : py - yOffset; // over here it is, because there is more memory than actually used.

						if (set)
							sysDrawPixel(x + addX, y + addY, area, Default, front_color, back_color);
					}
			}
			x += fontType.width + fontType.spacingX;
		}
	}

	void sysDrawNumber(int x, int y, Area area, double number, int numDecimal, Font fontType, short front_color, short back_color)
	{
		if (numDecimal == Default)
		{
			if ((int)number == number) numDecimal = 0;
			else if (abs((long)((float)number - (int)number)) < 1.0f) numDecimal = 4;
			else numDecimal = 2;
		}
		char text[30] = { 0 };
		char formatText[10] = "%.";
		char numDecimalText[10] = { 0 };

		_itoa(numDecimal, numDecimalText, 10);
		strcat(formatText, numDecimalText);
		strcat(formatText, "f");

		snprintf(text, 30, formatText, number);
		return sysDrawText(x, y, area, text, fontType, front_color, back_color);
	}

	void sysDrawArea(int x, int y, Area area, Area areaToDraw)
	{
		if (!legalArea(areaToDraw)) _Error("Can't draw deleted Area!", __LINE__);

		for (int ys = 0; ys < areaToDraw.height; ys++)
			for (int xs = 0; xs < areaToDraw.width; xs++)
			{
				int loc = ys * (areaToDraw.width) + xs;
				sysDrawPixel(x + xs, y + ys, area, (areaToDraw.drawText) ? areaToDraw.characters[loc] : Default, (areaToDraw.drawFront) ? areaToDraw.colFront[loc] : Default, (areaToDraw.drawBack) ? areaToDraw.colBack[loc] : Default);
			}
	}

	void sysDrawPartialArea(int x, int y, Area area, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY)
	{
		int newX=0, newY=0;
		if (!legalArea(areaToDraw)) _Error("Can't draw deleted Area!", __LINE__);
		if (endAreaX > areaToDraw.width || endAreaY > areaToDraw.height || startAreaX < 0 || startAreaY < 0) _Error("Can't draw partial Area bigger than area itself.", __LINE__);

		for (int ys = startAreaY; ys < endAreaY; ys++)
		{
			for (int xs = startAreaX; xs < endAreaX; xs++)
			{
				int loc = ys * (areaToDraw.width) + xs;
				sysDrawPixel(x+newX, y+newY, area, areaToDraw.characters[loc], areaToDraw.colFront[loc], areaToDraw.colBack[loc]);
				newX++;
			}
			newX=0, newY++;
		}
	}

	/*-------------------------------------------*\
	|		   Space Drawing Functions			  |
	\*-------------------------------------------*/

	Space spDrawPixel(int x, int y, Space space, short color)
	{
		space = calcSpace(space, x, y, 1, 1);
		sysDrawPixel(space.xStart, space.yStart, *areaToDrawOn, Default, Default, color);
		return space;
	}
	Space spDrawChar(int x, int y, Space space, char character, short color)
	{
		space = calcSpace(space, x, y, 1, 1);
		sysDrawPixel(space.xStart, space.yStart, *areaToDrawOn, character, color, Default);
		return space;
	}

	Space spDrawRect(int x, int y, int width, int height, Space space, bool filled, short color)
	{	
		space = calcSpace(space, x, y, width, height);
		sysDrawRect(space.xStart, space.yStart, space.xEnd, space.yEnd, *areaToDrawOn, filled, Default, Default, color);
		return space;
	}

	Space spDrawCircle(int x, int y, Space space, int radius, bool filled, short color)
	{
		space = calcSpace(space, x, y, radius * 2, radius * 2);
		sysDrawCircle(space.xStart+radius, space.yStart+radius, *areaToDrawOn, radius, filled, Default, Default, color);
		return space;
	}
	
	Space spDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Space space, bool filled, short color)
	{
		int closestX = min(x1, min(x2, x3));
		int closestY = min(y1, min(y2, y3));
		int furthestX = max(x1, max(x2, x3));
		int furthestY = max(y1, max(y2, y3));

		space = calcSpace(space, closestX, closestY, furthestX - closestX, furthestY - closestY);
		sysDrawTriangle(space.xStart+x1,space.yStart+y1,space.xStart+x2,space.yStart+y2,space.xStart+x3,space.yStart+y3, *areaToDrawOn, filled, Default, Default, color);
		return space;
	}

	Space spDrawLine(int xStart, int yStart, int xEnd, int yEnd, Space space, short color)
	{
		space = calcSpace(space, xStart, yStart, xEnd-xStart, yEnd-xEnd);
		sysDrawLine(space.xStart, space.yStart, space.xEnd, space.yEnd, *areaToDrawOn, Default, Default, color);
		return space;
	}
	Space spDrawText(int x, int y, Space space, const char* text, Font fontType, short color)
	{
		space = calcSpace(space, x, y, txtWidth(text, fontType), txtHeight(text, fontType));
		sysDrawText(space.xStart, space.yStart, *areaToDrawOn, text, fontType, fontType.data == NULL ? color : Default, fontType.data == NULL ? Default : color);
		return space;
	}
	Space spDrawNumber(int x, int y, Space space, double number, int numDecimal, Font fontType, short color)
	{
		int count = number < 0 ? 1 : 0, n = (int)number;
		
		do {(n = n / (int)10), ++count;} 
		while (n != 0);

		int textWidth = (count + numDecimal) * (fontType.width + fontType.spacingX) - fontType.spacingX; // because last spacing is not existant.

		space = calcSpace(space, x, y, textWidth, fontType.height); // x is a placeholder, for any letter
		sysDrawNumber(space.xStart, space.yStart, *areaToDrawOn, number, numDecimal, fontType, Default, color);
		return space;
	}

	Space spDrawArea(int x, int y, Space space, Area areaToDraw)
	{
		space = calcSpace(space, x, y, areaToDraw.width, areaToDraw.height);
		sysDrawArea(space.xStart, space.yStart, *areaToDrawOn, areaToDraw);
		return space;
	}
	Space spDrawPartialArea(int x, int y, Space space, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY)
	{
		space = calcSpace(space, x, y, endAreaX - startAreaX, endAreaY - startAreaY);
		sysDrawPartialArea(space.xStart, space.yStart, *areaToDrawOn, areaToDraw, startAreaX, startAreaY, endAreaX, endAreaY);
		return space;
	}

	void clear(Area area)
	{
		for (int i = 0; i < (area.width * area.height); i++)
			area.colBack[i] = Default, area.colFront[i] = Default;

		memset(area.characters, Default, sizeof(char) * (area.width * area.height));
	}

	void reset(Area area)
	{
		for (int i = 0; i < (area.width * area.height); i++)
			area.colBack[i] = defaultBackColor, area.colFront[i] = defaultFrontColor;
		
		memset(area.characters, DEFAULT_CHARACTER, sizeof(char) * (area.width * area.height));
	}

	/*-------------------------------------------*\
	|		   User Drawing Functions			  |
	\*-------------------------------------------*/

	Space drawPixel(int x, int y, short color)									{ return spDrawPixel(x, y, ScreenSpace, color); }
	Space drawChar(int x, int y, char character, short color)						{ return spDrawChar(x, y, ScreenSpace, character, color); }

	Space drawRect(int x, int y, int width, int height, short color)				{ return spDrawRect(x, y, width, height, ScreenSpace, false, color); }
	Space drawRectFilled(int x, int y, int width, int height, short color)		{ return spDrawRect(x, y, width, height, ScreenSpace, true,  color); }
	  
	Space drawCircle(int x, int y, int radius, short color)                       { return spDrawCircle(x, y, ScreenSpace, radius, false, color); }
	Space drawCircleFilled(int x, int y, int radius, short color)                 { return spDrawCircle(x, y, ScreenSpace, radius, true,  color); }

	Space drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short color) { return spDrawTriangle(x1, y1, x2, y2, x3, y3, ScreenSpace, false, color); }
	Space drawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, short color) { return spDrawTriangle(x1, y1, x2, y2,x3,y3,ScreenSpace,true,color); }
	
	Space drawLine(int xStart, int yStart, int xEnd, int yEnd, short color)		{ return spDrawLine(xStart, yStart, xEnd, yEnd, ScreenSpace, color); }
	Space drawText(int x, int y, const char* text, Font fontType, short color)	{ return spDrawText(x, y, ScreenSpace, text, fontType, color); }

	Space drawNumber(int x, int y, double number, Font fontType, short color)		{ return spDrawNumber(x,y,ScreenSpace,number,Default,fontType,color);}
	Space drawArea(int x, int y, Area areaToDraw)								{ return spDrawArea(x, y, ScreenSpace, areaToDraw); }
	Space drawPartialArea(int x, int y, Area area, int sX,int sY,int eX,int eY) { return spDrawPartialArea(x, y, ScreenSpace, area, sX, sY, eX, eY); }
	
	/*-------------------------------------------*\
	|		       Input Functions			  	  |
	\*-------------------------------------------*/

	Key key(int whichKey)
	{
		if (whichKey < 0 || whichKey >= AMOUNT_KEYS)
			_Error("Tried to access key that doesn't exist!", __LINE__);

		return allKeys[whichKey];
	}

	void keyCalc(int code, char normal, char shift, char* output)
	{
		if (key(Shift).held && key(code).pressed)
			output[strlen(output)] = shift;
		else if (key(code).pressed)
			output[strlen(output)] = normal;
	}

	bool textBoxInput(char* outputString, size_t length)
	{
		if (!isWindowActive() || strlen(outputString) >= length - 1)
			return true;
		if (allKeys[Esc].pressed || allKeys[Enter].pressed)
			return false;

		keyCalc(Spacebar, ' ', ' ', outputString);
		keyCalc(Comma, ',', '<', outputString);
		keyCalc(Period, '.', '>', outputString);
		keyCalc(Colon, ';', ':', outputString);
		keyCalc(Slash, '/', '?', outputString);
		
		keyCalc(Num1, '1', '!', outputString);
		keyCalc(Num2, '2', '@', outputString);
		keyCalc(Num3, '3', '#', outputString);
		keyCalc(Num4, '4', '$', outputString);
		keyCalc(Num5, '5', '%', outputString);
		keyCalc(Num6, '6', '^', outputString);
		keyCalc(Num7, '7', '&', outputString);
		keyCalc(Num8, '8', '*', outputString);
		keyCalc(Num9, '9', '(', outputString);
		keyCalc(Num0, '0', ')', outputString);

		if (allKeys[Backspace].pressed)
			outputString[strlen(outputString)-1] = 0;

		for (int i = A; i <= Z; i++)
			keyCalc(i, tolower(allKeys[i].character), allKeys[i].character, outputString);
			
		return true;
	}

	/*-------------------------------------------*\
	|		 Creating And Destroying Areas        |
	\*-------------------------------------------*/

	Area createArea(int width, int height, short front_color, short back_color)
	{
		Area area;
		area.width = width;
		area.height = height;
		area.drawText = false;
		area.drawFront = false;
		area.drawBack = true;

		area.characters = (char*)malloc((sizeof(char) * width * height) + 1);
		area.colFront = (short*)malloc((sizeof(short) * width * height));
		area.colBack = (short*)malloc((sizeof(short) * width * height));

		for (int i = 0; i < (width * height); i++)
		{
			area.colFront[i] = front_color;
			area.colBack[i] = back_color;
			area.characters[i] = DEFAULT_CHARACTER;
		}
		return area;
	}

	void resizeArea(int width, int height, Area* area)
	{
		area->width = width;
		area->height = height;

		if (!legalArea(*area)) _Error("Can't resize area to be negative!", __LINE__);

		char* charData = (char*)realloc(area->characters, (sizeof(char) * width * height) + 1);
		short* colFrontData = (short*)realloc(area->colFront, (sizeof(short) * width * height));
		short* colBackData = (short*)realloc(area->colBack, (sizeof(short) * width * height));
		
		// this exists so we don't get warnings.
		if (colFrontData != NULL) area->colFront = colFrontData;
		if (colBackData != NULL) area->colBack = colBackData;
		if (charData != NULL) area->characters = charData;

		for (int i = 0; i < (width * height); i++)
		{
			area->colFront[i] = defaultFrontColor;
			area->colBack[i] = defaultBackColor;
			area->characters[i] = DEFAULT_CHARACTER;
		}
	}

	void deleteArea(Area* area)
	{
		if (area->width == -1 || area->height == -1)
			return;

		area->width = -1;
		area->height = -1;

		free(area->characters);
		free(area->colFront);
		free(area->colBack);
		area->characters = NULL;
		area->colFront = NULL;
		area->colBack = NULL;
	}

	/*-------------------------------------------*\
	|		    Windows Console Functions   	  |
	\*-------------------------------------------*/

	void SetFont(int fontSizeX, int fontSizeY, int fontWeight, UINT codePage)
	{
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.X = fontSizeX;
		info.dwFontSize.Y = fontSizeY; // leave X as zero
		info.FontWeight = FONT_WEIGHT;
		info.FontFamily = FF_DONTCARE;
		wcscpy(info.FaceName, L"Consolas");
		if (!SetConsoleOutputCP(codePage)) _Error("Setting consoles codepage failed.", __LINE__);

		if (!SetCurrentConsoleFontEx(hConsoleOutput, 0, &info)) _Error("Setting console font failed.", __LINE__);
	}

	void getConsoleWindowSize(int* w, int* h)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			_Error("Unable to get the current console window size", __LINE__);

		*w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
 		*h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}

	void dimensionTooBigError(char dimension, int currSize, int maxSize)
	{
		char errMsg[200] = { 0 };
		sprintf(errMsg, "%c dimension too big (%d > %d)", dimension, currSize, maxSize);
		_Error(errMsg, __LINE__);
	}

	void setModes()
	{
		#ifdef ACRE_ALLOW_RESIZE
			SetWindowLongA(ConsoleWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_VSCROLL); // makes the window normal again
		#else
			SetWindowLongA(ConsoleWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX & ~WS_VSCROLL); //makes window not resizbale
		#endif
		SendMessageA(ConsoleWindow, WM_SYSCOMMAND, SC_RESTORE, 0);
	}

	void _setConsoleFullscreen(bool fullscreen)
	{
		_hasBeenResized = true;
		COORD largestSize;
		if (fullscreen)
			getConsoleWindowSize(&_oldWidth, &_oldHeight);

		if (SetConsoleDisplayMode(hConsoleOutput, fullscreen ? CONSOLE_FULLSCREEN_MODE : CONSOLE_WINDOWED_MODE, 0))
		{
			if (fullscreen) // cant combine this with if statement above, because we dont want the else to trigger
			{
				largestSize = GetLargestConsoleWindowSize(hConsoleOutput);
				_newWidth = largestSize.X, _newHeight = largestSize.Y;
			}
			else
			{
				setModes();
				_newWidth = _oldWidth, _newHeight = _oldHeight;
			}
		}
		else // if it failed, then make the console fullscreen the x64 way.
		{
			largestSize = GetLargestConsoleWindowSize(hConsoleOutput);

			if (fullscreen)
			{
				getConsoleWindowSize(&_oldWidth, &_oldHeight);

				if (_consoleFontHeight != _consoleFontWidth)
					_Error("When using fullscreen in x64, font width and height must be equal!", __LINE__);

				SetWindowLongA(ConsoleWindow, GWL_STYLE, GetWindowLongA(ConsoleWindow, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
				SendMessageA(ConsoleWindow, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

				SetConsoleScreenBufferSize(hConsoleOutput, largestSize);
				DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN) / _consoleFontWidth;
				DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN) / _consoleFontHeight;

				double ratio = (double)dwWidth / (double)largestSize.X;
				largestSize.Y = (int)((double)dwHeight / ratio);

				// Super janky, but works??? it corrects the dimensions depending on the font size
				if (_consoleFontHeight == 5 || _consoleFontHeight == 7 || _consoleFontHeight == 10 || _consoleFontHeight == 11 ||
					_consoleFontHeight == 14 || _consoleFontHeight == 29 || _consoleFontHeight == 30 || _consoleFontHeight == 17 || _consoleFontHeight == 27)
					largestSize.Y += 1;

				if (_consoleFontHeight == 22 || _consoleFontHeight == 23 || _consoleFontHeight == 24 || _consoleFontHeight == 26 ||
					_consoleFontHeight == 27 || _consoleFontHeight == 29 || _consoleFontHeight == 30)
					largestSize.X -= 1;

				if (!SetConsoleScreenBufferSize(hConsoleOutput, largestSize))
					_Error("Unable to set screen buffer size in x64 mode!", __LINE__);

				_newWidth = largestSize.X, _newHeight = largestSize.Y;
			}
			else
			{
				setModes();
				_newWidth = _oldWidth, _newHeight = _oldHeight;
			}
		}
	
		_fullscreen = fullscreen;
	}

	void setConsoleToSize(int width, int height, bool errors)
	{
		COORD largestSize = GetLargestConsoleWindowSize(hConsoleOutput);
		if (width > largestSize.X && errors) dimensionTooBigError('X', width, largestSize.X);
		if (height > largestSize.Y && errors) dimensionTooBigError('Y', height, largestSize.Y);

		int currWidth, currHeight;
		getConsoleWindowSize(&currWidth, &currHeight);

		if (currWidth > width || currHeight > height)
		{
			// window size needs to be adjusted before the buffer size can be reduced.
			SMALL_RECT info = { 0,0, (short)(width < currWidth ? width - 1 : currWidth - 1), (short)(height < currHeight ? height - 1 : currHeight - 1) };
			if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info) && errors)
				_Error("Resizing window failed!", __LINE__);
		}

		COORD size = { (short)width, (short)height };
		if (!SetConsoleScreenBufferSize(hConsoleOutput, size) && errors)
			_Error("Unable to resize screen buffer!", __LINE__);

		SMALL_RECT info = { 0, 0, (short)(width - 1), (short)(height - 1) };
		if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info) && errors)
			_Error("Unable to resize window after resizing buffer!", __LINE__);
	}

	inline bool isWindowActive()
	{
		#ifdef ACRE_IGNORE_ACTIVE_WINDOW
			return true;
		#else
			if (ConsoleWindow == GetForegroundWindow()) return true;
			return false;
		#endif
	}

	/*-------------------------------------------*\
	|	 Functions For Starting And Stoping		  |
	\*-------------------------------------------*/

	WINDOW_BUFFER_SIZE_RECORD wbsr = { 0 };

	void resizeCalculations(bool showErrors, bool getSize)
	{
		if (_needsResizeCorrection)
		{
			if (_to_be_fullscreen && !_fullscreen)
				_setConsoleFullscreen(true);
			
			else if (!_to_be_fullscreen && _fullscreen)
				_setConsoleFullscreen(false);
			
			else if (getSize)
				getConsoleWindowSize(&_newWidth, &_newHeight);
			
			setConsoleToSize(_newWidth, _newHeight, showErrors);

			resizeArea(_newWidth, _newHeight, &Screen);
			screenBufferFull = (char*)realloc(screenBufferFull, sizeof(char) * ((Screen.width * Screen.height) * ANSI_STR_LEN + 1));
			memset(screenBufferFull, 0, sizeof(char) * (Screen.width * Screen.height * ANSI_STR_LEN + 1)); // after allocating the screenBufferFull, empty it out.

			ScreenSpace.xEnd = Screen.width, ScreenSpace.yEnd = Screen.height;
			_needsResizeCorrection = false;
		}

		int w, h;
		getConsoleWindowSize(&w, &h);

		if (w != Screen.width || h != Screen.height)
			setConsoleToSize(w, h, showErrors);
	}

	void consoleEvents()
	{
		//get mouse location
		INPUT_RECORD irInBuf[100];
		DWORD events = 0;

		// Wait for the events.
		GetNumberOfConsoleInputEvents(hConsoleInput, &events);
		if (events > 0)
			if (!ReadConsoleInputA(hConsoleInput, irInBuf, events, &events))
				_Error("failed reading console inputs\n", __LINE__);

		bool didResize = false, scrollWMOVED = false, scrollHMOVED = false;

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
					scrollWMOVED = true;
					break;

				case MOUSE_WHEELED:
					Mouse.scrollH = irInBuf[i].Event.MouseEvent.dwButtonState;
					scrollHMOVED = true;
					break;

				default: break;
				}
			}
			break;

			#ifdef ACRE_ALLOW_RESIZE
			case WINDOW_BUFFER_SIZE_EVENT:
			{
				bool didResize = true;
				wbsr = irInBuf[i].Event.WindowBufferSizeEvent;
				if (wbsr.dwSize.X == Screen.width && wbsr.dwSize.Y == Screen.height)
					break;

				_newWidth = wbsr.dwSize.X, _newHeight = wbsr.dwSize.Y;
				_needsResizeCorrection = true, _hasBeenResized = true, didResize = true;
			} break;
			
			#endif
			default: break;
			}	
		}

		if (!didResize)
		{
			resizeCalculations(false, true);
		}

		if (!scrollHMOVED) Mouse.scrollH = 0;
		if (!scrollWMOVED) Mouse.scrollW = 0;
	}

	void terminateACRE()
	{
		if (SetConsoleOutputCP(65001) == 0)
			_Error("Changing codepage back to default failed.", __LINE__);

		free(screenBufferFull);
		deleteArea(&Screen);
	}
	
	void initializeKeys()
	{
		for (int i = 0; i < AMOUNT_KEYS; i++)
		{
			allKeys[i].held = false;
			allKeys[i].pressed = false;
			allKeys[i].released = false;
			allKeys[i].character = -1;
		}
		
		for (char letter = 'A'; letter <= 'Z'; letter++)
			allKeys[letter - 'A'].code = letter, allKeys[letter - 'A'].character = letter;
		
		allKeys[Up].code = VK_UP, allKeys[Down].code = VK_DOWN, allKeys[Left].code = VK_LEFT, allKeys[Right].code = VK_RIGHT;
		allKeys[Enter].code = VK_RETURN, allKeys[Esc].code = VK_ESCAPE, allKeys[LMB].code = VK_LBUTTON, allKeys[RMB].code = VK_RBUTTON;
		allKeys[Spacebar].code = VK_SPACE, allKeys[Shift].code = VK_SHIFT, allKeys[Alt].code = VK_MENU, allKeys[Tab].code = VK_TAB, allKeys[Comma].code = VK_OEM_COMMA, allKeys[Period].code = VK_OEM_PERIOD;
		allKeys[Colon].code = VK_OEM_1, allKeys[Slash].code = VK_OEM_2, allKeys[QuestionMark].code = '?', allKeys[Backspace].code = VK_BACK;

		allKeys[Num0].code = '0', allKeys[Num1].code = '1', allKeys[Num2].code = '2', allKeys[Num3].code = '3', allKeys[Num4].code = '4';
		allKeys[Num5].code = '5', allKeys[Num6].code = '6', allKeys[Num7].code = '7', allKeys[Num8].code = '8', allKeys[Num9].code = '9';
	}

	void calculateAndSetWindowTitle(char* userTitleName)
	{
		char currentTitle[200] = { 0 };

		#if defined(ACRE_SHOW_FPS) && !defined(ACRE_REMOVE_WATERMARK)
			sprintf(currentTitle, "%s - AMZG Studio - ACREngine - %.2f fps", windowTitle, fps);

		#elif defined(ACRE_SHOW_FPS) && defined(ACRE_REMOVE_WATERMARK)
			sprintf(currentTitle, "%s - %.2f fps", windowTitle, fps);

		#elif !defined(ACRE_REMOVE_WATERMARK)
			sprintf(currentTitle, "%s - AMZG Studio - ACREngine", windowTitle);

		#else
			strcat(currentTitle, windowTitle);

		#endif
		SetConsoleTitleA(currentTitle);
	}

	void initialize(const char* title, int width, int height, int fontWidth, int fontHeight, short frontColor, short backColor)
	{
		//set default values
		if (width == Default) width = defaultScreenWidth;
		if (height == Default) height = defaultScreenHeight;

		if (frontColor != Default) defaultFrontColor = frontColor;
		if (backColor != Default) defaultBackColor = backColor;

		if (fontWidth != Default) _consoleFontWidth = fontWidth;
		if (fontHeight != Default) _consoleFontHeight = fontHeight;
		if ((int)title != Default) strcpy(windowTitle, title);

		if (_consoleFontWidth < 2)
			_Error("The minimum font height is 2!", __LINE__);

		if (_firstInitialize)
		{
			// initialize the fps stuff
			_countIndex = 0;
			for (size_t i = 0; i < FPS_COUNTS; i++) _pastPerformance[i] = 1;

			hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

			if (hConsoleOutput == INVALID_HANDLE_VALUE) _Error("Retreiving Console Output Handle Failed", __LINE__);
			if (hConsoleInput == INVALID_HANDLE_VALUE) _Error("Retreiving Console Input Handle Failed", __LINE__);

			ConsoleWindow = GetConsoleWindow();

			setModes();
			initializeKeys();

			// Set flags to allow mouse input, and disable selecting, and support for ANSI escape sequences.	
			if (!SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
				_Error("Setting The consoles Input modes did not work.", __LINE__);
			if (!SetConsoleMode(hConsoleOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN))
				_Error("Setting The consoles Output modes did not work.", __LINE__);

			QueryPerformanceCounter(&liStart);
			QueryPerformanceFrequency(&frequency);

			WriteConsoleA(hConsoleOutput, "\x1b[?25l", 7, NULL, NULL); // hide the console cursor

			areaToDrawOn = &Screen;
			_firstInitialize = false;
		}

		SetFont(_consoleFontWidth, _consoleFontHeight, FONT_WEIGHT, 65001);
		calculateAndSetWindowTitle(windowTitle);
		
		// since now the dimensions are different, we are going to need to resize the console and whatnot.
		_newWidth = width;
		_newHeight = height;
		_needsResizeCorrection = true;
		resizeCalculations(true, false);

		srand((unsigned int)liStart.QuadPart);
	}

	/*-------------------------------------------*\
	|		     Functions for Rendering	  	  |
	\*-------------------------------------------*/
	
	void calculateKeys()
	{
		for (size_t i = 0; i < AMOUNT_KEYS; i++)
		{
			bool down = (GetAsyncKeyState(allKeys[i].code) & 0x8000) && isWindowActive();

			allKeys[i].pressed = false;
			allKeys[i].released = false;

			if (down && !allKeys[i].held)
				allKeys[i].pressed = true;

			if (!down && allKeys[i].held)
				allKeys[i].released = true;

			allKeys[i].held = down;
		}
	}

	static inline void addString(const char* string, size_t size)
	{
		memcpy(&screenBufferFull[nextSlot], string, size);
		nextSlot += size;
	}

	static inline void _addSingleColor(const char* before, Color color)
	{
		char buffer[4] = {0};
		_itoa(color, buffer, 10);
		addString(before, 5);	
		addString(buffer, 3);
	}

	void render(bool clearScreen)
	{
		memcpy(screenBufferFull, "\033[0;0H", 6);
		nextSlot = 6;

		short currentForeground = Default, currentBackground = Default;
		for (size_t i = 0; i < Screen.width * Screen.height; i++)
		{
			bool drawForeground = Screen.colFront[i] != currentForeground;
			bool drawBackground = Screen.colBack[i] != currentBackground;
			
			if (drawForeground || drawBackground)
			{
				addString("\033[", 2);

				if (drawForeground)
					_addSingleColor("38;5;", Screen.colFront[i]);

				if (drawForeground && drawBackground)
					screenBufferFull[nextSlot] = ';', nextSlot++;

				if (drawBackground)
					_addSingleColor("48;5;", Screen.colBack[i]);

				screenBufferFull[nextSlot] = 'm'; nextSlot++; // m is needed for ansi stuff

				currentForeground = Screen.colFront[i];
				currentBackground = Screen.colBack[i];
			} 
			screenBufferFull[nextSlot] = Screen.characters[i]; nextSlot++;
		}

		// actual render
		if (!WriteConsoleA(hConsoleOutput, screenBufferFull, nextSlot, NULL, NULL))
			_Error("Rendering failed.", __LINE__);

		if (clearScreen) 
			reset(Screen);

		consoleEvents();
		calculateKeys();
		calculateAndSetWindowTitle(windowTitle);

		QueryPerformanceCounter(&liEnd);
		deltaTime = clampFloat((float)(liEnd.QuadPart - liStart.QuadPart) / (float)frequency.QuadPart, 0, 2);
		liStart = liEnd;
		
		if (_countIndex >= FPS_COUNTS) _countIndex = 0, _finishedFPSLoop = true;
		_pastPerformance[_countIndex++] = deltaTime;

		float totalTime = 0;
		for (size_t i = 0; i < (_finishedFPSLoop ? FPS_COUNTS : _countIndex); i++)
			totalTime += _pastPerformance[i];

		fps = 1.0f / (totalTime / (float)(_finishedFPSLoop ? FPS_COUNTS : _countIndex));
	}

	int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		// create a console. Note this project is a windowed application. The reason we do it this way, is so it will never use the windows terminal, and always the cmd.
		AllocConsole();
		start();
		terminateACRE();
		return 0;
	}

#endif