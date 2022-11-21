#define ACRE_START
#define SHOW_FPS
#include "../ACREngine.h"

#define BLOCK_W 14
#define CHESS_W 8
enum cols { white = 1, black = 2 };

Point selected = { -1,-1 };
Point placeToMove = { -1, -1 };

typedef struct Piece {char* piece; short color;} Piece;

void calculateAvailable(bool* available, char* piece, int px, int py)
{

	available[0] = true;
}
void calculations(bool* available, Piece* board)
{
	if (key(LeftM).pressed)
		if  (selected.x == -1 && selected.y == -1)
			 selected.x    = Mouse.x / 14, selected.y    = Mouse.y / 14;
		else placeToMove.x = Mouse.x / 14, placeToMove.y = Mouse.y / 14;
	
	if (placeToMove.x != -1 && placeToMove.y != -1)
	{
		Piece newVal = { 0,0 };
		newVal.piece = board[selected.y * CHESS_W + selected.x].piece;
		newVal.color = board[selected.y * CHESS_W + selected.x].color;

		board[selected.y * CHESS_W + selected.x].color = 0;
		board[selected.y * CHESS_W + selected.x].piece = 0;

		board[placeToMove.y * CHESS_W + placeToMove.x].color = newVal.color;
		board[placeToMove.y * CHESS_W + placeToMove.x].piece = newVal.piece;

		placeToMove.x = -1, placeToMove.y = -1;
		selected.x = -1, selected.y = -1;

		for (int i = 0; i < CHESS_W * CHESS_W; i++)
			available[i] = false;
	}
	if (selected.x != -1 && selected.y != -1)
	{
		Piece selectedP = board[selected.y * CHESS_W + selected.x];
		calculateAvailable(available, selectedP.piece, selected.x, selected.y);
	}
}

void resetBoard(Piece* board, bool* available)
{
	for (int i = 0; i < CHESS_W * CHESS_W; i++)
		board[i].piece = 0, board[i].color = 0, available[i] = false;
		
	char* row = "chbqkbhc";
	for (int x = 0; x < CHESS_W; x++)
	{
		board[0 * CHESS_W + x].piece = row[x], board[7 * CHESS_W + x].piece = row[x];
		board[0 * CHESS_W + x].color = white,  board[7 * CHESS_W + x].color = black;

		board[1 * CHESS_W + x].piece = 'p',    board[6 * CHESS_W + x].piece = 'p';
		board[1 * CHESS_W + x].color = white,  board[6 * CHESS_W + x].color = black;
	}
	
}
int main()
{
	initalize("Chess", 112, 112, 5, 5, Default, Default);
	Area ponW  = loadSprite("Chess/pw.acre");
	Area ponB  = loadSprite("Chess/pb.acre");

	Area castleW=loadSprite("Chess/cw.acre");
	Area castleB=loadSprite("Chess/cb.acre");

	Area bishopW=loadSprite("Chess/bw.acre");
	Area bishopB=loadSprite("Chess/bb.acre");

	Area horseW =loadSprite("Chess/hw.acre");
	Area horseB =loadSprite("Chess/hb.acre");

	Area kingW = loadSprite("Chess/kw.acre");
	Area kingB = loadSprite("Chess/kb.acre");

	Area queenW =loadSprite("Chess/qw.acre");
	Area queenB =loadSprite("Chess/qb.acre");

	Piece* board    = malloc(sizeof(char) * CHESS_W * CHESS_W);
	bool* available = malloc(sizeof(bool) * CHESS_W * CHESS_W);
	
	resetBoard(board, available);

	while (true)
	{
		calculations(available, board);

		for (int x = 0; x < 8; x++)
			for (int y = 0; y < 8; y++)
			{
				int color = ((x + y) % 2) ? Color(200,200,200) : Color(25,100,25);
				int xs = map(x, 0, CHESS_W, 0, Width(Screen));
				int ys = map(y, 0, CHESS_W, 0, Width(Screen));
				
				if (selected.x == x && selected.y == y) color = Yellow;
				if (available[y * CHESS_W + x] == true) color = Red;

				drawRectFilled(xs, ys, xs + BLOCK_W, ys + BLOCK_W, color);
				Piece boardPiece = board[y * CHESS_W + x];

				if (boardPiece.piece == 'p' && boardPiece.color == white) drawArea(xs, ys, ponW);
				if (boardPiece.piece == 'p' && boardPiece.color == black) drawArea(xs, ys, ponB);

				if (boardPiece.piece == 'c' && boardPiece.color == white) drawArea(xs, ys, castleW);
				if (boardPiece.piece == 'c' && boardPiece.color == black) drawArea(xs, ys, castleB);

				if (boardPiece.piece == 'b' && boardPiece.color == white) drawArea(xs, ys, bishopW);
				if (boardPiece.piece == 'b' && boardPiece.color == black) drawArea(xs, ys, bishopB);

				if (boardPiece.piece == 'h' && boardPiece.color == white) drawArea(xs, ys, horseW);
				if (boardPiece.piece == 'h' && boardPiece.color == black) drawArea(xs, ys, horseB);

				if (boardPiece.piece == 'q' && boardPiece.color == white) drawArea(xs, ys, queenW);
				if (boardPiece.piece == 'q' && boardPiece.color == black) drawArea(xs, ys, queenB);

				if (boardPiece.piece == 'k' && boardPiece.color == white) drawArea(xs, ys, kingW);
				if (boardPiece.piece == 'k' && boardPiece.color == black) drawArea(xs, ys, kingB);
			}
		
		render(true);
	}
	free(board);
	free(available);
	 
	return terminate();
}