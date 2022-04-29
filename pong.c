#define WAIT 35
#define PADDLE_HEIGHT 10
#include "ConsoleEngine.h"

bool checkCol(int paddleX, int paddleY, int paddleX2, int paddleY2, float ballX, float ballY)
{
	if ((ballX + 1 > paddleX) && (ballX -1 <= paddleX2) && (ballY >= paddleY) && (ballY <= paddleY2)) return true;
	else return false;
}

int main()
{
	initalize("Pong", 100, 50, 10, 10, Default, Default);
	int paddleHR = 1, paddleHL = 1;
	int paddleDR = 1, paddleDL = 1;

	float ballX = 50, ballY = 25, ballVX = 1.5, ballVY = 0.5;
	int color = White;

	while (true)
	{
		color = White;
		drawSquare(1, 1, 100, 50, Default, Black);
		drawSquare(2, paddleHL, 3, paddleHL + PADDLE_HEIGHT, Default, White);
		drawSquare(98, paddleHR, 99, paddleHR + PADDLE_HEIGHT, Default, White);

		if (checkCol(97, paddleHR, 99, paddleHR + PADDLE_HEIGHT, ballX, ballY) || checkCol(2, paddleHL, 4, paddleHL + PADDLE_HEIGHT, ballX, ballY)) ballVX *= -1;
		if (ballY - 1 <= 1 || ballY + 1 >= 50) ballVY *= -1, color = Red;
		if (ballX - 1 <= 1 || ballX + 1 >= 100) ballVX *= -1, color = Red;

		drawSquare((int)ballX - 1, (int)ballY - 1, (int)ballX + 1, (int)ballY + 1, Default, color);
		drawChar('/', ballX - 1, ballY - 1, Default,Black);
		drawChar('\\', ballX + 1, ballY - 1, Default, Black);
		drawChar('\\', ballX - 1, ballY + 1, Default, Black);
		drawChar('/', ballX + 1, ballY + 1, Default, Black);
		
		ballX += ballVX, ballY += ballVY;

		if (key('W', 0)) paddleHL--;
		if (key('S', 0)) paddleHL++;

		if (key('O', 0)) paddleHR--;
		if (key('L', 0)) paddleHR++;

		render(true);
	}
	return terminate();
}