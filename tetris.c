#define ACRE_START
#define SHOW_FPS
#define ACRE_FONTS

#include "ACREngine.h"
#include "ACRE_Fonts.h"

typedef struct Piece {
	char* data;
	int width;
} Piece;

Piece allPieces[7] = { {".t.ttt...", 3},
	{".ssss....", 3},{"....iiii........",4},{".j..j.jj.", 3},
	{".l..l..ll", 3},{"zz..zz...", 3},{"oooo", 2} };

Piece* currPiece;
Piece* nextPiece;
Piece* heldPiece;

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

int boardWidth = 10;
int boardHeight = 20;

bool placed = false;
bool edgeCase = false;

Image  tb, sb, ib, jb, lb, zb, ob;

Space gameSpace = { 5,  20, 55, 120};
Space nextSpace = { 62, 98, 84, 120};
Space heldSpace = { 62, 62, 84, 84 };
Space winsSpace = { 62, 30, 84, 39 };

char board[(BOARD_HEIGHT * BOARD_WIDTH) + 1] = { 0 };

void drawThickText(const char* text, Space space, Font font, int y, int x)
{
	if(x == Centered) x = center(stringLength(text, font), space, X);
	if (y == Centered) y = center(8, space, Y);

	drawText(space.startX+x + 1, space.startY+y + 1, text, font, VeryDarkGrey);
	drawText(space.startX+x, space.startY+y, text, font, White);
}
char calcuatePiece(int amntRotated, Piece* piece, int x, int y)
{
	char thingToRotate = 0;
	if (amntRotated < 0)
		amntRotated = 4 - amntRotated;

	amntRotated = amntRotated % 4;

	int widthS = piece->width - 1;
	switch (amntRotated)
	{
	case 0: thingToRotate = piece->data[y * piece->width + x]; break;
	case 1: thingToRotate = piece->data[(widthS - x) * piece->width + y]; break;
	case 2: thingToRotate = piece->data[(widthS - y) * piece->width + (widthS - x)]; break;
	case 3: thingToRotate = piece->data[x * piece->width + (widthS - y)]; break;
	}
	return thingToRotate;
}

void drawPeice(int x, int y, char blockType, Image tb, Image sb, Image ib, Image jb, Image lb, Image zb, Image ob)
{
	switch (blockType)
	{
	case 't': drawImage(x, y, tb); break;
	case 's': drawImage(x, y, sb); break;
	case 'i': drawImage(x, y, ib); break;
	case 'j': drawImage(x, y, jb); break;
	case 'l': drawImage(x, y, lb); break;
	case 'z': drawImage(x, y, zb); break;
	case 'o': drawImage(x, y, ob); break;
	}
}

void drawBlocks(int amntRotated, int currX, int currY)
{
	if(currPiece != NULL)
		for (int x = 0; x < currPiece->width; x++)
			for (int y = 0; y < currPiece->width; y++)
				drawPeice(gameSpace.startX + currX + x * 5, gameSpace.startY + currY + y * 5, calcuatePiece(amntRotated, currPiece, x, y), tb, sb, ib, jb, lb, zb, ob);
	
	if (nextPiece != NULL)
	{
		int xStart = center(nextPiece->width * 5, nextSpace, X);
		int yStart = center(nextPiece->width * 5, nextSpace, Y);

		for (int x = 0; x < nextPiece->width; x++)
			for (int y = 0; y < nextPiece->width; y++)
				drawPeice(nextSpace.startX + xStart + x * 5, nextSpace.startY + yStart + y * 5, calcuatePiece(0, nextPiece, x, y), tb, sb, ib, jb, lb, zb, ob);
	}
	if (heldPiece != NULL)
	{
		int xStart = center(heldPiece->width * 5, heldSpace, X);
		int yStart = center(heldPiece->width * 5, heldSpace, Y);

		for (int x = 0; x < heldPiece->width; x++)
			for (int y = 0; y < heldPiece->width; y++)
				drawPeice(heldSpace.startX + xStart + x * 5, heldSpace.startY + yStart + y * 5, calcuatePiece(0, heldPiece, x, y), tb, sb, ib, jb, lb, zb, ob);
	}
	for (int y = 0; y < boardHeight; y++)
		for (int x = 0; x < boardWidth; x++)
			drawPeice(gameSpace.startX + x * 5, gameSpace.startY + y * 5, board[y * boardWidth + x], tb, sb, ib, jb, lb, zb, ob);
}

