#define ACRE_START
#include "../acre files/ACREngine.h"

int cell(int x, int y, int w, int h, int* board)
{
	if ((x < w && x >= 0 && y < h && y >= 0))
		return board[(y)*w + (x)]; // returns the board at the x and y coord.
}

int countNeighbors(int* board, int x, int y, int w, int h)
{
	return // each one is going to be 1 or 0, add them all up to see how many neighbors there are.
		cell(x + 1, y + 1, w, h, board) + cell(x, y + 1, w, h, board) + cell(x + 1, y, w, h, board) +
		cell(x - 1, y - 1, w, h, board) + cell(x, y - 1, w, h, board) + cell(x - 1, y, w, h, board) +
		cell(x + 1, y - 1, w, h, board) + cell(x - 1, y + 1, w, h, board);
}

int main()
{
	initalize("ACREngine - Game of life", 200, 100, 5, 5, Default, Grey);

	bool playing = false;

	int* board = malloc(sizeof(int) * Width(Screen) * Height(Screen));
	int* board2 = malloc(sizeof(int) * Width(Screen) * Height(Screen));

	// set the boards to be emtpy
	for (int i = 0; i < Width(Screen) * Height(Screen); i++)
		board[i] = 0, board2[i] = 0;

	while (!key(Esc).pressed)
	{	
		for(int x = 1; x<Width(Screen)-1; x++)
			for (int y = 1; y < Height(Screen)-1; y++)
			{
				// if the game is running run the rules of the game
				if (playing)
				{
					// check how many neighbors a cell has.
					int amountBors = countNeighbors(board, x, y, Width(Screen), Height(Screen));

					if (amountBors < 2 || amountBors > 3)
						board2[y * Width(Screen) + x] = 0;

					else
						board2[y * Width(Screen) + x] = board[y * Width(Screen) + x];

					if (amountBors == 3)
						board2[y * Width(Screen) + x] = 1;
				}
				// draw the pixel, at the approprite x and y coord.
				drawPoint(x, y, board[y * Width(Screen) + x] ? White : Black);
			}
		// if the game is running, copy everything from the second buffer to the first.
		if(playing)
			for (int i = 0; i < Width(Screen) * Height(Screen); i++)
				board[i] = board2[i];

		if (key(R).pressed)
			for (int i = 0; i < Width(Screen) * Height(Screen); i++)
				board[i] = rand() % 2;

		// when the spacebar is pressed reverse playing, so if it was true, then its false.
		if (key(Spacebar).pressed)
			playing = !playing;

		// if the user left clicks, then fill the board with a peice (1)
		if (key(LeftM).held)
			board[(Mouse.y) * Width(Screen) + (Mouse.x)] = 1;
		
		render(true);
	}
	return terminate();
}