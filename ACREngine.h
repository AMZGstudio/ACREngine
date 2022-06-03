/*
ACREngine, a game engine that runs entirely in the console!

original github:
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

*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WIN32_WINNT 0x0500
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>

#ifndef DEFAULT_CHARACTER
#define DEFAULT_CHARACTER ' '
#endif

#define WIDTHESCAPE 24
#ifndef FPS
#define FPS 100
#endif
#ifndef FULLSCREEN
#define FULLSCREEN false
#endif
#define AMOUNT_KEYS 49
#define hideCursor() printf("\033[?25l")
enum defaultTypes { EightBit = -503, Thirds = -502, Centered = -501, Default = -1, A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Up, Down, Left, Right, EnterKey, EscapeKey, LeftM, RightM, SpaceKey, ShiftKey, Comma, QuestionMark, Backspace, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0};
enum colors { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Grey};
enum special {LightShade = 176, MediumShade = 177, DarkShade = 178, FullBlock = 219, LowerHalfBlock = 220, LeftHalfBlock = 221, RightHalfBlock = 222, UpperHalfBlock = 223};

typedef struct Point {
	int x, y;
} Point;
typedef struct COLORVAL {
	int red, green, blue;
} COLORVAL;
typedef struct Key {
	bool pressed;
	bool held;
	int letter;
} Key;
typedef struct Space {
	int startX, startY, endX, endY;
} Space;
typedef struct Image {
	int** colorArray;
	char** characterArray;
	int width, height;
} Image;
/**************************************************************************************************
Global Variables
**************************************************************************************************/
char title[100] = { 0 };
char* screenBuffer = NULL, *screenBufferFull = NULL;
int* backgroundBuffer = NULL, *foregroundBuffer = NULL;
int fps = -1, nextOpenSlot = 0, bufferWidth = 100, bufferHeight = 50, fontWidth = 12, fontHeight = 12, defaultFrontColor = White, defaultBackColor = Black;
float elapsedTime = 0;
bool checkActiveWindow = false, terminated = true;
//windows handles
HANDLE hConsoleOutput, hConsoleInput;
HWND ConsoleWindow;
//others
Point Mouse = { 0, 0 };
Key allKeys[AMOUNT_KEYS] = { 0 };
Space Screen = { 0, 0, 0, 0 };
clock_t startTime = 0;

