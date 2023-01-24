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

		To use gcc, simply use the command:
		gcc -o example.exe example.c

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

		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		/*
		Changelog:

		Fixed initalize to be called initialize
		MAJOR:
		space functions.
		Areas (and their functions).
		Image routines. (making, loading, etc).

		Fixed Bugs in triangle routines.
		Removed sysDrawColorBuffer.
		Removed sysDrawFontChar, now sysDrawText is used.
		drawPoint now called drawPixel.
		More functions work when using ACRE on mutliple files.
		Fixed user input, when window is not selected one. to allow that to happen define: NO_WINDOW_ACTIVE
		added makeImage()
		Renamed Screen to ScreenSpace.
		Screen is now an Area.
		added Areas.
		renamed clearScreen to clear() (now takes in an area).
		changed getting functions.

		No value needs to be assigned to FULLSCREEN. now just #define FULLSCREEN
		Clamp function works with floats now.

		added Areas.
		added Xterm(), which converts a xterm color to rgb.
		changed colors to look more consistent on different devices.
		changed color system, to now have more colors, and different colors.
		map function works with floats now.
		Error functions now show which line error was caused.
		resizing console window can now be activated with ALLOW_WINDOW_RESIZE
		use #define FPS_TICKS val to define how many ticks the fps will be averaged over.
		dont touch for default
		added sysDrawPartialArea() function.
		added max time step
		added center() function in the header mode of the file.
		added extern variables.

		removed Images, Areas are now used exclusivly.
			Image struct gone. Image functions, now use sprite name instead, and return Areas.
			Removed sysDrawImage()
			Removed drawImage()
			flipImage now called flipArea

		added spWidth, and spHeight.
		fixed bug in makeSprite()
		fixed bug in spDrawNumber()
		fixed bug in drawCircle() causing it too be create malformed circles.
		fixed bug in spDrawCircleFilled

		Changed ACRE_Window extension, now works like other extensions (#ifdef stuff)
		Changed terminate() function, to terminateACRE(). it caused issues with cpp
		renamed stringLength to stringWidth
		ACRE_Window extension, is now called ACRE_Gui.

		Default Area to draw on, is now configurable. call setDefaultDrawArea().
			- Note: only draws on area specified, assuming no other draw area is set.
			- Note: area rendered is still Screen, so you must draw to screen at the end, with sysDrawArea().

		added legalArea() function. (it checks if a area is able to be drawn properly.

		FINISHED: TODO: Add other drawPartialArea functions.
		ACRE_Fonts now work in OOP.
			- do be able to use all fonts define ALL_FONTS
			- to start the fonts, define ACRE_FONTS

		Changed FULLSCREEN to be ACRE_FULLSCREEN

		TODO: onResize() function.
		TODO: Change how fps works, instead of ticks, it goes by time.
		TODO: Finish textBoxInput()
		*/
		