void drawEverything(int amntRotated, int pieceX, int pieceY, int score)
{
	drawRectFilled(gameSpace.startX, gameSpace.startY, gameSpace.endX, gameSpace.endY, Grey);
	drawRectFilled(nextSpace.startX, nextSpace.startY, nextSpace.endX, nextSpace.endY, Grey);
	drawRectFilled(heldSpace.startX, heldSpace.startY, heldSpace.endX, heldSpace.endY, Grey);
	drawBlocks(amntRotated, pieceX, pieceY);

	drawThickText("TETRIS", Screen, M38, 5, Centered);
	drawThickText("Score", winsSpace, Pzim, -10, Centered);
	drawThickText("Held", heldSpace, Pzim, -10, Centered);
	drawThickText("Next", nextSpace, Pzim, -10, Centered);
	
	drawRect(heldSpace.startX - 1, heldSpace.startY - 1, heldSpace.endX + 1, heldSpace.endY + 1, VeryDarkGrey);
	drawRect(gameSpace.startX - 1, gameSpace.startY - 1, gameSpace.endX + 1, gameSpace.endY + 1, VeryDarkGrey);
	drawRect(nextSpace.startX - 1, nextSpace.startY - 1, nextSpace.endX + 1, nextSpace.endY + 1, VeryDarkGrey);

	char numString[10] = { 0 };
	intToStr(numString, score);
	int numberLoc = center(stringLength(numString, Pzim), winsSpace, X);

	sysDrawNumber(numberLoc+1, 1, winsSpace, score, 0, Pzim, Default, VeryDarkGrey);
	sysDrawNumber(numberLoc,   0, winsSpace, score, 0, Pzim, Default, White);
}
void resetBoard()
{
	for (int i = 0; i < (boardHeight * boardWidth); i++)
		board[i] = '.';
}

bool clearLines(int* score)
{
	bool anyFilled = false;
	for (int y = 0; y < boardHeight; y++)
	{
		bool filled = true;
		for (int x = 0; x < boardWidth; x++)
			if (board[y * boardWidth + x] == '.')
				filled = false;

		if (filled)
		{
			*score += 15;
			anyFilled = true;
			for (int x = 0; x < boardWidth; x++)
				board[y * boardWidth + x] = '.';
		}
	}
	for (int y = boardHeight - 1; y >= 0; y--) 
	{
		if (y > 0)
		{
			bool empty = true;
			for (int x = 0; x < boardWidth; x++)
				if (board[y * boardWidth + x] != '.')
					empty = false;

			if (empty)
				for (int x = 0; x < boardWidth; x++)
				{
					board[y * boardWidth + x] = board[(y - 1) * boardWidth + x];
					board[(y - 1) * boardWidth + x] = '.';
				}
		}
	}
	return anyFilled;
}

bool checkCollison(Piece* piece, int pieceX, int pieceY, int rotateAmount)
{
	if(piece != NULL)
		for (int x = 0; x < piece->width; x++)
			for (int y = 0; y < piece->width; y++)
			{
				char val = calcuatePiece(rotateAmount, piece, x, y);

				int realY = (int)((pieceY + y * 5) / 5.0f);
				int realX = (int)((pieceX + x * 5) / 5.0f);

				if (val != '.')
					if (board[realY * 10 + realX] != '.' || realX < 0 || realX >= 10)
						return true;
			}
	return false;
}
int getRandomPiece()
{
	return rand() % 7;
}
bool updateGame(int* pieceX, float* pieceY, int* rotateAmount, int* score)
{
	if (currPiece == NULL)
	{
		if (!edgeCase)
			placed = true;

		if (nextPiece == NULL)
		{
			currPiece = &allPieces[getRandomPiece()];
			nextPiece = &allPieces[getRandomPiece()];
		}
		else
		{
			currPiece = nextPiece;
			nextPiece = &allPieces[getRandomPiece()];
		}
		*pieceX = 20, * pieceY = 0;
		*rotateAmount = rand() % 4;

		if (checkCollison(currPiece, *pieceX, *pieceY, *rotateAmount))
		{
			currPiece = NULL;
			return false;
		}
	}
	bool tabPressed = key(Tab).pressed;
	if (tabPressed && placed && heldPiece == NULL)
	{
		edgeCase = true;
		placed   = false;
		
		(*pieceY) = 0, (*pieceX) = 20;
		heldPiece = currPiece;
		currPiece = NULL;
	}
	else if (tabPressed && placed)
	{
		placed = false;
		(*pieceY) = 0, (*pieceX) = 20;

		Piece* temp = heldPiece;
		heldPiece = currPiece;
		currPiece = temp;
	}
	if (tabPressed) edgeCase = false;

	bool aPressed = false, dPressed = false;
	bool rotatedCW = false, rotatedCCW = false;

	if (aPressed = key(A).pressed) (*pieceX) -= 5;
	if (dPressed = key(D).pressed) (*pieceX) += 5;
	if (rotatedCW = key(E).pressed) (*rotateAmount)++;
	if (rotatedCCW = key(Q).pressed) (*rotateAmount)--;

	if (key(S).held) *pieceY += timePerSec(80);
	else *pieceY += timePerSec(16);

	if(checkCollison(currPiece, *pieceX, *pieceY, *rotateAmount))
	{
		if (aPressed) (*pieceX) += 5;
		if (dPressed) (*pieceX) -= 5;
		if (rotatedCW) (*rotateAmount)--;
		if (rotatedCCW) (*rotateAmount)++;
	}
	if (checkCollison(currPiece, *pieceX, *pieceY + 3.8, *rotateAmount))
	{
		for (int x = 0; x < currPiece->width; x++)
			for (int y = 0; y < currPiece->width; y++)
			{
				char val = calcuatePiece(*rotateAmount, currPiece, x, y);
				if (val != '.')
				{
					int realY = (int)((*pieceY + y * 5) / 5.0f);
					int realX = (int)((*pieceX + x * 5) / 5);

					board[realY * boardWidth + realX] = val;
				}
			}
		(*score) += 1;
		currPiece = NULL;
	}
	return true;
}

