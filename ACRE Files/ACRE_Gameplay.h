#pragma once

#ifdef ACRE_3_COMPATIBLE

	#ifndef ACRE_EX_GAMEPLAY
		#define ACRE_EX_GAMEPLAY
	#endif

#ifdef ACRE_GAMEPLAY

#include <vector> 
#include <string>
#include <map>

namespace acre
{
	/*-------------------------------------------*\
	|				 Renderer Class	    		  |
	\*-------------------------------------------*/

	class Renderer
	{
	private:
		Area _window;

		float fadeProgress;
		float fadeIncrement;

	public:
		enum fadeState { Neither, startedFadeIn, finished, startedFadeOut };
		fadeState fs;

		Renderer()
		{
			_window = createArea(Width(Screen), Height(Screen), Default, Default);
			setDefaultDrawArea(&_window);

			fs = Neither;
			fadeProgress = 0;
			fadeIncrement = 2;
		}
		Area getWindow()
		{
			return _window;
		}
		void draw()
		{
			if (fs == startedFadeIn || fs == startedFadeOut)
			{
				if (fadeProgress < 1)
					for (int y = 0; y < Height(Screen); y++)
						for (int x = 0; x < Width(Screen); x++)
						{
							short r, g, b;
							Xterm(_window.colBack[y * Width(Screen) + x], &r, &g, &b);
							
							r -= map(fs == startedFadeOut ? 1 - fadeProgress : fadeProgress, 0, 1, 0, 255);
							g -= map(fs == startedFadeOut ? 1 - fadeProgress : fadeProgress, 0, 1, 0, 255);
							b -= map(fs == startedFadeOut ? 1 - fadeProgress : fadeProgress, 0, 1, 0, 255);
							
							sysDrawPoint(x, y, Screen, Default, Default, Color(clamp(r, 0, 255), clamp(g, 0, 255), clamp(b, 0, 255)));
						}

				fadeProgress += timePerSec(fadeIncrement);
				if (fadeProgress > 1)
				{
					fadeProgress = 0;
					if (fs == startedFadeIn) fs = finished;
					if (fs == startedFadeOut) fs = Neither;
				}
					
			}

			else if (fs == finished)
			{
				clear();
			}
			else
			{
				sysDrawArea(0, 0, Screen, _window);
			}
		}

		void render()
		{
			::render(false);
		}
		void clear()
		{
			::clear(_window);
		}
		bool fadingIn()
		{
			return fs == startedFadeIn;
		}
		bool finishedFade()
		{
			return fs == finished;
		}
		bool notFading()
		{
			return fs == Neither;
		}
		void startFadeIn()
		{
			fs = startedFadeIn;
		}
		void startFadeOut()
		{
			fs = startedFadeOut;
		}
	};

	class Fade
	{
	private:
		Renderer* r;
		bool thisCalledFade;

	public:
		Fade(Renderer* rendererPointer)
		{
			r = rendererPointer;
		}
		void fadeOutIfNecessary()
		{
			if (!thisCalledFade && r->finishedFade())
				r->startFadeOut();
		}
		bool fadeInFinished()
		{
			if (r->finishedFade() && thisCalledFade)
			{
				thisCalledFade = false;
				return true;
			}
			return false;
		}
		bool notFading()
		{
			return r->notFading();
		}
		void fadeIn()
		{
			if (notFading())
			{
				thisCalledFade = true;
				r->startFadeIn();
			}
		}
	};
	/*-------------------------------------------*\
	|				   Menu Class	    		  |
	\*-------------------------------------------*/

	/*
	Class Notes:

	When creating an option, if you specify the x as Default, it will become Centered.
	if you specify y as Default, it will add the y to be the next layer down.

	*/
	class Menu
	{
	public:
		struct Option
		{
			std::string text;
			int x, y;
			float r = 255, g = 255, b = 255;
		};

	private:
		// options and options space.
		std::vector<Option> _options;
		Space spOptions;
		Font _font;

		// selected option and pressed or not
		int _selectedOption = -1;
		bool _pressed = false;
		
		// option specs
		bool _optionShadow;
		short _opShadowColor;
		bool _fade;
		short _fadeSpeed;
		int _shadowOffsetX = 1;
		int _shadowOffsetY = 1;
		int _vSpace = 7; // space in between options
		int hitSpace = 2;
		
		// area related
		bool _areaShadow;
		short _arShadowColor;
		AreaTrans _tv;

	protected:
		virtual void drawOption(Option& op, bool selected)
		{
			if (_optionShadow)
				spDrawText(op.x + _shadowOffsetX, op.y + _shadowOffsetY, spOptions, op.text.c_str(), _font, DarkGrey);

			spDrawText(op.x, op.y, spOptions, op.text.c_str(), _font, Color(op.r, op.g, op.b));
		}

		virtual void optionHovered(Option& op)
		{
			short r, g, b;
			Xterm(Red, &r, &g, &b);

			op.r = r;
			op.g = g;
			op.b = b;
		}

		virtual void optionPressed(Option& op)
		{
			op.r = 255;
			op.g = 255;
			op.b = 255;

			_pressed = true;
		}

