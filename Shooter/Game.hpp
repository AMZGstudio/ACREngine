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
	enum splashState {FadingIn, Waiting, FadingOut, None};
	enum coolDownState { Neither, Started, Finished };

	Space spPaused = { 0 };
	bool paused = false;
	int index; // for paused screen

	Player p;
	std::vector<Bullet> bullets;
	std::vector<Zombie> zombies;

	acre::Renderer* _ar;
	acre::Fade f;

	acre::Menu pausedMenu;
	acre::Menu waveScreen;

	splashState ss = None;
	coolDownState cds = Neither;
	float timePassed = 0;
	float coolDown = 0;
	float coolDownTime = 3;

	int ammo = 15;
	
private:
	void drawWave(int num, AreaTrans& at)
	{
		std::string text;

		if (num == -1)
			text = "Wave XXXX";

		else
			text = "Wave " + std::to_string(num);

		int x = (int)((float)Width(at.area) / 2 - (float)txtWidth(text.c_str(), Five) / 2.0f);
		sysDrawText(x + 1,1, at.area, text.c_str(), Five, Default, DarkRed);
		sysDrawText(x,    0, at.area, text.c_str(), Five, Default, Color(200,200,200));
	}

public:
	static int score;
	
	Game(acre::Renderer* r) : f(r), waveScreen(DefaultFont, {}), pausedMenu(Five, calcSpace(ScreenSpace, Centered, Centered, 80, 50), true)
	{ 
		pausedMenu.addOption("Restart", Centered, Default);
		pausedMenu.addOption("Resume", Centered, Default);
		pausedMenu.addOption("Exit", Centered, Default);

		spPaused = calcSpace(ScreenSpace, Centered, Centered, 80, 100);

		Area splash = createArea(txtWidth("Wave XXXX", Five) + 1, Five.height + 1, Default, Default);
		waveScreen.setArea(splash, Centered, 40, 2);

		AreaTrans& at = waveScreen.getAT();
		at.opacity = 0;
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

		AreaTrans& at = waveScreen.getAT();
		at.opacity = 0;
		timePassed = 0;
		coolDown = 0;

		cds = Neither;
		ss = None;

		aud.playSound("music", true);
	}

	void update()
	{
		AreaTrans& at = waveScreen.getAT();
		
		std::for_each(bullets.begin(), bullets.end(), [](auto&& item) { item.update(); });
		std::for_each(zombies.begin(), zombies.end(), [](auto&& item) { item.update(); });

		p.update();

		if (cds == Finished)
			if (Wave::attemptNext(zombies.size() == 0))
			{
				ss = FadingIn, cds = Neither;
				drawWave(Wave::waveNum, at);
			}	

		if (zombies.size() == 0)
			cds = Started;

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


		if (cds == Started)
			coolDown += timePerSec(1);

		if (coolDown > 2)
		{
			cds = Finished;
			coolDown = 0;
		}	

		if (ss == FadingIn)
			at.opacity += timePerSec(1);
		if (ss == FadingOut)
			at.opacity -= timePerSec(1);
		
		if (at.opacity >= 1)
			ss = Waiting;
		if (at.opacity <= 0)
			ss = None;

		if (ss == Waiting)
			timePassed += timePerSec(0.5);

		if (timePassed > 1)
		{
			timePassed = -1;
			ss = FadingOut;
		}

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

		if (key(R).pressed || key(RightM).pressed)
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

		waveScreen.drawArea();

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

				else
					f.fadeIn();
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