int main()
{
	initalize("Tetris", 90, 140, 5, 5, Default, DarkGrey);
	
	Image pointer = loadImage("tetris/pointer.acre");
	Image backdrop = loadImage("tetris/backdrop.acre");
	Image controls = loadImage("tetris/controls.acre");
	Image rightArrow = loadImage("tetris/rightArrow.acre");
	Image leftArrow = loadImage("tetris/leftArrow.acre");
	Image downArrow = loadImage("tetris/downArrow.acre");
	Image msg1 = loadImage("tetris/msg1.acre");

	int selected = 0;
	char* options[4] = { "Play", "Controls", "Credits", "Exit"};

	bool startGame = false;
	bool closeGame = false;
	while (!startGame && !closeGame)
	{
		drawRect(8, 18, Width(Screen) - 8, Height(Screen) - 18, VeryDarkGrey);
		drawThickText("TETRIS", Screen, M38, 5, Centered);
		
		for (int i = 0; i < 4; i++)
		{
			if (i == selected)
			{
				int width = stringLength(options[i], EightBit) + 4;
				Space rect = drawRect(Centered, 23 + 12 * i, width, 35 + 12 * i, Grey);
				drawImage(rect.startX - 1 - pointer.width, rect.startY + 3, pointer);
			}
			drawThickText(options[i], Screen, EightBit, 25 + 12 * i, Centered);
		}
		if (key(Enter).pressed)
		{
			while (!key(Esc).held && !startGame && !closeGame)
			{
				if (selected == 0)
				{
					startGame = true;
				}
				if (selected == 1)
				{
					int y = 40;
					int x = center(60, Screen, X) - 6;
					drawImage(x, y, controls);
					drawImage(x+7, y+25, leftArrow);
					drawImage(x + 55, y + 25, rightArrow);
					drawImage(x+31, y + 35, downArrow);
					drawImage(x-4, y-3, msg1);
				}
				if (selected == 2)
				{
					drawThickText("Game Made", Screen, EightBit, 20, Centered);
					drawThickText("By AMZG!", Screen, EightBit, 31, Centered);

					drawThickText("Using", Screen, EightBit, 50, Centered);
					drawThickText("ACRE On", Screen, EightBit, 61, Centered);
					drawThickText("Github", Screen, EightBit, 80, Centered);
				}
				if (selected == 3) closeGame = true;
					
				render(true);
			}
		}

		if (key(W).pressed) selected--;
		if (key(S).pressed) selected++;
		
		drawImage(0, Height(Screen) - backdrop.height, backdrop);
		render(true);
	}
	
	if (startGame)
	{
		resetBoard();

		float pieceY = 0;
		int   pieceX = 0;
		int   score = 0;
		int   amntRotated = 0;

		tb = loadImage("tetris/ppeice.acre");
		sb = loadImage("tetris/gpeice.acre");
		ib = loadImage("tetris/cpeice.acre");
		jb = loadImage("tetris/bpeice.acre");
		lb = loadImage("tetris/opeice.acre");
		zb = loadImage("tetris/rpeice.acre");
		ob = loadImage("tetris/ypeice.acre");

		while (true)
		{
			if (key(Esc).pressed)
			{
				while (!key(Esc).pressed)
				{
					drawEverything(amntRotated, pieceX, pieceY, score);
					drawRectFilled(Centered, Centered, 76, 14, Grey);
					drawRect(Centered, Centered, 76, 14, VeryDarkGrey);
					drawThickText("Paused", Screen, EightBit, Centered, Centered);
					render(true);
				}
			}
			if (updateGame(&pieceX, &pieceY, &amntRotated, &score))
			{
				if (clearLines(&score))
				{
					Timer timer = createTimer();
					while (timer.elapsedTime < 0.3)
					{
						drawEverything(amntRotated, pieceX, pieceY, score);
						calculateTimer(&timer);
						render(true);
					}
				}

				drawEverything(amntRotated, pieceX, pieceY, score);
			}
			else
			{
				while (!key(Enter).held)
				{
					
					drawEverything(amntRotated, pieceX, pieceY, score);
					drawRectFilled(Centered, Centered, 83, 40, DarkGrey);
					Space rect = drawRect(Centered, Centered, 83, 40, VeryDarkGrey);
					drawThickText("GAME OVER", rect, EightBit, 6, Centered);

					char scoreMsg[20] = { "Score: "};
					char scoreStr[10] = { 0 };
					intToStr(scoreStr, score);
					strcat(scoreMsg, scoreStr);
					drawThickText(scoreMsg, rect, Pzim, 17, Centered);
					render(true);
				}
				score = 0;
				heldPiece = NULL;

				resetBoard();
			}
			render(true);
		}
		
	}
	return terminate();
}