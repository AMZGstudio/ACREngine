#include "Game.h"
#include <algorithm>
#include <vector>

Game::Game() : p(), bullets(), zombies()
{
}

void Game::runState()
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
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [this](auto&& item)
		{ return item.damageOther(this->zombies, 15); }), bullets.end());

	// remove off screen bullets from vector
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](auto&& item)
		{ return item.getX() > Width(Screen) || item.getX() < 0 || item.getY() > Width(Screen) || item.getY() < 0; }), bullets.end());

	// remove dead zombies
	zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [](auto&& item)
		{ return !item.isAlive(); }), zombies.end());

	drawText(2, 2, "Health: ", EightBit, White);
	drawNumber(2 + stringWidth("Health", EightBit) + 8, 2, p.getHealth(), EightBit, White);
}
