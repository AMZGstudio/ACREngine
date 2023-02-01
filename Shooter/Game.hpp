#pragma once

#include "Audio.h"

#include "Bullet.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include "Collision.hpp"

#include <algorithm>
#include <format>

class Game : public acre::State
{
private:
	bool paused = false;
	Player p;
	Space spPaused = { 0 };

	std::vector<Bullet> bullets;
	std::vector<Zombie> zombies;

	acre::Menu m;
	acre::Renderer* _ar;

	acre::Fade f;

	int ammo = 15;

public:
	static int score;
	
	Game(acre::Renderer* r) : f(r), m(Five, calcSpace(ScreenSpace, Centered, Centered, 80, 50), true)
	{ 
		m.addOption("Exit", Centered, Default);
		m.addOption("Resume", Centered, Default);

		spPaused = calcSpace(ScreenSpace, Centered, Centered, 80, 100);
	}

	void initalizer() override
	{
		p = Player();
		bullets.clear();
		zombies.clear();
		paused = false;
		Wave::reset();
		score = 0;
		ammo = 15;
		aud.playSound("music", true);
	}

	void update()
	{
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.update(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.update(); });

		p.update();
		Wave::attemptNext(zombies.size() == 0);

		if (Wave::spawnZombie())
		{
			Zombie zom(p, zombies, 32 + Wave::waveNum * 8);
			zombies.push_back(zom);
		}

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [this](auto&& item)
			{   return item.damageOther(this->zombies, 15) || // remove bullets that hit, and damage zombie
			(item.getX() > Width(Screen) || item.getX() < 0 || item.getY() > Width(Screen) || item.getY() < 0); // remove off screen bullets from vector
			}), bullets.end());

		// remove dead zombies
		zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [this](auto&& item)
			{ if (!item.isAlive()) score += 100; return !item.isAlive(); }), zombies.end());


		if (key(Spacebar).pressed || key(LeftM).pressed)
		{
			if (ammo > 0)
			{
				aud.playSound("firing");
				bullets.push_back(Bullet(p.getX(), p.getY(), p.getVX(), p.getVY(), Mouse.x, Mouse.y));
				ammo--;
			}
			else
				aud.playSound("empty");
		}

		if (key(R).pressed)
		{
			aud.playSound("reload");
			ammo = 15;
		}
			
	}
	void draw()
	{
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.draw(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.draw(); });

		p.draw();

		const char* s = std::format("Wave: {}", Wave::waveNum).c_str();

		drawText(Width(Screen) - txtWidth(s, Pzim) - 2, 2, s, Pzim, White);
		drawText(2, 2, std::format("Health: {:.1f}", p.getHealth()).c_str(), Pzim, White);
		drawText(2, 10, std::format("Ammo: {}", ammo).c_str(), Pzim, White);
		drawText(Centered, 2, std::format("Score: {}", score).c_str(), Pzim, White);

		//drawPixel(Mouse.x-1, Mouse.y, Red);
		//drawPixel(Mouse.x, Mouse.y+1, Red);
		//drawPixel(Mouse.x, Mouse.y-1, Red);
		//drawPixel(Mouse.x+1, Mouse.y, Red);
	}

	void runState() override
	{
		f.fadeOutIfNecessary();
		if (f.fadeInFinished())
		{
			setState("menu");
			reset();
		}
		
		// if player is dead, reset
		if (!p.isAlive())
		{
			setState("over");
			reset();
			return;
		}

		if (key(Esc).pressed)
		{
			paused = !paused;
			m.noneSelected();
		}

		if (paused)
		{
			draw();
			
			drawRectFilled(spPaused.startX, spPaused.startY, spPaused.endX, spPaused.endY, VeryDarkGrey);
			drawRect(spPaused.startX, spPaused.startY, spPaused.endX, spPaused.endY, DarkGrey);
			drawText(Centered, spPaused.startY + 6, "Paused", Five, White);

			if (m.pressed() && f.notFading())
			{
				int index = m.indexPressed();

				switch (index)
				{
				case 0: f.fadeIn(); break;
				case 1: paused = false; break;
				}
			}
	
			m.calculations();
			m.draw();

			return;
		}
		else
		{
			update();
			draw();
		}
	}
};

int Game::score = 0;