#ifndef ACRE_INCLUDES
#define ACRE_INCLUDES
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		#define _CRT_SECURE_NO_WARNINGS 1
		#define _WIN32_WINNT 0x0500

		#include <stdio.h>
		#include <windows.h>
		#include <stdbool.h>
		#include <stdarg.h>
		#include <ctype.h>

		#ifdef __GNUC__
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
			BOOL WINAPI SetConsoleDisplayMode(HANDLE hConsoleOutput, DWORD  dwFlags,PCOORD lpNewScreenBufferDimensions);
			
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
	#define ACRE_3_COMPATIBLE // its in here, because we only want it to be defined once, regardless of if ACRE_START is defined.

	// used for triangle drawing
	#define SWAP(x,y) do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)

	// all structs used by ACRE
	typedef struct Point { int x, y; } Point;
	typedef struct Space { int startX, startY, endX, endY; } Space;
	typedef struct MOUSE { int x, y; int scrollH, scrollW; } MOUSE;
	typedef struct Font { int w, displayW; const unsigned char *dat; } Font;
	typedef struct Area { short* colFront, * colBack; char* characters; int width, height; bool drawFront, drawBack, drawText; } Area;
	typedef struct Key {bool pressed, held, released; int letter;} Key;
	typedef struct Timer { double elapsedTime; } Timer;

	extern Area Screen;
	extern Space ScreenSpace;
	// all enums
	enum KEYS {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Up, Down, Left, Right,
		Enter, Esc, LeftM, RightM, Spacebar, Shift, Alt, Tab, Comma, Period, Colon, Slash, QuestionMark, Backspace,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9
	};
	enum ACRE_TYPES {Thirds = -502, Centered = -501, Default = -1 };
	enum COLORS { 
		Black = 16, VeryDarkGrey = 234, DarkGrey = 237, Grey = 243, LightGrey = 247, White = 255,
		
		Red = 196, Maroon = 52,		   DarkRed = 124,  Pink = 218,
		Orange=202,Brown = 130,		   DarkOrange=166, Tan = 180,
		Yellow=226,Olive=100,		   DarkYellow=184, LightYellow=228,
		Green=40,  VeryDarkGreen=22,   DarkGreen=34,   LightGreen=83, 
		Cyan=37,   VeryDarkCyan=24,    DarkCyan=31,    LightCyan=44,
		Blue=33,   Navy=17,		       DarkBlue=20,    LightBlue=75,
		Purple=93, VeryDarkPurple=54,  DarkPurple=91,  LightPurple=129,
		
		Magenta=127
	};


	enum SPECIAL_CHARS {
		LightShade = 176, MediumShade = 177, DarkShade = 178, FullBlock = 219, LowerHalfBlock = 220,
		LeftHalfBlock = 221, RightHalfBlock = 222, UpperHalfBlock = 223
	};
	// variable declarations
	extern int defaultFrontColor, defaultBackColor;
	extern MOUSE Mouse;
	extern Font EightBit;

	// function declarations
	int center(int length, Space screenSpace, int mode);

	Area loadSprite(const char* spriteFilePath);
	void makeSprite(Area areaToMakeSprite, char* spriteFilePath);

	int Width(Area area);
	int Height(Area area);
	int spWidth(Space space);
	int spHeight(Space space);
	int Random(int rangeStart, int rangeEnd);
	float timePerSec(float amount);
	Space getSpace(Space prevSpace, int xStart, int yStart, int xEnd, int yEnd);
	void calculateTimer(Timer* timer);
	Timer createTimer();
	int strToInt(char* string);
	void intToStr(char* string, int num);
	float map(float numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd);
	float clamp(float numToClamp, float min, float max);
	void Xterm(short col, short* r, short* g, short* b);
	int Color(int r, int g, int b);
	int stringWidth(const char* string, Font fontType);
	void setDefaultDrawArea(Area* ar);
	bool legalArea(Area area);

	void onResize(int* newWidth, int* newHeight);
	bool pointSpaceCollide(int x, int y, Space screenSpace);
	bool rectangleCollide(int xStart1, int yStart1, int xEnd1, int yEnd1, int xStart2, int yStart2, int xEnd2, int yEnd2);
	bool spaceCollide(Space space1, Space space2);

	void sysGetPoint(int x, int y, Area area, int data[3]);
	char getChar(int x, int y);
	int getPointFront(int x, int y);
	int getPointBack(int x, int y);
	
	Point sysDrawPoint(int x, int y, Area area, char character, int colorFront, int colorBack);
	void sysDrawRect(int xStart, int yStart, int xEnd, int yEnd, Area area, char character, bool filled, int colorFront, int colorBack);
	void sysDrawCircle(int x, int y, Area area, int radius, char character, bool filled, int colorFront, int colorBack);
	void sysDrawLine(int xStart, int yStart, int xEnd, int yEnd, Area area, char character, int colorFront, int colorBack);
	void sysDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Area area, char character, bool filled, int colorFront, int colorBack);
	void sysDrawText(int x, int y, Area area, const char* text, Font fontType, int colorFront, int colorBack);
	void sysDrawNumber(int x, int y, Area area, double number, int numDecimal, Font fontType, int colorFront, int colorBack);
	void sysDrawArea(int x, int y, Area area, Area areaToDraw);
	void sysDrawPartialArea(int x, int y, Area area, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY);

	Space spDrawPixel(int x, int y, Space space, int color);
	Space spDrawChar(int x, int y, Space space, char character, int color);
	Space spDrawRect(int xStart, int yStart, int xEnd, int yEnd, Space space, int color);
	Space spDrawRectFilled(int xStart, int yStart, int xEnd, int yEnd, Space space, int color);
	Space spDrawCircle(int x, int y, Space space, int radius, short color);
	Space spDrawCircleFilled(int x, int y, Space space, int radius, short color);
	Space spDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Space space, int color);
	Space spDrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, Space space, int color);
	Space spDrawLine(int xStart, int yStart, int xEnd, int yEnd, Space space, int color);
	Space spDrawText(int x, int y, Space space, const char* text, Font fontType, int color);
	Space spDrawNumber(int x, int y, Space space, double number, int numDecimal, Font fontType, int color);
	Space spDrawArea(int x, int y, Space space, Area areaToDraw);
	Space spDrawPartialArea(int x, int y, Space space, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY);

	Space drawPixel(int x, int y, int color);
	Space drawChar(int x, int y, char character, int color);
	Space drawRect(int xStart, int yStart, int xEnd, int yEnd, int color);
	Space drawRectFilled(int xStart, int yStart, int xEnd, int yEnd, int color);
	Space drawCircle(int x, int y, int radius, int color);
	Space drawCircleFilled(int x, int y, int radius, int color);

	void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
	void drawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, int color);

	Space drawLine(int xStart, int yStart, int xEnd, int yEnd, int color);
	Space drawText(int x, int y, const char* text, Font fontType, int color);
	Space drawNumber(int x, int y, double number, Font fontType, int color);
	Space drawArea(int x, int y, Area areaToDraw);
	Space drawPartialArea(int x, int y, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY);

	void clear(Area area);
	Key key(int whichKey);
	bool textBoxInput(char* outputString, int outputStringLength);

	Area createArea(int width, int height, short colorFront, short colorBack);
	void deleteArea(Area area);
	void initialize(const char* title, int width, int height, int fontWidth, int fontHeight, int defaultFront, int defaultBack);
	void render(bool clearScreen);
	int terminateACRE(void);

#endif

#ifdef ACRE_START
	#undef ACRE_START
	#ifndef ACRE_SYS_DEFS
		#define ACRE_SYS_DEFS
		#define ANSI_STR_LEN 24
		#define AMOUNT_KEYS 54

		#ifndef FPS_TICKS
			#define FPS_TICKS 20
		#endif
		#ifndef FONT_WEIGHT
			#define FONT_WEIGHT 500
		#endif
	#ifndef DEFAULT_CHARACTER
		#define DEFAULT_CHARACTER ' '
	#endif
	#ifndef MOUSE_HWHEELED
		#define MOUSE_HWHEELED 0x0008
	#endif
