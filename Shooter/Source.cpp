#include <vector>
#include <algorithm>

#include "Bullet.h"
#include "Player.h"
#include "Zombie.h"

#define SHOW_FPS
#define ACRE_START
#include "../ACRE Files/ACREngine.h"

int main()
{
	initalize("Game Game!", 300, 200, 3, 3, Default, Default);

	Player p;
	std::vector<Bullet> bullets;
	std::vector<Zombie> zombies;

	while (true)
	{
		if (key(Spacebar).pressed)
			bullets.push_back(Bullet(p.getX(), p.getY(), Mouse.x, Mouse.y));

		if (key(Q).pressed)
			zombies.push_back(Zombie(p));

		p.update();
		p.draw();

		// update and draw bullets and zombies
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.update(); item.draw(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.update(); item.draw(); });

		// remove bullets that hit, and damage zombie
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&zombies](auto&& item)
			{ return item.damageOther(zombies, 15); }), bullets.end());
	
		// remove off screen bullets from vector
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](auto&& item) 
			{ return item.getX() > Width(Screen) || item.getX() < 0 || item.getY() > Width(Screen) || item.getY() < 0; }), bullets.end());

		// remove dead zombies
		zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [](auto&& item)
			{ return !item.isAlive(); }), zombies.end());

		drawText(2, 2, "Health: ", EightBit, White);
		drawNumber(2+stringWidth("Health", EightBit)+8, 2, p.getHealth(), EightBit, White);
		render(true);
	}
	return terminateACRE();
}