//MessageBox(NULL, L"Hello there, an error occured", NULL, MB_OK);
/**************************************************************************************************
General functions
**************************************************************************************************/
char font8x8_basic[128][8] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},
	{ 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},
	{ 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},{ 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},
	{ 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},{ 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},{ 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},
	{ 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},{ 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},{ 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},{ 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},
	{ 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},{ 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},
	{ 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},{ 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},
	{ 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},{ 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},
	{ 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},{ 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},
	{ 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},{ 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},
	{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},
	{ 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},{ 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},
	{ 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},{ 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},
	{ 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},{ 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},
	{ 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},{ 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},
	{ 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},
	{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},{ 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},
	{ 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},{ 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
	{ 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},{ 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},
	{ 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},{ 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},
	{ 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},{ 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},
	{ 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},{ 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},
	{ 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},{ 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},
	{ 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},
	{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},{ 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},
	{ 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},{ 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},
	{ 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},{ 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},
	{ 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},{ 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},
	{ 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
	{ 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},
	{ 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},{ 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},
	{ 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},{ 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},
	{ 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},
	{ 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},{ 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
	{ 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},{ 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},
	{ 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},{ 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},
	{ 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},{ 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},
	{ 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},
	{ 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},{ 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},
	{ 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},{ 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},
	{ 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},
	{ 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},{ 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},
	{ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},{ 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},
	{ 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};
Image createImage(char* imageFilePath)
{
	char supportedVersion[] = "acgev2.0", ch, currentVersion[10] = { 0 }, width[5] = { 0 }, height[5] = { 0 };
	FILE* image = fopen(imageFilePath, "r");
	if (image == NULL) while (1) printf("Opening file failed.\n");
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
int width(Space screenSpace)
{
	return screenSpace.endX - screenSpace.startX;
}
int height(Space screenSpace)
{
	return screenSpace.endY - screenSpace.startY;
}
int xyLoc(int x, int y)
{
	if (x < bufferWidth && x >= 0 && y < bufferHeight && y >= 0)
		return ((y * bufferWidth) + x);
	return -1;
}
int random(int rangeStart, int rangeEnd)
{
	return (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;
}
int readColor(FILE* imageFile)
{
	int selected = 0;
	char ch, color[5] = { 0 };
	while ((ch = fgetc(imageFile)) != ';' && ch != '\n')
		color[selected] = ch, selected++;
	
	return atoi(color);
}
int center(int length, Space screenSpace, int mode)
{	
	float value = 0;
	if (mode == X) value = screenSpace.startX + ((float)((float)screenSpace.endX - (float)screenSpace.startX + 1) / 2.0) - ((float)length / 2.0); //  1-10 should be a distance of 10, se we add 1
	if (mode == Y) value = screenSpace.startY + ((float)((float)screenSpace.endY - (float)screenSpace.startY + 1) / 2.0) - ((float)length / 2.0); //  1-10 should be a distance of 10, se we add 1
	return (int)value;
}
int thirds(int firstOrSecond, int mode)
{
	//TODO
}
Space getSpace(Space prevSpace, int xStart, int yStart, int xEnd, int yEnd)
{
	Space Location = { 0, 0, 0, 0 };
	
	if (xStart == Centered)
	{
		Location.startX = center(xEnd, prevSpace, X);
		Location.endX = Location.startX + xEnd;
	}
	else
	{
		Location.startX = prevSpace.startX + xStart;
		Location.endX = prevSpace.startX + xEnd;
	}
	if (yStart == Centered)
	{
		Location.startY = center(yEnd, prevSpace, Y);
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
int Color(int r, int g, int b)
{
#   define v2ci(v) (v < 48 ? 0 : v < 115 ? 1 : (v - 35) / 40)
	int ir = v2ci(r), ig = v2ci(g), ib = v2ci(b);   // 0..5 each
#   define color_index() (36 * ir + 6 * ig + ib)  /* 0..215, lazy evaluation */

	int average = (r + g + b) / 3;
	int gray_index = average > 238 ? 23 : (average - 3) / 10;  // 0..23

	static const int i2cv[6] = { 0, 0x5f, 0x87, 0xaf, 0xd7, 0xff };
	int cr = i2cv[ir], cg = i2cv[ig], cb = i2cv[ib];  // r/g/b, 0..255 each
	int gv = 8 + 10 * gray_index;  // same value for r/g/b, 0..255

#   define dist_square(A,B,C, a,b,c) ((A-a)*(A-a) + (B-b)*(B-b) + (C-c)*(C-c))
	int color_err = dist_square(cr, cg, cb, r, g, b);
	int gray_err = dist_square(gv, gv, gv, r, g, b);
	return color_err <= gray_err ? 16 + color_index() : 232 + gray_index; // this code is note mine
} // removed static int, and replaced with int
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
int SetFont(int fontSizeX, int fontSizeY, UINT codePage)
{
	int returnValue = 0; //0 means ok
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.X = fontSizeX;
	info.dwFontSize.Y = fontSizeY; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, 9, L"Consolas");
	if (!SetCurrentConsoleFontEx(hConsoleOutput, 0, &info)) while (1) printf("Setting console font failed.\n");;
	//char text[500] = { 0 }GetLastError();
	if (!SetConsoleOutputCP(codePage)) while (1) printf("Setting consoles codepage failed.\n");
	return returnValue;
}
void SetConsoleWindowSize(int* x, int* y)
{
	if (FULLSCREEN) SetConsoleDisplayMode(hConsoleOutput, CONSOLE_FULLSCREEN_MODE, 0);
	if (hConsoleOutput == INVALID_HANDLE_VALUE) while (1) printf("Unable to get stdout handle.");
	{
		COORD largestSize = GetLargestConsoleWindowSize(hConsoleOutput);
		if (FULLSCREEN)
		{
			(*x) = largestSize.X;
			(*y) = largestSize.Y;
		}
		if ((*x) > largestSize.X) while (1) printf("ERROR: X dimension to big. (%d > %d)\n", (*x), largestSize.X);
		if ((*y) > largestSize.Y) while (1) printf("ERROR: Y dimension to big. (%d > %d)\n", (*y), largestSize.Y);
	}
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(hConsoleOutput, &bufferInfo)) while(1) printf("Unable to retrieve screen buffer info.");

	SMALL_RECT winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > (*x) || windowSize.Y > (*y))
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info = { 0,0,(*x) < windowSize.X ? (*x) - 1 : windowSize.X - 1,(*y) < windowSize.Y ? (*y) - 1 : windowSize.Y - 1 };
		if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info)) while (1) printf("Resizing Window Failed.\n");
	}
	COORD size = { (*x), (*y) };
	if (!SetConsoleScreenBufferSize(hConsoleOutput, size)) while(1) printf("Unable to resize screen buffer.");

	SMALL_RECT info = { 0, 0, (*x) - 1, (*y) - 1 };
	if (!SetConsoleWindowInfo(hConsoleOutput, TRUE, &info)) while(1) printf("Unable to resize window after resizing buffer.");
}
void setMouse(bool visible) {
	if (!visible)
		while (ShowCursor(false) >= 0);
}
bool windowActive()
{
	if (!checkActiveWindow) return true;
	if (ConsoleWindow == GetForegroundWindow()) return true;
	else return false;
}
bool setRequiredModes()
{
	// Set flags to allow mouse input, and disable selecting		
	if (!SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		while (1) printf("Giving the console input attributes failed.\n");
}
/**************************************************************************************************
Drawing to the screen functions (draw functions
**************************************************************************************************/
Point sysDrawPoint(int x, int y, Space screenSpace, char character, int colorFront, int colorBack)
{
	if (character == '\n' || character == 0) while (1) printf("ERROR: tried to print new line\n");
	int slot = xyLoc(screenSpace.startX + x, screenSpace.startY + y);
	if (character != Default) screenBuffer[slot] = character;
	if (colorFront != Default) foregroundBuffer[slot] = colorFront;
	if (colorBack != Default) backgroundBuffer[slot] = colorBack;
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
}
Space sysDrawTriange(int x1, int y1, int x2, int y2, int x3, int y3, Space screenSpace, char character, bool filled, int colorFront, int colorBack)
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
	if (!radius) return;

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
	}
	return circleSpace;*/
}
Space sysDrawImage(int x, int y, Space screenSpace, Image inputImage)
{
	Space rectLocation = getSpace(screenSpace, x, y, (x == Centered) ? inputImage.width : x + inputImage.width - 1,
													 (y == Centered) ? inputImage.height : y + inputImage.height - 1);

	int colorx = 0, colory = 0, y2, x2;
	for (x2 = rectLocation.startX; x2 <= rectLocation.endX; x2++)
	{
		for (y2 = rectLocation.startY; y2 <= rectLocation.endY; y2++)
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
	char* letter = font8x8_basic[character];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int set = letter[i] & 1 << j;
			sysDrawPoint(x+j, y+i, screenSpace, Default, colorFront, set ? colorBack : Default);
		}
	}
}
Space sysDrawText(int x, int y, Space screenSpace, const char* text, int fontType, int colorFront, int colorBack)
{
	int stringLength = 0, i=0;
	while (text[i] != '\n' && text[i] != 0)
		i++;

	int textWidth = i * ((fontType == EightBit) ? 8 : 1);
	Space textSpace = getSpace(screenSpace, x, y, (x == Centered) ? textWidth : x + textWidth - 1, (fontType == EightBit) ? 8 : 1);
	//Space textSpace = { 0, 0, 0, 0 };
	
	int slot = 0;
	x = textSpace.startX, y=textSpace.startY;

	int xPrev = textSpace.startX;
	while (text[slot]!=0)
	{
		if (text[slot] == '\n') x = xPrev, y+=(fontType==EightBit)?9:1;
		else
		{
			if (fontType == EightBit) sysDrawFontChar(x, y, Screen, text[slot], colorFront, colorBack);
			else sysDrawPoint(x, y, Screen, text[slot], colorFront, colorBack);
			x+=(fontType == EightBit) ? 8 : 1;
		}
		slot++;
	}
	//return textSpace;
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
	_itoa_s(number, text, 30, 10);
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

Space drawMenu(int xStart, int yStart, Space screenSpace, int menuWidth, int seperation, int selected, int numOptions, int colorFront, int colorBack, ...)
{
	char** options = (char**)malloc(sizeof(char*) * numOptions);
	Space rect;

	va_list ptr;
	va_start(ptr, colorBack);
	for (int i = 0; i < numOptions; i++)
	{
		options[i] = (char*)malloc(sizeof(char) * 100);
		for (int j = 0; j < 100; j++) options[i][j] = 0;
		strcpy(options[i], va_arg(ptr, char*));
	}
	va_end(ptr);
	int longestOption = 0;
	for (int i = 0; i < numOptions; i++)
		if ((signed)strlen(options[i]) >= longestOption) longestOption = strlen(options[i]);

	int menuPadding = ((menuWidth - longestOption) / 2);
	for (int i = 0; i < numOptions; i++)
	{
		if (i == selected)
		{
			if (xStart == Centered) rect = sysDrawRect(xStart, yStart, menuWidth, 1, screenSpace, Default, true, colorFront, colorBack);
			else rect = sysDrawRect(xStart, yStart, xStart + menuWidth, yStart, screenSpace, Default, true, colorFront, colorBack);
			sysDrawText(Centered, 1, rect, options[i], Default, Default, Default);
		}
		else
		{
			if (xStart == Centered) rect = sysDrawRect(xStart, yStart, menuWidth, 1, screenSpace, Default, false, colorBack, Default);
			else rect = sysDrawRect(xStart, yStart, xStart + menuWidth, yStart, screenSpace, Default, true, Default, Default);
			sysDrawText(Centered, 1, rect, options[i], Default, Default, Default);
		}
		yStart += seperation;
	}
	for (int i = 0; i < numOptions; i++)
		free(options[i]);
	free(options);
}
Space drawRect(int xStart, int yStart, int xEnd, int yEnd, int color)
{
	return sysDrawRect(xStart, yStart, xEnd, yEnd, Screen, Default, false, Default, color);
}
Space drawRectFilled(int xStart, int yStart, int xEnd, int yEnd, int color)
{
	return sysDrawRect(xStart, yStart, xEnd, yEnd, Screen, Default, true, Default, color);
}
Space drawCircle(int x, int y, int radius, int color)
{
	return sysDrawCircle(x, y, Screen, radius, Default, false, Default, color);
}
void drawTriange(int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
	sysDrawTriange(x1, y1, x2, y2, x3, y3, Screen, Default, false, Default, color);
}
void drawLine(int xStart, int yStart, int xEnd, int yEnd, int color)
{
	sysDrawLine(xStart, yStart, xEnd, yEnd, Screen, Default, Default, color);
}
Space drawImage(int x, int y, Image img)
{
	return sysDrawImage(x, y, Screen, img);
}
Space drawText(int x, int y, const char* text, int fontType, int color)
{
	return sysDrawText(x, y, Screen, text, fontType, (fontType == EightBit) ? defaultFrontColor : color, (fontType == EightBit) ? (color == Default) ? defaultFrontColor : color : defaultBackColor);
}
Point drawPoint(int x, int y, int colorBack)
{
	return sysDrawPoint(x, y, Screen, Default, Default, colorBack);
}
Point drawChar(int x, int y, char character, int colorFront)
{
	return sysDrawPoint(x, y, Screen, character, colorFront, Default);
}
Space drawInt(int x, int y, int number, int fontType, int color)
{
	return sysDrawInt(x, y, Screen, number, fontType, (fontType == EightBit) ? defaultFrontColor : color, (fontType == EightBit) ? (color == Default) ? defaultFrontColor : color : defaultBackColor);
}
Space drawOutline(int xStart, int yStart, int xEnd, int yEnd, int color)
{
	return sysDrawOutline(xStart, yStart, xEnd, yEnd, Screen, color, Default);
}

void clearScreen()
{
	sysDrawRect(0,0, width(Screen), height(Screen), Screen, DEFAULT_CHARACTER, true, defaultFrontColor, defaultBackColor);
}
/**************************************************************************************************
Input Functions (also related to windows, wont work cross platform)
**************************************************************************************************/
Key key(int whichKey)
{
	bool pressed = false;
	if ((GetAsyncKeyState(allKeys[whichKey].letter) & 0x8000) && windowActive()) pressed = true;

	if (pressed == true && allKeys[whichKey].held == false)
		allKeys[whichKey].pressed = true;

	else allKeys[whichKey].pressed = false;
	allKeys[whichKey].held = pressed;
	return allKeys[whichKey];
}
void arrowInput(int* number, int numberMin, int numberMax, int mode)
{
	if (mode == Y)
	{
		if (key(Up).pressed && *number > numberMin) *number -= 1;
		if (key(Down).pressed && *number < numberMax) *number += 1;
	}
	else if (mode == X)
	{
		if (key(Left).pressed && *number > numberMin) *number -= 1;
		if (key(Right).pressed && *number < numberMax) *number += 1;
	}
}
void textBoxInput(int colorFront, int colorBack, Space screenSpace, char* outputString, int outputStringLength, int x, int y)
{
	int nextSlot = strlen(outputString);
	for (int i = 0; i <= AMOUNT_KEYS; i++)
		if (key(i).pressed && windowActive())
		{
			if (allKeys[i].letter == allKeys[SpaceKey].letter && strlen(outputString) < outputStringLength - 1)
			{
				outputString[nextSlot] = ' ';
				break;
			}
			else if (allKeys[i].letter == allKeys[Backspace].letter)
				outputString[nextSlot - 1] = 0;
			
			else if (strlen(outputString) < outputStringLength - 1 && (allKeys[i].letter != allKeys[ShiftKey].letter) && (allKeys[i].letter != allKeys[LeftM].letter) && (allKeys[i].letter != allKeys[RightM].letter))
			{
				if(!key(ShiftKey).held)
					outputString[nextSlot] = tolower(key(i).letter);
				else outputString[nextSlot] = key(i).letter;
			}
		}
 	//drawTextSpace(colorFront, colorBack, screenSpace, outputString, x, y);
}
/**************************************************************************************************
Handing console (creating buffers, destroying buffers, rendering buffers, etc).
**************************************************************************************************/
int terminate(void)
{
	terminated = true;
	if (SetConsoleOutputCP(65001) == 0) while (1) printf("Changing codepage back to default failed.\n");
	free(screenBuffer);
	
	screenBuffer = NULL;
	return 0;
}
void initalize(const char* title, int width, int height, int bufferFontWidth, int bufferFontHeight, int defaultFront, int defaultBack)
{
	srand(time(0));

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput == 0) while (1) printf("Getting console output handle didnt work.\n");
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	ConsoleWindow = GetConsoleWindow();

	if (FULLSCREEN) checkActiveWindow = false;
	//set default values
	if (defaultFront != Default) defaultFrontColor = defaultFront;
	if (defaultBack != Default) defaultBackColor = defaultBack;
	if (width != Default) bufferWidth = width;
	if (height != Default) bufferHeight = height;
	if (bufferFontWidth != Default) fontWidth = bufferFontWidth;
	if (bufferFontHeight != Default) fontHeight = bufferFontHeight;

	SetFont(fontWidth, fontHeight, 65001);
	SetConsoleWindowSize(&bufferWidth, &bufferHeight);

	Screen.startX = 0, Screen.startY = 0, Screen.endX = bufferWidth, Screen.endY = bufferHeight;
	
	SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //makes window not resizbale
	// Set flags to allow mouse input, and disable selecting, and support for ANSI escape sequences.	
	if (!SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		while (1) printf("Setting The consoles Input modes did not work.\n");
	if (!SetConsoleMode(hConsoleOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN))
		while (1) printf("Setting The consoles Output modes did not work.\n");
	
	hideCursor();

	if (title != Default) SetConsoleTitleA(title);
	else SetConsoleTitleA("AMZG Studio - ConsoleGameEngine - Github");
	if (terminated == false) terminate();

	screenBufferFull = (char*)malloc(sizeof(char) * ((bufferWidth * bufferHeight) * WIDTHESCAPE + 1));
	screenBuffer = (char*)malloc(sizeof(char) * ((bufferWidth * bufferHeight) + 1));
	foregroundBuffer = (int*)malloc(sizeof(int) * (bufferWidth * bufferHeight));
	backgroundBuffer = (int*)malloc(sizeof(int) * (bufferWidth * bufferHeight));

	for (int i = 0; i < ((bufferWidth * bufferHeight) * WIDTHESCAPE + 1); i++) screenBufferFull[i] = 0;
	for (int i = 0; i < (bufferWidth * bufferHeight); i++)
	{
		foregroundBuffer[i] = defaultFrontColor;
		backgroundBuffer[i] = defaultBackColor;
		screenBuffer[i] = DEFAULT_CHARACTER;
	}
	allKeys[A].letter = 'A', allKeys[B].letter = 'B', allKeys[C].letter = 'C', allKeys[D].letter = 'D', allKeys[E].letter = 'E';
	allKeys[F].letter = 'F', allKeys[G].letter = 'G', allKeys[H].letter = 'H', allKeys[I].letter = 'I', allKeys[J].letter = 'J';
	allKeys[K].letter = 'K', allKeys[L].letter = 'L', allKeys[M].letter = 'M', allKeys[N].letter = 'N', allKeys[O].letter = 'O';
	allKeys[P].letter = 'P', allKeys[Q].letter = 'Q', allKeys[R].letter = 'R', allKeys[S].letter = 'S', allKeys[T].letter = 'T';
	allKeys[U].letter = 'U', allKeys[V].letter = 'V', allKeys[W].letter = 'W', allKeys[X].letter = 'X', allKeys[Y].letter = 'Y';
	allKeys[Z].letter = 'Z', allKeys[Up].letter = VK_UP, allKeys[Down].letter = VK_DOWN, allKeys[Left].letter = VK_LEFT, allKeys[Right].letter = VK_RIGHT;
	allKeys[EnterKey].letter = VK_RETURN;
	allKeys[EscapeKey].letter = VK_ESCAPE,allKeys[RightM].letter = VK_RBUTTON,allKeys[LeftM].letter = VK_LBUTTON,allKeys[SpaceKey].letter = VK_SPACE;
	allKeys[Comma].letter = ',',allKeys[QuestionMark].letter = '?',allKeys[Backspace].letter = VK_BACK, allKeys[ShiftKey].letter = VK_SHIFT;
	allKeys[Num1].letter = '1', allKeys[Num2].letter = '2', allKeys[Num3].letter = '3', allKeys[Num4].letter = '4', allKeys[Num5].letter = '5';
	allKeys[Num6].letter = '6', allKeys[Num7].letter = '7', allKeys[Num8].letter = '8', allKeys[Num9].letter = '9', allKeys[Num0].letter = '0';
	terminated = false;
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

	if (GetCursorPos(&cursor_pos))
		if (ScreenToClient(ConsoleWindow, &cursor_pos));
	{
		//cursor_pos.x = map((int)cursor_pos.x, 1, 1200, 1, 1000);
		Mouse.x = (int)((int)(cursor_pos.x) / fontWidth);
		Mouse.y = (int)((int)(cursor_pos.y) / fontHeight);
	}
	//drawInt(1, height(Screen) - 18, cursor_pos.x, EightBit, White);
	//drawInt(1, height(Screen) - 9, cursor_pos.y, EightBit, White);

	screenBufferFull[0] = '\033', screenBufferFull[1] = '[', screenBufferFull[2] = '0';
	screenBufferFull[3] = ';', screenBufferFull[4] = '0', screenBufferFull[5] = 'H';
	nextOpenSlot = 6;
	int currentForeground = -1, currentBackground = -1;
	for (int i = 0; i < bufferWidth * bufferHeight; i++)
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
	if (!WriteConsoleA(hConsoleOutput, screenBufferFull, nextOpenSlot, NULL, NULL)) while (1) printf("Rendering failed.\n");
	if (clear == true) clearScreen();
	
	elapsedTime = ((float)clock()/CLOCKS_PER_SEC)- ((float)startTime/CLOCKS_PER_SEC);
	do
	{
		int allTime = (((int)clock()) - (int)startTime);
		fps = (int)(1000.0f / ((float)allTime));

	} while (fps > FPS);
	startTime = clock();

	char title[100] = { 0 };
	_itoa(fps, title, 10);
	strcat(title, " FPS");
	SetConsoleTitleA(title);
}
