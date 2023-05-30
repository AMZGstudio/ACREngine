#define ACRE_START
#define SHOW_FPS true
#include "../acre files/ACREngine.h"

int spawnNum(int* boardState, int w, int h)
{
	int x = rand() % w, y = rand() % h;
	while(boardState[y*w+x] != 0)
		x = (rand() % w), y = (rand() % h);

	boardState[y*w+x] = rand() % 100 >= 60 ? 4 : 2;
}

int compress(int direction, int* boardState, int w, int h)
{
	for (int time = 0; time < 4; time++)
	{
		int wd = 0, wideOrHigh = 0;

		if (direction == 2 || direction == 4)
			wd = w, wideOrHigh = 1;

		if (direction == 1 || direction == 3)
			wd = h, wideOrHigh = 2;

		for (int d = 0; d < wd; d++)
		{
			if (direction == 1 || direction == 2)
			{
				for (int s = 0; s < (direction == 1 ? h : w); s++)
				{
					if (boardState[direction == 1 ? s * w + d : d * w + s] == 0 && s < ((direction == 1 ? h : w) - 1))
					{
						if (direction == 1)
						{
							boardState[s * w + d] = boardState[(s + 1) * w + d];
							boardState[(s + 1) * w + d] = 0;
						}
						else if (direction == 2)
						{
							boardState[d * w + s] = boardState[d * w + s + 1];
							boardState[d * w + s + 1] = 0;
						}
					}
				}
			}
			if (direction == 3 || direction == 4)
			{
				for (int s = (direction == 3) ? h - 1 : w - 1; s >= 0; s--)
				{
					if (boardState[(direction == 3) ? s * w + d : d * w + s] == 0 && s > 0)
					{
						if (direction == 3)
						{
							boardState[s * w + d] = boardState[(s - 1) * w + d];
							boardState[(s - 1) * w + d] = 0;
						}
						else if (direction == 4)
						{
							boardState[d * w + s] = boardState[d * w + s - 1];
							boardState[d * w + s - 1] = 0;
						}
					}
				}
			}
		}
	}
}

int merge(int direction, int* boardState, int w, int h)
{
	//for(int )
}

int main()
{
	int width = 4, height = 4;
	int blockWidth = 38, blockHeight = 38;
	initalize("2048 - AMZG", width*blockWidth+1, height*blockHeight+1, 4, 4, Default, Default);

	int* boardState = malloc(sizeof(int) * width * height);
	for (int i = 0; i < width * height; i++)
		boardState[i] = 0;

	while (!key(Esc).pressed)
	{
		for (int x = 0; x<width; x++)
			for (int y = 0; y < height; y++)
			{
				int locx = map(x, 0, width, 0, width * blockWidth);
				int locy = map(y, 0, height, 0, height * blockHeight);
				Space rect = drawRect(locx+1, locy+1, locx + blockWidth-1, locy + blockHeight-1, Red);
				
				if (boardState[y * width + x] != 0)
				{
					char text[5] = { 0 };
					_itoa(boardState[y * width + x], text, 10);
					sysDrawText(Centered, Centered, rect, text, EightBit, Default, White);
				}
			}

		if (key(Q).pressed)
			spawnNum(boardState, width, height);

		if (key(A).pressed)
			compress(2, boardState, width, height);

		if (key(D).pressed)
			compress(4 , boardState, width, height);

		if(key(W).pressed)
			compress(1, boardState, width, height);

		if (key(S).pressed)
			compress(3, boardState, width, height);

		render(true);
	}


	return 0;
}