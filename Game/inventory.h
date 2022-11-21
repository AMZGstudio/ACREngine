

typedef struct Item {
	int id;
	Area* img;
} Item;

typedef struct Items {
	int w, h;
	Item* items;
} Items;

Items initalizeInventory(int w, int h)
{
	Items i;
	i.items = (Item*)malloc(sizeof(Item) * w * h);
	i.w = w;
	i.h = h;
	return i;
}

void drawInventory(int y, Items i)
{
	int boxW = 8;
	int rectX = center((i.w * boxW) + 3, ScreenSpace, X);
	int rectY = y - 9 - (i.h * boxW) + 3;

	sysDrawRect(rectX, rectY, rectX + (i.w * boxW) + 3, rectY + (i.h * boxW) + 3, surface, Default, true, Default, DarkGrey);

	for (int x = 0; x < i.w; x++)
		for (int y = 0; y < i.h; y++)
			sysDrawRect(rectX + 2 + (x * boxW), rectY + 2 + (y * boxW), rectX + 2 + ((x + 1) * boxW) - 1, rectY + 2 + ((y + 1) * boxW) - 1, surface, Default, true, Default, Grey);

}