#endif
	char* screenBufferFull = NULL, windowTitle[200] = { 0 };

	int nextOpenSlot = 0, buffW = 100, buffH = 50, globalFontWidth = 12, globalFontHeight = 12;
	int defaultFrontColor = White, defaultBackColor = Black;
	float fps = -1;
	float totalTimes = 0;
	int currFPSslot = 0;
	bool checkActiveWindow = false, terminated = true;
	bool roundOne = true;
	bool needsResizeCorrection = false;
	bool hasBeenResized = false;
	bool showDefaultFPS = true;
	//windows handles
	HANDLE hConsoleOutput, hConsoleInput;
	HWND ConsoleWindow;

	Area* areaToDrawOn;
	Area Screen;
	Space ScreenSpace;
	
	//others
	MOUSE Mouse = { 0, 0, 0, 0 };
	Key  allKeys[AMOUNT_KEYS] = { 0 };
	LARGE_INTEGER start = { 0 }, end = { 0 }, frequency = { 0 };
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
	Font EightBit = { 8, 8, (const unsigned char*)font8x8_basic }; //sysDrawFontChar(x, y, Screen, EIGHT_BIT, text[slot], colorFront, colorBack);
	Font DefaultFont = { 1, 1, NULL };
	Timer timer = { 0 };
	/*-------------------------------------------*\
	|			 System Only Functions   		  |
	\*-------------------------------------------*/

	// used for sysDrawTri-angle
	void simple_draw_line(int x1, int x2, unsigned int y, Area area, char charater, int colorFront, int colorBack)
	{
		if (x1 >= x2) SWAP(x1, x2);
		for (; x1 <= x2; x1++) sysDrawPoint(x1, y, area, charater, colorFront, colorBack);
	}
	
	void Error(const wchar_t* errorMsg, int line)
	{

		wchar_t thing[200] = { 0 };
		#ifdef __GNUC__
			swprintf(thing, L"ACRError: (LINE:%d): %s", line, errorMsg);
		#else 
			swprintf(thing, 200, L"ACRError: (LINE:%d): %s", line, errorMsg);
		#endif
		MessageBoxW(NULL, (LPCWSTR)thing, NULL, MB_OK);
		exit(EXIT_FAILURE);
	}

	int center(int length, Space screenSpace, int mode)
	{
		if (mode == X)
		{
			int screenSpaceWidth = screenSpace.endX - screenSpace.startX;
			float halfWayThrough = (float)screenSpaceWidth / 2.0f;
			float halfText = (float)length / 2.0f;

			return (int)(halfWayThrough - halfText);
		}
		else if (mode == Y)
		{
			int screenSpaceWidth = screenSpace.endY - screenSpace.startY; // include the other end.
			float halfWayThrough = (float)screenSpaceWidth / 2.0f;
			float halfText = (float)length / 2.0f;

			return (int)(halfWayThrough - halfText);
		}
		return -1;
	}

	Space getSpace(Space prevSpace, int xStart, int yStart, int xEnd, int yEnd)
	{
		Space currSpace = { 0,0,0,0 };

		if (xStart == Centered)
		{
			currSpace.startX = prevSpace.startX + center(xEnd, prevSpace, X);
			currSpace.endX = currSpace.startX + xEnd;
		}
		else
		{
			currSpace.startX = prevSpace.startX + xStart;
			currSpace.endX = prevSpace.startX + xEnd;
		}
		if (yStart == Centered)
		{
			currSpace.startY = prevSpace.startY + center(yEnd, prevSpace, Y);
			currSpace.endY = currSpace.startY + yEnd;
		}
		else
		{
			currSpace.startY = prevSpace.startY + yStart;
			currSpace.endY = prevSpace.startY + yEnd;
		}
		return currSpace;
	}
	
	/*-------------------------------------------*\
	|		 General Functions / Miscelanous   	  |
	\*-------------------------------------------*/

	int Width(Area area)
	{
		return area.width;
	}
	int Height(Area area)
	{
		return area.height;
	}
	int spWidth(Space space)
	{
		return abs(space.endX - space.startX);
	}
	int spHeight(Space space)
	{
		return abs(space.endY - space.startY);
	}
	int Random(int rangeStart, int rangeEnd)
	{
		return (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;
	}

	int stringWidth(const char* string, Font fontType)
	{
		return (int)strlen(string) * fontType.displayW;
	}

	void onResize(int* newWidth, int* newHeight)
	{
		
	}

	float timePerSec(float amount)
	{
		return amount * deltaTime;
	}

	Timer createTimer()
	{
		Timer timer;
		timer.elapsedTime = 0.0f;
		return timer;
	}
	void calculateTimer(Timer* timer)
	{
		timer->elapsedTime += deltaTime;
	}

	float map(float numberToMap, int numberBegin, int numberEnd, int numberMapStart, int numberMapEnd)
	{
		float output = (float)numberMapStart + (((float)numberMapEnd - (float)numberMapStart) / ((float)numberEnd - (float)numberBegin)) * ((float)numberToMap - (float)numberBegin);
		return output;
	}
	float clamp(float numToClamp, float min, float max)
	{
		if (numToClamp < (float)min)
			numToClamp = (float)min;
		if (numToClamp > (float)max)
			numToClamp = (float)max;
		return numToClamp;
	}

	int strToInt(char* string)
	{
		return atoi(string);
	}
	void intToStr(char* string, int num)
	{
		_itoa(num, string, 10);
	}
	
	void Xterm(short col, short* r, short* g, short* b)
	{
		col = (short)clamp(col, 0, 255);
		int vals[6] = { 0,95,135,175,215,255 };

		if (col < 16)
			switch(col)
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
		else if (col >= 16 && col <= 231)
		{
			col -= 16;
			int num6s = (int)(col / 6.0f);
			*b = vals[col % 6];
			*r = (int)(num6s / 6.0f); // keep as a 0...5 number, to be used for green.
			*g = vals[num6s - ((*r) * 6)];
			*r = vals[*r]; // then convert it to 0...255;
		}
		else if (col > 231)
		{
			col -= 232;
			*r = 8, * g = 8, * b = 8;
			*r += col * 10;
			*g += col * 10;
			*b += col * 10;
		}
	}

	int Color(int r, int g, int b) // this code is not mine
	{
		clamp(r, 0, 255);
		clamp(g, 0, 255);
		clamp(b, 0, 255);

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
		return color_err <= gray_err ? 16 + color_index() : 232 + gray_index;
	} // removed static int, and replaced with int

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
			wchar_t msg[100] = { L"Opening ACRE file: "};
			wchar_t wszDest[100];
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, spriteFilePath, -1, wszDest, 100);
			wcscat(msg, wszDest);
			Error(msg, __LINE__);
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

		bool foundDot = false;
		for (int i = 0; i < 200; i++)
		{
			if (newPath[i] == '.' && i < 199 && i>0)
				if(newPath[i+1] != '.' && newPath[i-1] != '.')
					foundDot = true;

			if (foundDot) newPath[i] = 0;
		}
		strcat(newPath, ".acre");
		char extraModes[5] = { 0 };

		if (areaToMakeSprite.drawText)
			strcat(extraModes, ":T");

		FILE* file = fopen(newPath, "w");
		fprintf(file, "acrev3.0%s;%d;%d\n", extraModes, areaToMakeSprite.width, areaToMakeSprite.height);
		
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
		if (area.width == -1 && area.height == -1)
			return false;
		return true;
	}

	/*-------------------------------------------*\
	|		       Collision Functions	     	  |
	\*-------------------------------------------*/

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
		if (!SetConsoleOutputCP(codePage)) Error(L"Setting consoles codepage failed.", __LINE__);

		if (!SetCurrentConsoleFontEx(hConsoleOutput, 0, &info)) Error(L"Setting console font failed.", __LINE__);

	}

	void getConsoleWindowSize(int* w, int* h)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			Error(L"Unable to get the current console window size", __LINE__);
		
		*w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		*h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}

	void SetConsoleWindowSize(int* x, int* y, bool Errors)
	{
		bool fullscreenFailed = false;
		#ifdef ACRE_FULLSCREEN
		if (!SetConsoleDisplayMode(hConsoleOutput, CONSOLE_FULLSCREEN_MODE, 0))
		{
			DWORD dwStyle = GetWindowLong(ConsoleWindow, GWL_STYLE);
			SetWindowLong(ConsoleWindow, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
			SendMessage(ConsoleWindow, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			fullscreenFailed = true;
		}		
		#endif

		{
			COORD largestSize = GetLargestConsoleWindowSize(hConsoleOutput);
			if (fullscreenFailed)
			{
				DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN) / globalFontWidth;
				DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN) / globalFontHeight;
				
				float ratio = (float)dwWidth / (float)largestSize.X;
				int yNew = dwHeight / ratio;
				largestSize.X -= 1;
				//largestSize.Y += 1;
			}
#ifdef ACRE_FULLSCREEN
			(*x) = largestSize.X;
			(*y) = largestSize.Y;
#endif

			if ((*x) > largestSize.X)
			{
				if (!Errors) return;
				wchar_t errMsg[200] = { 0 };
#ifdef __GNUC__ // gcc uses different swprintf declaration.
				swprintf(errMsg, L"X dimension too big (%d > %d)", (*x), largestSize.X);
#else
				swprintf(errMsg, 200, L"X dimension too big (%d > %d)", (*x), largestSize.X);
#endif

				Error(errMsg, __LINE__);
			}
			if ((*y) > largestSize.Y)
			{
				if (!Errors) return;
				wchar_t errMsg[200] = { 0 };
#ifdef __GNUC__ // gcc uses different swprintf declaration.
				swprintf(errMsg, L"Y dimension too big (%d > %d)", (*y), largestSize.Y);
#else
				swprintf(errMsg, 200, L"Y dimension too big (%d > %d)", (*y), largestSize.Y);
#endif
				Error(errMsg, __LINE__);
			}
		}

		int width, height;
		getConsoleWindowSize(&width, &height);

		if (width > (*x) || height > (*y))
		{
			// window size needs to be adjusted before the buffer size can be reduced.
			SMALL_RECT info = { 0,0,(short)(*x) < width ? (short)(*x) - 1 : width - 1,(short)(*y) < height ? (short)(*y) - 1 : height - 1 };
			if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info))
				if (!Errors) return; else Error(L"Resizing window failed!", __LINE__);
		}

		COORD size = { (short)(*x), (short)(*y) };
		if (!SetConsoleScreenBufferSize(hConsoleOutput, size))
			if (!Errors) return; else Error(L"Unable to resize screen buffer!", __LINE__);

		SMALL_RECT info = { 0, 0, (short)(*x) - (short)1, (short)(*y) - (short)1 };
		if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info))
			if (!Errors) return; else Error(L"Unable to resize window after resizing buffer!", __LINE__);
	}

	bool windowActive()
	{
		#ifdef NO_WINDOW_ACTIVE
			return true;
		#endif
			if (ConsoleWindow == GetForegroundWindow()) return true;
			return false;
	}

	void setRequiredModes()
	{
		#ifndef ALLOW_WINDOW_RESIZE
				SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //makes window not resizbale
		#endif
		// Set flags to allow mouse input, and disable selecting, and support for ANSI escape sequences.	
		if (!SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
			Error(L"Setting The consoles Input modes did not work.", __LINE__);
		if (!SetConsoleMode(hConsoleOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN))
			Error(L"Setting The consoles Output modes did not work.", __LINE__);
	}

	/*-------------------------------------------*\
	|		       Getting Functions	     	  |
	\*-------------------------------------------*/

	void sysGetPoint(int x, int y, Area area, int data[3])
	{
		int slot = y * (buffW) + x;
		data[0] = area.characters[slot];
		data[1] = area.colFront[slot];
		data[2] = area.colBack[slot];
	}
	
	char getChar(int x, int y)
	{
		int data[3] = { 0 };
		sysGetPoint(x, y, Screen, data);
		return data[0];
	}
	
	int getPointFront(int x, int y)
	{
		int data[3] = { 0 };
		sysGetPoint(x, y, Screen, data);
		return data[1];
	}
	
	int getPointBack(int x, int y)
	{
		int data[3] = { 0 };
		sysGetPoint(x, y, Screen, data);
		return data[2];
	}

	/*-------------------------------------------*\
	|		   System Drawing Functions			  |
	\*-------------------------------------------*/

	Point sysDrawPoint(int x, int y, Area area, char character, int colorFront, int colorBack)
	{
		Point loc = { x, y };
		if (x < 0 || y < 0 || x >= area.width || y >= area.height) return loc;

		int slot = y * (area.width) + x;

		if (character != Default)// or invalid color
			if ((character == '\n' || character > 256 || character <= 0) && character != -1)
				Error(L"Tried to add newline (\'\\n\'), or invalid character, to the screen buffer!", __LINE__);
		else area.characters[slot] = character;

		if (colorFront != Default)
			if ((colorFront < 0 || colorFront > 255) && colorFront != -1)
				Error(L"Tried to add invalid foreground color, to the screen buffer!", __LINE__);
		else area.colFront[slot] = colorFront;

		if (colorBack != Default)
			if ((colorBack < 0 || colorBack  > 255) && colorBack != -1)
				Error(L"Tried to add invalid background color, to the screen buffer!", __LINE__);
		else area.colBack[slot] = colorBack;
			
		return loc;
	}
	
	void sysDrawRect(int xStart, int yStart, int xEnd, int yEnd, Area area, char character, bool filled, int colorFront, int colorBack)
	{
		for (int x = xStart; x < xEnd; x++)
			for (int y = yStart; y < yEnd; y++)
				if (filled || ((x == xStart || x == xEnd-1) || (y == yStart || y == yEnd-1)))
					sysDrawPoint(x, y, area, character, colorFront, colorBack);
	}

	void sysDrawCircle(int x, int y, Area area, int radius, char character, bool filled, int colorFront, int colorBack)
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
					sysDrawPoint(ia, y - ya, area, character, colorFront, colorBack);
					sysDrawPoint(ia, y + ya, area, character, colorFront, colorBack);
				}
				for (int ia = x - ya; ia <= x + ya; ia++)
				{
					sysDrawPoint(ia, y - xa, area, character, colorFront, colorBack);
					sysDrawPoint(ia, y + xa, area, character, colorFront, colorBack);
				}
			}
			else
			{
				sysDrawPoint(x - xa, y - ya, area, character, colorFront, colorBack);//upper left left
				sysDrawPoint(x - ya, y - xa, area, character, colorFront, colorBack);//upper upper left
				sysDrawPoint(x + ya, y - xa, area, character, colorFront, colorBack);//upper upper right
				sysDrawPoint(x + xa, y - ya, area, character, colorFront, colorBack);//upper right right
				sysDrawPoint(x - xa, y + ya, area, character, colorFront, colorBack);//lower left left
				sysDrawPoint(x - ya, y + xa, area, character, colorFront, colorBack);//lower lower left
				sysDrawPoint(x + ya, y + xa, area, character, colorFront, colorBack);//lower lower right
				sysDrawPoint(x + xa, y + ya, area, character, colorFront, colorBack);//lower right right
			}
			if (pa < 0) pa += 4 * xa++ + 6;
			else pa += 4 * (xa++ - ya--) + 10;
		}
	}

	void sysDrawLine(int xStart, int yStart, int xEnd, int yEnd, Area area, char character, int colorFront, int colorBack)
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

			sysDrawPoint(x, y, area, character, colorFront, colorBack);

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
				sysDrawPoint(x, y, area, character, colorFront, colorBack);
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
			sysDrawPoint(x, y, area, character, colorFront, colorBack);

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
				sysDrawPoint(x, y, area, character, colorFront, colorBack);
			}
		}
	}

	void sysDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Area area, char character, bool filled, int colorFront, int colorBack)
	{
		if (!filled)
		{
			sysDrawLine(x1, y1, x2, y2, area, character, colorFront, colorBack);
			sysDrawLine(x2, y2, x3, y3, area, character, colorFront, colorBack);
			sysDrawLine(x1, y1, x3, y3, area, character, colorFront, colorBack);

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
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) t1xp = signx1;//t1x += signx1;
						else          goto next1;
					}
					if (changed1) break;
					else t1x += signx1;
				}
				// Move line
			next1:
				// process second line until y value is about to change
				while (1) {
					e2 += dy2;
					while (e2 >= dx2) {
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
				simple_draw_line(minx, maxx, y, area, character, colorFront, colorBack);    // Draw line from min to max points found on the y
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
					while (e1 >= dx1) {
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
					while (e2 >= dx2) {
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
				simple_draw_line(minx, maxx, y, area, character, colorFront, colorBack);    // Draw line from min to max points found on the y
				// Now increase y
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y > y3) return;
			}
		}
	}

	void sysDrawText(int x, int y, Area area, const char* text, Font fontType, int colorFront, int colorBack)
	{
		int slot = 0, xPrev = x;
		while (text[slot] != 0)
		{
			if (text[slot] == '\n')
				x = xPrev, y += fontType.displayW;

			else
			{
				if (fontType.dat == NULL) sysDrawPoint(x, y, area, text[slot], colorFront, colorBack);
				else
				{
					const unsigned char* letter = (fontType.dat + (((char)text[slot]) - ' ') * fontType.w);

					for (int i = 0; i < fontType.w; i++)
						for (int j = 0; j < 8; j++)
						{
							int set = letter[i] & 1 << j;
							int addX = (fontType.dat == (const unsigned char*)font8x8_basic) ? j : i;
							int addY = (fontType.dat == (const unsigned char*)font8x8_basic) ? i : j;
							sysDrawPoint(x + addX, y + addY, area, Default, colorFront, set ? colorBack : Default);
						}
				}
				x += fontType.displayW;
			}
			slot++;
		}
	}

	void sysDrawNumber(int x, int y, Area area, double number, int numDecimal, Font fontType, int colorFront, int colorBack)
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
		return sysDrawText(x, y, area, text, fontType, colorFront, colorBack);
	}

	void sysDrawArea(int x, int y, Area area, Area areaToDraw)
	{
		if (!legalArea(areaToDraw)) Error(L"Can't draw deleted Area!", __LINE__);

		for (int ys = 0; ys < areaToDraw.height; ys++)
			for (int xs = 0; xs < areaToDraw.width; xs++)
			{
				int loc = ys * (areaToDraw.width) + xs;
				sysDrawPoint(x + xs, y + ys, area, (area.drawText) ? areaToDraw.characters[loc] : Default, (area.drawFront) ? areaToDraw.colFront[loc] : Default, (area.drawBack) ? areaToDraw.colBack[loc] : Default);
			}
	}

	void sysDrawPartialArea(int x, int y, Area area, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY)
	{
		int newX=0, newY=0;
		if (!legalArea(areaToDraw)) Error(L"Can't draw deleted Area!", __LINE__);
		if (endAreaX > areaToDraw.width || endAreaY > areaToDraw.height || startAreaX < 0 || startAreaY < 0) Error(L"Can't draw partial Area bigger than area itself.", __LINE__);

		for (int ys = startAreaY; ys < endAreaY; ys++)
		{

			for (int xs = startAreaX; xs < endAreaX; xs++)
			{
				int loc = ys * (areaToDraw.width) + xs;
				sysDrawPoint(x+newX, y+newY, area, areaToDraw.characters[loc], areaToDraw.colFront[loc], areaToDraw.colBack[loc]);
				newX++;
			}
			newX=0, newY++;
		}
	}

	/*-------------------------------------------*\
	|		   Space Drawing Functions			  |
	\*-------------------------------------------*/

	Space spDrawPixel(int x, int y, Space space, int color)
	{
		Space pix = getSpace(space, x, y, x, y);
		sysDrawPoint(pix.startX, pix.startY, *areaToDrawOn, Default, Default, color);
		return pix;
	}
	Space spDrawChar(int x, int y, Space space, char character, int color)
	{
		Space chr = getSpace(space, x, y, x, y);
		sysDrawPoint(chr.startX, chr.startY, *areaToDrawOn, character, color, Default);
		return chr;
	}

	Space spDrawRect(int xStart, int yStart, int xEnd, int yEnd, Space space, int color)
	{	
		Space rectLocation = getSpace(space, xStart, yStart, xEnd, yEnd);
		sysDrawRect(rectLocation.startX, rectLocation.startY, rectLocation.endX, rectLocation.endY, *areaToDrawOn, Default, false, Default, color);
		return rectLocation;
	}
	Space spDrawRectFilled(int xStart, int yStart, int xEnd, int yEnd, Space space, int color)
	{
		Space rectLocation = getSpace(space, xStart, yStart, xEnd, yEnd);
		sysDrawRect(rectLocation.startX, rectLocation.startY, rectLocation.endX, rectLocation.endY, *areaToDrawOn, Default, true, Default, color);
		return rectLocation;
	}

	Space spDrawCircle(int x, int y, Space space, int radius, short color)
	{
		Space circleSpace = getSpace(space, x == Centered ? x : x - radius, y == Centered ? y : y - radius, x == Centered ? radius : x + radius, y == Centered ? radius : y + radius);
		sysDrawCircle(x, y, *areaToDrawOn, radius, Default, false, Default, color);
		return circleSpace;
	}
	Space spDrawCircleFilled(int x, int y, Space space, int radius, short color)
	{
		Space circleSpace = getSpace(space, x == Centered ? x : x - radius, y == Centered ? y : y - radius, x == Centered ? radius : x + radius, y == Centered ? radius : y + radius);
		sysDrawCircle(x, y, *areaToDrawOn, radius, Default, true, Default, color);
		return circleSpace;
	}
	
	Space spDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Space space, int color)
	{
		int closestX = x1, closestY = y1;
		int furthestX = x1, furthestY = y1;

		if (x2 < closestX) closestX = x2;
		if (x3 < closestX) closestX = x3;
		if (y2 < closestY) closestY = y2;
		if (y3 < closestY) closestY = y3;

		if (x2 > furthestX) furthestX = x2;
		if (x3 > furthestX) furthestX = x3;
		if (y2 > furthestY) furthestY = y2;
		if (y3 > furthestY) furthestY = y3;

		Space triLocation = getSpace(space, closestX, closestY, furthestX, furthestY);
		sysDrawTriangle(triLocation.startX + x1, triLocation.startY + y1, triLocation.startX + x2, triLocation.startY + y2,
			triLocation.startX + x3, triLocation.startY + y3, *areaToDrawOn, Default, false, Default, color);
		return triLocation;
	}
	Space spDrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, Space space, int color)
	{
		int closestX = x1, closestY = y1;
		int furthestX = x1, furthestY = y1;

		if (x2 < closestX) closestX = x2;
		if (x3 < closestX) closestX = x3;
		if (y2 < closestY) closestY = y2;
		if (y3 < closestY) closestY = y3;

		if (x2 > furthestX) furthestX = x2;
		if (x3 > furthestX) furthestX = x3;
		if (y2 > furthestY) furthestY = y2;
		if (y3 > furthestY) furthestY = y3;

		Space triLocation = getSpace(space, closestX, closestY, furthestX, furthestY);
		sysDrawTriangle(triLocation.startX + x1, triLocation.startY + y1, triLocation.startX + x2, triLocation.startY + y2,
			triLocation.startX + x3, triLocation.startY + y3, *areaToDrawOn, Default, false, Default, color);
		return triLocation;
	}

	Space spDrawLine(int xStart, int yStart, int xEnd, int yEnd, Space space, int color)
	{
		Space line = getSpace(space, xStart, yStart, xEnd, yEnd);
		sysDrawLine(line.startX, line.startY, line.endX, line.endY, *areaToDrawOn, Default, Default, color);
		return line;
	}
	Space spDrawText(int x, int y, Space space, const char* text, Font fontType, int color)
	{
		int i = 0;
		while (text[i] != '\n' && text[i] != 0) i++;
		int textWidth = i * (fontType.displayW);

		Space textSpace = getSpace(space, x, y, (x == Centered) ? textWidth : x + textWidth, (y == Centered) ? fontType.displayW : y + fontType.displayW);
		
		sysDrawText(textSpace.startX, textSpace.startY, *areaToDrawOn, text, fontType, fontType.dat == NULL ? color : Default, fontType.dat == NULL ? Default : color);
		return textSpace;
	}
	Space spDrawNumber(int x, int y, Space space, double number, int numDecimal, Font fontType, int color)
	{
		int count = number < 0 ? 1 : 0;
		int n = (int)number;
		do {(int)(n = n/10), ++count;} 
		while (n != 0);
		int textWidth = (count + numDecimal) * fontType.displayW;

		Space numSpace = getSpace(space, x, y, (x == Centered) ? textWidth : x + textWidth, (y == Centered) ? fontType.displayW : y + fontType.displayW);
		sysDrawNumber(numSpace.startX, numSpace.startY, *areaToDrawOn, number, numDecimal, fontType, Default, color);
		return numSpace;
	}

	Space spDrawArea(int x, int y, Space space, Area areaToDraw)
	{
		Space areaSpace = getSpace(space, x, y, x == Centered ? areaToDraw.width : x + areaToDraw.width, y == Centered ? areaToDraw.height : y + areaToDraw.height);
		sysDrawArea(areaSpace.startX, areaSpace.startY, *areaToDrawOn, areaToDraw);
		return areaSpace;
	}
	Space spDrawPartialArea(int x, int y, Space space, Area areaToDraw, int startAreaX, int startAreaY, int endAreaX, int endAreaY)
	{
		Space areaSpace = getSpace(space, x, y, x == Centered ? endAreaX - startAreaX : x + endAreaX - startAreaX, y == Centered ? endAreaY - startAreaY : x + endAreaY - startAreaY);
		sysDrawPartialArea(areaSpace.startX, areaSpace.startY, *areaToDrawOn, areaToDraw, startAreaX, startAreaY, endAreaX, endAreaY);
		return areaSpace;
	}

	void clear(Area area)
	{
		for (int i = 0; i < (buffW * buffH); i++)
			area.colBack[i] = defaultBackColor, area.colFront[i] = defaultFrontColor;
		
		memset(area.characters, DEFAULT_CHARACTER, sizeof(char) * (buffW * buffH));
	}

	/*-------------------------------------------*\
	|		   User Drawing Functions			  |
	\*-------------------------------------------*/

	Space drawPixel(int x, int y, int color)									{ return spDrawPixel(x, y, ScreenSpace, color); }
	Space drawChar(int x, int y, char character, int color)						{ return spDrawChar(x, y, ScreenSpace, character, color); }

	Space drawRect(int xStart, int yStart, int xEnd, int yEnd, int color)       { return spDrawRect(xStart, yStart, xEnd, yEnd, ScreenSpace, color); }
	Space drawRectFilled(int xStart, int yStart, int xEnd, int yEnd, int color) { return spDrawRectFilled(xStart, yStart, xEnd, yEnd, ScreenSpace, color); }
	  
	Space drawCircle(int x, int y, int radius, int color)                       { return spDrawCircle(x, y, ScreenSpace, radius, color);       }
	Space drawCircleFilled(int x, int y, int radius, int color)                 { return spDrawCircleFilled(x, y, ScreenSpace, radius, color); }

	void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) { spDrawTriangle(x1, y1, x2, y2, x3, y3, ScreenSpace, color); }
	void drawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, int color) { spDrawTriangleFilled(x1, y1, x2, y2, x3, y3, ScreenSpace, color); }
	
	Space drawLine(int xStart, int yStart, int xEnd, int yEnd, int color)		{ return spDrawLine(xStart, yStart, xEnd, yEnd, ScreenSpace, color); }
	Space drawText(int x, int y, const char* text, Font fontType, int color)	{ return spDrawText(x, y, ScreenSpace, text, fontType, color); }

	Space drawNumber(int x, int y, double number, Font fontType, int color)		{ return spDrawNumber(x,y,ScreenSpace,number,Default,fontType,color);}
	Space drawArea(int x, int y, Area areaToDraw)								{ return spDrawArea(x, y, ScreenSpace, areaToDraw); }
	Space drawPartialArea(int x, int y, Area area, int sX,int sY,int eX,int eY) { return spDrawPartialArea(x, y, ScreenSpace, area, sX, sY, eX, eY); }
	
	/*-------------------------------------------*\
	|		       Input Functions			  	  |
	\*-------------------------------------------*/

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

				else if ((signed)strlen(outputString) < outputStringLength - 1 && (allKeys[i].letter != allKeys[Shift].letter) && (allKeys[i].letter != allKeys[LeftM].letter) && (allKeys[i].letter != allKeys[RightM].letter) && (allKeys[i].letter != allKeys[Alt].letter))
				{
					if (!key(Shift).held)
						outputString[nextSlot] = tolower(key(i).letter);
					else 
						outputString[nextSlot] = key(i).letter;
				}
			}
		return true;
	}

	/*-------------------------------------------*\
	|		 Creating And Destroying Areas        |
	\*-------------------------------------------*/

	Area createArea(int width, int height, short colorFront, short colorBack)
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
			area.colFront[i] = colorFront;
			area.colBack[i] = colorBack;
			area.characters[i] = DEFAULT_CHARACTER;
		}
		return area;
	}

	void resizeArea(int width, int height, Area area)
	{
		area.width = width;
		area.height = height;

		if (area.characters == NULL)
			Error(L"NULL AREA", __LINE__);


		char* newVal = (char*)realloc(NULL, (sizeof(char) * width * height) + 1);

		if (newVal != NULL)
			area.characters = newVal;

		area.colFront = (short*)realloc(area.colFront, (sizeof(short) * width * height));
		area.colBack = (short*)realloc(area.colBack, (sizeof(short) * width * height));

		for (int i = 0; i < (width * height); i++)
		{
			area.colFront[i] = defaultFrontColor;
			area.colBack[i] = defaultBackColor;
			area.characters[i] = DEFAULT_CHARACTER;
		}
	}

	void deleteArea(Area area)
	{
		free(area.characters);
		free(area.colFront);
		free(area.colBack);
		area.width = -1;
		area.height = -1;
		area.characters = NULL;
		area.colFront = NULL;
		area.colBack = NULL;
	}

	/*-------------------------------------------*\
	|	 Functions For Starting And Stoping		  |
	\*-------------------------------------------*/

	WINDOW_BUFFER_SIZE_RECORD wbsr = { 0 };

	void resizeCorrect()
	{
		int w, h;
		getConsoleWindowSize(&w, &h);
		SetConsoleWindowSize(&w, &h, true);

		needsResizeCorrection = false;
	}

	void mouseEvents()
	{
		//get mouse location
		INPUT_RECORD irInBuf[300];
		DWORD events = 0;

		// Wait for the events.
		GetNumberOfConsoleInputEvents(hConsoleInput, &events);
		if (events > 0)
			if (!ReadConsoleInput(hConsoleInput, irInBuf, events, &events))
				Error(L"failed reading console inputs\n", __LINE__);

		bool scrollWMOVED = false, scrollHMOVED = false;
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
#ifdef ALLOW_WINDOW_RESIZE
			case WINDOW_BUFFER_SIZE_EVENT:
			{
				needsResizeCorrection = true;
				wbsr = irInBuf[i].Event.WindowBufferSizeEvent;

				buffW = wbsr.dwSize.X;
				buffH = wbsr.dwSize.Y;

				deleteArea(Screen);
				Screen = createArea(buffW, buffH, Yellow, Red);
				ScreenSpace.startX = 0, ScreenSpace.startY = 0, ScreenSpace.endX = buffW, ScreenSpace.endY = buffH;
				screenBufferFull = (char*)realloc(screenBufferFull, sizeof(char) * ((buffW * buffH) * ANSI_STR_LEN + 1));
				for (int i = 0; i < ((buffW * buffH) * ANSI_STR_LEN + 1); i++) screenBufferFull[i] = 0;
				
				hasBeenResized = true;
				resizeCorrect();
			}
#endif
			default: break;//resizeCorrect(); break;
			}
		}
		if (!scrollHMOVED)
			Mouse.scrollH = 0;
		if (!scrollWMOVED)
			Mouse.scrollW = 0;
	}

	int terminateACRE(void)
	{
		terminated = true;
		if (SetConsoleOutputCP(65001) == 0)
			Error(L"Changing codepage back to default failed.", __LINE__);

		free(screenBufferFull);
		deleteArea(Screen);

		return 0;
	}
	
	void startKeys()
	{
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
		allKeys[Spacebar].letter = VK_SPACE, allKeys[Shift].letter = VK_SHIFT, allKeys[Alt].letter = VK_MENU, allKeys[Tab].letter = VK_TAB, allKeys[Comma].letter = VK_OEM_COMMA, allKeys[Period].letter = VK_OEM_PERIOD,
			allKeys[Colon].letter = VK_OEM_1, allKeys[Slash].letter = VK_OEM_2, allKeys[QuestionMark].letter = '?', allKeys[Backspace].letter = VK_BACK;

		allKeys[Num0].letter = '0', allKeys[Num1].letter = '1', allKeys[Num2].letter = '2', allKeys[Num3].letter = '3', allKeys[Num4].letter = '4';
		allKeys[Num5].letter = '5', allKeys[Num6].letter = '6', allKeys[Num7].letter = '7', allKeys[Num8].letter = '8', allKeys[Num9].letter = '9',
			terminated = false;
	}

	void initialize(const char* title, int width, int height, int fontWidth, int fontHeight, int defaultFront, int defaultBack)
	{
		strcpy(windowTitle, title);
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

		if (hConsoleOutput == INVALID_HANDLE_VALUE) Error(L"Retreiving Console Output Handle Failed", __LINE__);
		if (hConsoleInput == INVALID_HANDLE_VALUE) Error(L"Retreiving Console Input Handle Failed", __LINE__);

		ConsoleWindow = GetConsoleWindow();

		#ifdef ACRE_FULLSCREEN
			checkActiveWindow = false;
		#endif
		//set default values
		if (defaultFront != Default) defaultFrontColor = defaultFront;
		if (defaultBack != Default) defaultBackColor = defaultBack;
		if (width != Default) buffW = width;
		if (height != Default) buffH = height;
		if (fontWidth != Default) globalFontWidth = fontWidth;
		if (fontHeight != Default) globalFontHeight = fontHeight;

		SetFont(globalFontWidth, globalFontHeight, FONT_WEIGHT, 65001);
		SetConsoleWindowSize(&buffW, &buffH, true);

		setRequiredModes();
		printf("\x1b[?25l"); // hide the console cursor

		if ((int)title != Default) SetConsoleTitleA(title);
		else SetConsoleTitleA("AMZG Studio - ACREngine - Github");
		if (terminated == false) terminateACRE();

		screenBufferFull = (char*)malloc(sizeof(char) * ((buffW * buffH) * ANSI_STR_LEN + 1));

		Screen = createArea(buffW, buffH, defaultFrontColor, defaultBackColor);
		ScreenSpace.startX = 0, ScreenSpace.startY = 0, ScreenSpace.endX = buffW, ScreenSpace.endY = buffH;
		
		for (int i = 0; i < ((buffW * buffH) * ANSI_STR_LEN + 1); i++) screenBufferFull[i] = 0;

		if(roundOne)
			startKeys();
		
		resizeCorrect();
		QueryPerformanceCounter(&start);
		srand((unsigned int)start.QuadPart);

		areaToDrawOn = &Screen;
		roundOne = false;
	}

	/*-------------------------------------------*\
	|		     Functions for Rendering	  	  |
	\*-------------------------------------------*/

	void addColorToBuffer(int foregroundColor, int backgroundColor)
	{
		screenBufferFull[nextOpenSlot] = '\033', screenBufferFull[nextOpenSlot + 1] = '[';
		nextOpenSlot += 2;

		if (foregroundColor != -1)
		{
			memcpy(&screenBufferFull[nextOpenSlot], "38;5;", 5);
			char buffer[8] = { 0 };
			nextOpenSlot += 5;
			_itoa((int)foregroundColor, buffer, 10);
			strncpy(screenBufferFull + nextOpenSlot, buffer, 3);
			nextOpenSlot += 3; 
		}
		if (foregroundColor != -1 && backgroundColor != -1) 
			screenBufferFull[nextOpenSlot] = ';', nextOpenSlot++;
		
		if (backgroundColor != -1)
		{
			memcpy(&screenBufferFull[nextOpenSlot], "48;5;", 5);
			nextOpenSlot += 5;
			char buffer[8] = { 0 };
			_itoa((int)backgroundColor, buffer, 10);
			strncpy(screenBufferFull + nextOpenSlot, buffer, 3);
			nextOpenSlot += 3;
		}
		screenBufferFull[nextOpenSlot] = 'm';
		nextOpenSlot++;
	}
	
	void render(bool clearScreen)
	{
		memcpy(screenBufferFull, "\033[0;0H", 6);
		nextOpenSlot = 6;

		int currentForeground = -1, currentBackground = -1;
		
		for (int i = 0; i < buffW * buffH; i++)
		{
			if (Screen.colFront[i] != currentForeground && Screen.colBack[i] != currentBackground)
			{
				currentForeground = Screen.colFront[i];
				currentBackground = Screen.colBack[i];
				addColorToBuffer(Screen.colFront[i], Screen.colBack[i]);
			}
			else if (Screen.colBack[i] != currentBackground)
			{
				currentBackground = Screen.colBack[i];
				addColorToBuffer(-1, Screen.colBack[i]);
			}
			else if (Screen.colFront[i] != currentForeground)
			{
				currentForeground = Screen.colFront[i];
				addColorToBuffer(Screen.colFront[i], -1);
			}
			screenBufferFull[nextOpenSlot] = Screen.characters[i];
			nextOpenSlot++;
		}

		//render	
		if (!WriteConsoleA(hConsoleOutput, screenBufferFull, nextOpenSlot, NULL, NULL))
			Error(L"Rendering failed.", __LINE__);

		if (clearScreen) 
			clear(Screen);

		if (!QueryPerformanceFrequency(&frequency))
			Error(L"Getting Performance Frequency Failed!", __LINE__);

		if (!QueryPerformanceCounter(&end))
			Error(L"Getting Performace Counter Failed!", __LINE__);

		deltaTime = (float)(end.QuadPart - start.QuadPart) / (float)frequency.QuadPart;
		//		deltaTime = clamp((float)(end.QuadPart - start.QuadPart) / (float)frequency.QuadPart, 0, 1);
		
		start = end;

		if (currFPSslot >= FPS_TICKS)
		{
			fps = 1.0f / (totalTimes / currFPSslot);
			totalTimes = 0;
			currFPSslot = 0;
			showDefaultFPS = false;
		}
		else if (showDefaultFPS)
		{
			fps = 1.0f / (totalTimes / currFPSslot);
		}
		

		char currentTitle[200] = { 0 };
		
	#if defined(SHOW_FPS) && !defined(NO_ACRE_WATERMARK)
		sprintf(currentTitle, "%s - ACREngine - %.1f fps", windowTitle, fps);
		
	#elif defined(SHOW_FPS) && defined(NO_ACRE_WATERMARK)
		sprintf(currentTitle, "%s - %.1f fps", windowTitle, fps);

	#elif !defined(NO_ACRE_WATERMARK)
		sprintf(currentTitle, "%s - ACREngine", windowTitle);

	#else
		strcat(currentTitle, windowTitle);

	#endif
		SetConsoleTitleA(currentTitle);

		totalTimes += deltaTime;
		currFPSslot++;

	mouseEvents();
	}
#endif