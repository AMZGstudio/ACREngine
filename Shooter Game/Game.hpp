#pragma once

#include "Audio.h"

#include "Bullet.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include "Collision.hpp"

#include "health.hpp"

#include <algorithm>
#include <format>

class Game : public acre::State
{
private:
	enum splashState {FadingIn, Waiting, FadingOut, None};

	Space spPaused = { 0 };
	bool paused = false;
	int index; // for paused screen
	int ammo = 15;

	Player p;
	std::vector<Bullet> bullets;
	std::vector<Zombie> zombies;

	acre::Renderer* _ar;
	acre::Fade f;

	acre::Menu pausedMenu;
	acre::Menu waveScreen;

	splashState ss = None;
	float timePassed = 0;
	HealthBar hb;

	acre::Interval coolDown;
	acre::Interval background;
	acre::Interval reloading;

	AreaTrans* at;
	
private:
	void drawWave(int num, AreaTrans* at)
	{
		clear(at->area);
		acre::sysDrawShadowedText(Centered, 0, at->area, "Wave " + std::to_string(num), Five, Color(200, 200, 200), DarkRed);
	}

	void shoot()
	{
		if (!ammo)
			return aud.playSound("empty");

		if (reloading.getPaused())
		{
			aud.playSound("firing");
			bullets.push_back(Bullet(p.getX(), p.getY(), p.getRadius(), Mouse.x, Mouse.y));
			ammo--;
		}
	}

public:
	static int score;
	
	Game(acre::Renderer* r) : coolDown(2, 0), reloading(0.5, 0), background(9, 16, 0), f(r), waveScreen(DefaultFont, {}), pausedMenu(Five, calcSpace(ScreenSpace, Centered, Centered, 80, 50), true)
	{ 
		pausedMenu.addOption("Restart", Centered, Default);
		pausedMenu.addOption("Resume", Centered, Default);
		pausedMenu.addOption("Exit", Centered, Default);

		spPaused = calcSpace(ScreenSpace, Centered, Centered, 80, 100);

		Area splash = createArea(txtWidth("Wave XXXX", Five) + 1, Five.height + 1, Default, Default);
		waveScreen.setArea(splash, Centered, 40, 3);

		at = &waveScreen.getAT();
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
		index = -1;

		at->opacity = 0;
		timePassed = 0;

		ss = None;
		aud.playSound("music", true);
		reloading.pause();
	}

	void update()
	{
		// update all entities
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.update(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.update(); });
		p.update();

		// calculate intervals
		background.calculate();
		coolDown.calculate();
		reloading.calculate();

		if (background.timePassed())
			Audio::playSound("background" + std::to_string(Random(1, 5)));

		if (reloading.timePassed())
		{
			ammo = 15;
			reloading.pause();
			reloading.resetTime();
		}
		
		if (coolDown.timePassed() && zombies.size() == 0)
		{
			Wave::nextWave();
			coolDown.pause();
			ss = FadingIn;
			drawWave(Wave::waveNum, at);
		}	

		if (zombies.size() == 0)
			coolDown.resume();

		if (Wave::spawnZombie())
			zombies.push_back(Zombie(p, zombies, 30 + Wave::waveNum * 6));

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [this](auto&& item)
			{   return item.damageZombie(this->zombies, 15) || // remove bullets that hit, and damage zombie
					   item.damagePlayer(p, 3)              || // remove bullets that hit a player, and damage the player.
			(          item.getX() > Width(Screen) || item.getX() < 0 || item.getY() > Width(Screen) || item.getY() < 0); // remove off screen bullets from vector
			
			}), bullets.end());

		// remove dead zombies
		zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [this](auto&& item)
			{ if (!item.isAlive()) { score += 100; }; return !item.isAlive(); }), zombies.end());

		if (ss == FadingIn) at->opacity += timePerSec(1);
		if (ss == FadingOut) at->opacity -= timePerSec(1);
		
		if (at->opacity >= 1) ss = Waiting;
		if (at->opacity <= 0) ss = None;

		if (ss == Waiting) timePassed += timePerSec(0.5);

		if (timePassed > 1)
		{
			timePassed = -1;
			ss = FadingOut;
		}

		if (key(Spacebar).pressed || key(LeftM).pressed)
			shoot();

		if (key(R).pressed || key(RightM).pressed)
		{
			aud.playSound("reload");
			reloading.resume();
		}
	}
	
	void draw()
	{		
		// draw entities
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.draw(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.draw(); });
		p.draw();

		waveScreen.drawArea();
		acre::drawShadowedText(Centered, 2, std::format("Score: {}", score), Pzim, White, DarkGrey);
		hb.draw(p.getHealth(), ammo);
	}

	void runState() override
	{
		f.fadeOutIfNecessary();
		if (f.fadeInFinished())
		{
			switch (index)
			{
			case 0: setState("game"); break;
			case 2: setState("menu"); break;
			}
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
			pausedMenu.deselectOptions();
		}

		if (paused)
		{
			draw();
			
			drawRectFilled(spPaused.startX, spPaused.startY, spPaused.endX, spPaused.endY, VeryDarkGrey);
			drawRect(spPaused.startX, spPaused.startY, spPaused.endX, spPaused.endY, DarkGrey);
			drawText(Centered, spPaused.startY + 6, "Paused", Five, White);

			if (pausedMenu.pressed() && f.notFading())
			{
				index = pausedMenu.indexPressed();

				if (index == 1)
					paused = false;
					
				else f.fadeIn();
			}
	
			pausedMenu.calculations();
			pausedMenu.draw();

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

// 298