	public:
		Menu(Font whichFont, Space optionSpace, bool optionShadow = true, short shadowColor = DarkGrey, bool fade = true, short fadeSpeed = 800)
		{
			_font = whichFont;
			_font.spacingX = 2;

			spOptions = optionSpace;

			_optionShadow = optionShadow;
			_opShadowColor = shadowColor;
			_optionShadow = optionShadow;

			_fade = fade;
			_fadeSpeed = fadeSpeed;
		}

		void addOption(std::string text, int x, int y) // y can be default
		{
			if (x == Default || x == Centered) // calculate X here because we can, not Y, that must be done later
				x = center(txtWidth(text.c_str(), _font) + _shadowOffsetX, spOptions, X);

			_options.push_back({ text, x, y });
		}

		void addArea(Area area, int x, int y, float zoom = 1, bool shadow = false, short shadowColor = DarkGrey)
		{
			_areaShadow = shadow;
			_arShadowColor = shadowColor;

			_tv = createAT(area, x, y);
			changeZoom(&_tv, Centered, Centered, zoom, true);

		}

		void drawArea()
		{
			drawAT(_tv);
		}
		void drawOptions()
		{
			for (auto op = _options.begin(); op < _options.end(); op++)
				drawOption(*op, (op - _options.begin()) == _selectedOption);
		}
		void draw()
		{
			drawArea();
			drawOptions();
		}

		void calculations()
		{
			int i = 0, y = _tv.y + _tv.area.height * _tv.zoom + 5;
			bool leftMPressed = key(LeftM).pressed;
			bool EnterPressed = key(Enter).pressed;
			bool somethingPressed = false;

			for (Option& o : _options)
			{
				// correct Y in the case it was default
				if (o.y == Default)
					o.y = i * (txtHeight("", _font) + _vSpace + _shadowOffsetX);

				// calculate the collide space for that option
				Space textSpace = calcSpace(spOptions, o.x, o.y, txtWidth(o.text.c_str(), _font), txtHeight(o.text.c_str(), _font));

				textSpace.startX -= hitSpace;
				textSpace.startY -= hitSpace;

				textSpace.endX += _shadowOffsetX + hitSpace;
				textSpace.endY += _shadowOffsetY + hitSpace;
				
				if (leftMPressed && pointSpaceCollide(Mouse.x, Mouse.y, textSpace))
				{
					somethingPressed = true;
					optionHovered(o);

					if (_selectedOption == i)
						optionPressed(o);

					_selectedOption = i;
				}
				else if (!somethingPressed)
					_pressed = false;

				if (_selectedOption != i)
				{
					o.r += timePerSec(_fadeSpeed);
					o.g += timePerSec(_fadeSpeed);
					o.b += timePerSec(_fadeSpeed);

					o.r = clamp(o.r, 0, 255);
					o.g = clamp(o.g, 0, 255);
					o.b = clamp(o.b, 0, 255);
				}
				i++;
			}
		
			if (EnterPressed)
				optionPressed(_options[_selectedOption]);

			if ((key(W).pressed || key(Up).pressed) && _selectedOption > 0)
			{
				_selectedOption--;
				optionHovered(_options[_selectedOption]);
			}
			if ((key(S).pressed || key(Down).pressed) && (_selectedOption < _options.size() - 1 || _selectedOption == -1))
			{
				_selectedOption++;
				optionHovered(_options[_selectedOption]);
			}
		}
		
		bool pressed()
		{
			return _pressed;
		}

		void noneSelected()
		{
			_selectedOption = -1;
		}
		
		int indexPressed()
		{
			return _selectedOption;
		}
	};

	/*-------------------------------------------*\
	|			  Single State Class			  |
	\*-------------------------------------------*/

	class States;
	class State
	{
	protected:
		bool initalized;
		std::string* _thisState;
		States* _currState;

	public:
		State()
		{
			_thisState = nullptr;
			initalized = false;
			_currState = nullptr;
		}
		virtual void initalizer() = 0;
		virtual void runState() = 0;
		virtual void terminator() {};

		void setState(std::string state);

		void runInit(std::string& state, States& states)
		{
			if (!initalized)
			{
				_thisState = &state;
				_currState = &states;

				initalized = true;
				initalizer();
			}
			runState();
		}
		void reset()
		{
			initalized = false;
		}
		~State()
		{
			terminator();
		}
	};

	/*-------------------------------------------*\
	|				 States Class	    		  |
	\*-------------------------------------------*/

	class States
	{
	private:
		// vector of functions
		std::map<std::string, State*> states;
		bool _running;

	public:
		std::string currState;

		States(std::string stateName) : states()
		{
			_running = true;
			currState = stateName;
		}

		void runState()
		{
			states[currState]->runInit(currState, *this);
		}

		void setState(std::string name)
		{
			currState = name;
		}

		void addState(std::string name, State* state)
		{
			states[name] = state;
		}

		bool isRunning()
		{
			return _running;
		}

		void stopRunning()
		{
			_running = false;
		}

		States& operator=(const States& other)
		{
			currState = other.currState;
			states = other.states;
			return *this;
		}
	};


	// this has to be here, because the function definition for setState in States
	// doesnt exist yet. (writing 'class States' doesnt work here.)
	void State::setState(std::string state)
	{
		_currState->setState(state);
	}

}

#endif


#endif