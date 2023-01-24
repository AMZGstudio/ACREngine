#pragma once

#include "State.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include "Collision.hpp"

#include <algorithm>
#include <format>

class Game : public State
{
private:
	Player p;
	std::vector<Bullet> bullets;
	std::vector<Zombie> zombies;

public:
	static int score;

	Game() : p(), bullets(), zombies()
	{
		score = 0;
	}

	void runState(std::string& state) override
	{
		// check to make sure the player is not dead
		if (!p.isAlive())
			state = "over";

		if (key(Spacebar).pressed || key(LeftM).pressed)
			bullets.push_back(Bullet(p.getX(), p.getY(), p.getVX(), p.getVY(), Mouse.x, Mouse.y));

		Wave::attemptNext(zombies.size() == 0);

		if (Wave::spawnZombie(3))
		{
			Zombie zom(p, zombies, 32 + Wave::waveNum * 8);
			zombies.push_back(zom);
		}
			

		p.update();
		p.draw();

		// update and draw bullets and zombies
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.update(); item.draw(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.update(); item.draw(); });

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [this](auto&& item)
			{   return item.damageOther(this->zombies, 15) || // remove bullets that hit, and damage zombie
				(item.getX() > Width(Screen) || item.getX() < 0 || item.getY() > Width(Screen) || item.getY() < 0); // remove off screen bullets from vector
			}), bullets.end());

		// remove dead zombies
		zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [this](auto&& item)
			{ if (!item.isAlive()) score += 100; return !item.isAlive(); }), zombies.end());

		drawText(2, 2, std::format("Health: {:.1f}", p.getHealth()).c_str(), Pzim, White);
		drawText(2, 10, std::format("Wave:   {}", Wave::waveNum).c_str(), Pzim, White);
		drawText(2, 18, std::format("Num Zombies: {}", zombies.size()).c_str(), Pzim, White);
		drawText(Centered, 2, std::format("Score: {}", score).c_str(), Pzim, White);
	}
};

int Game::score = 0;