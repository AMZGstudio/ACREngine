#define PZIM_FONT
#define ACRE_SHOW_FPS

#define ACRE_START
#include "../acre files/ACREngine.h"

#define ACRE_FONTS
#include "../acre files/ACRE_Fonts.h"

#include "Camera.hpp"
#include "Entity.hpp"

#include <string>

void start()
{
    setFullscreen(true);
    // we create the screen, with the window title, dimensions, the text foreground, and background color. over here, its black text on a white background.
    initialize("Demo Game", 180, 110, 8, 8, Black, Black); // TIP: write Default, for default foreground and background.

    int blockSize = 14;

    Area floor = loadSprite("../sprites/tile_floor.acre");
    Area wall = loadSprite("../sprites/tile_wall.acre");

    // world
    int w = 10, h = 10;
    std::string map;

    map += "XXXXXXXXXX";
    map += "X........X";
    map += "X........X";
    map += "X........X";
    map += "X........X";
    map += "X........X";
    map += "X........X";
    map += "X........X";
    map += "X........X";
    map += "XXXXXXXXXX";

    Entity oldman({ 0, 0 }, Entity::LeftSide);
    oldman.add_side("../sprites/oldman_left.acre", Entity::LeftSide);
    oldman.add_side("../sprites/oldman_right.acre", Entity::RightSide);

    Entity player({ 0, 0 }, Entity::LeftSide);
    player.add_side("../sprites/bot_front.acre", Entity::FrontSide);
    player.add_side("../sprites/bot_back.acre", Entity::BackSide);
    player.add_side("../sprites/bot_left.acre", Entity::LeftSide);
    player.add_side("../sprites/bot_right.acre", Entity::RightSide);
    
    Camera camera(&player);

    while (!key(Esc).pressed)
    {
        if (key(W).held) player.set_facing(Entity::BackSide), player._pos.y -= amntPerSec(60);
        if (key(A).held) player.set_facing(Entity::LeftSide), player._pos.x -= amntPerSec(60);
        if (key(S).held) player.set_facing(Entity::FrontSide), player._pos.y += amntPerSec(60);
        if (key(D).held) player.set_facing(Entity::RightSide), player._pos.x += amntPerSec(60);

        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
            {
                v2i real = camera.w_to_screen(v2f(x * blockSize, y * blockSize), Screen.w, Screen.h);

                switch (map[y * w + x])
                {
                case 'X': drawArea(real.x, real.y, wall); break; 
                case '.': drawArea(real.x, real.y, floor); break;
                }
            }

        v2i pos = camera.w_to_screen(player._pos, Screen.w, Screen.h);

        player.draw(pos);
        Space sp = player.get_bounding_box();

        drawRect(pos.x + sp.xStart, pos.y + sp.yStart, spWidth(sp)+1, spHeight(sp)+1, Green);

        drawNumber(0, 0, fps, Pzim, White);
        render(true);
    }
}

//
//#define ACRE_SHOW_FPS
//#define ACRE_START
//#include "../acre files/ACREngine.h"
//
//void start()
//{
//	initialize("Title", 40, 20, 14, 14, Default, White);
//
//	while (true)
//	{
//		sysDrawPixel(Mouse.x, Mouse.y, Screen, '#', Yellow, Default);
//		render(true);
//	}
//}