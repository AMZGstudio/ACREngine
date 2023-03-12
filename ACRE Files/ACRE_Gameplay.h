#pragma once

/*
How to use this Extension:





*/

/*
Changelog:
	Updated renderer

*/
#ifdef ACRE_31_COMPATIBLE

#ifdef ACRE_EX_TRANSFORM
	#define ACRE_EX_GAMEPLAY
	
	#include <vector> 
	#include <string>
	#include <map>

namespace acre // delcarations
{
	void sysDrawShadowedText(int x, int y, Area area, std::string txt, Font font, short front_color, short back_color);
	void drawShadowedText(int x, int y, std::string txt, Font font, short front_color, short back_color);
	
	class Renderer
	{
	private:
		Area _window;
		AreaTrans _windowAT;

		float fadeProgress = 0;
		float timeFromLastShake = 0;
		
		int amntShakes = 0;
		float timeForShake = 10;
		int shakeState = 0;

		enum fadeState { Neither, startedFadeIn, finished, startedFadeOut };
		fadeState fs = Neither;

	public:

		// you are allowed to change this
		float fadeIncrement = 2;

		static bool doShake;

		Renderer();
		~Renderer();
		
		void render();
		void reset();

		// checkers
		bool isFadingIn();
		bool finishedFade();
		bool notFading();

		// setters
		void startFadeIn();
		void startFadeOut();

		// getters
		Area getWindow();
	};

	class Fade
	{
	private:
		Renderer* r;
		bool thisCalledFade;

	public:
		Fade(Renderer* rendererPointer);
		void fadeOutIfNecessary();
		bool fadeInFinished();
		bool notFading();

		void fadeIn();
	};

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
		// options and options space + font
		std::vector<Option> _options;
		//Space _spOptions;
		Font _font;

		// selected option and pressed or not
		int _highlighted = -1;
		int _indexPressed = -1;

		// option specs
		bool _optionShadow;
		short _opShadowColor;
		
		bool _fade;
		short _fadeSpeed;

		AreaTrans _tv;
		bool hasTV;

		// internal
		bool _usingKeyboard = false;

	protected:
		virtual void drawOption(Option& op, Space _spOptions, const bool hovered);
		virtual void optionHovered(Option& op);
		virtual void optionPressed(Option& op);

	private:
		void keyboardCalculations();

	public:
		const int _shadowOffsetX = 1;
		const int _shadowOffsetY = 1;
		const int _vSpace = 7;   // space in between options (vertical space)
		const int _hitSpace = 2; // how much bigger text bounding box is

		Menu(Font optionFont, int normalR, int normalG, int normalB, int hoveredR, int hoveredG, int hoveredB, bool optionShadow = true, short shadowColor = DarkGrey, bool fade = true, short fadeSpeed = 800);

		// When creating an option, if you specify the x as Default, it will become Centered.
		// if you specify y as Default, it will add the y to be the next layer down.
		void addOption(std::string text); // y can be default
		void setArea(Area area, int x, int y, float zoom = 1);

		void drawArea();
		void drawOptions(Space optionSpace);
		void draw(Space optionSpace);

		void calculations(Space optionSpace);

		void deselectOptions();
		bool pressed() const;
		int indexPressed();

		AreaTrans& getAT();
	};


	// this has to be here, because the function definition for setState in States
	// doesnt exist yet. (writing 'class States' doesnt work here.)
	class States;

	class State
	{
	protected:
		bool initalized;
		std::string* _thisState;
		States* _currState;

	public:
		State();
		virtual void initalizer() = 0;
		virtual void runState() = 0;
		virtual void terminator() {};

		void setState(std::string state);

		void runInit(std::string& state, States& states);
		void reset();

		~State();
	};

	class States
	{
	private:
		// vector of functions
		std::map<std::string, State*> states;
		bool _running;

	public:
		std::string currState;

		States(std::string stateName);
		~States();

		void runState();
		void setState(std::string name);
		void addState(std::string name, State* state);

		bool isRunning();
		void stopRunning();

		States& operator=(const States& other);
	};
}

#ifdef ACRE_GAMEPLAY
#undef ACRE_GAMEPLAY

namespace acre // definitions
{
	void sysDrawShadowedText(int x, int y, Area area, std::string txt, Font font, short front_color, short back_color)
	{
		const char* ctxt = txt.c_str();
		if (x == Centered) x = Width(area) / 2 - txtWidth(ctxt, font) / 2;
		if (y == Centered) y = Height(area) / 2 - txtHeight(ctxt, font) / 2;

		sysDrawText(x + 1, y + 1, area, ctxt, font, Default, back_color);
		sysDrawText(x, y, area, ctxt, font, Default, front_color);
	}
	
	void drawShadowedText(int x, int y, std::string txt, Font font, short front_color, short back_color)
	{
		sysDrawShadowedText(x, y, *areaToDrawOn, txt, font, front_color, back_color);
	}

	/*-------------------------------------------*\
	|				 Renderer Class	    		  |
	\*-------------------------------------------*/

	inline Renderer::Renderer()
	{
		_window = createArea(Width(Screen), Height(Screen), Default, Default);
		_windowAT = createAT(&_window, 0, 0);
		setDefaultDrawArea(&_window);
	}

	Renderer::~Renderer()
	{
		deleteArea(&_window);
		setDefaultDrawArea(&Screen);
	}

	inline void Renderer::render()
	{
		if (wasResized())
		{
			resizeArea(Screen.width, Screen.height, &_window);
		}
		 
		if (fs == finished)
			sysDrawRect(0, 0, Screen.width, Screen.height, Screen, true, Default, Default, Black);

		else if (fs == Neither)
			sysDrawArea(0, 0, Screen, _window);

		else // its either fading in, or fading out
		{
			sysDrawAT(&_windowAT, Screen);
			
			fadeProgress += amntPerSec(fadeIncrement);
			if (fs == startedFadeIn) _windowAT.opacity =1-fadeProgress;
			if (fs == startedFadeOut) _windowAT.opacity = fadeProgress;

			if (fadeProgress > 1)
			{
				fadeProgress = 0;
				if (fs == startedFadeIn) fs = finished;
				if (fs == startedFadeOut) fs = Neither;
			}
		}

		::render(false);
		::reset(Screen);
		reset();
	}

	inline void Renderer::reset()
	{
		::reset(_window);
	}

	inline bool Renderer::isFadingIn()
	{
		return fs == startedFadeIn;
	}

	inline bool Renderer::finishedFade()
	{
		return fs == finished;
	}

	inline bool Renderer::notFading()
	{
		return fs == Neither;
	}

	inline void Renderer::startFadeIn()
	{
		fs = startedFadeIn;
	}

	void Renderer::startFadeOut()
	{
		fs = startedFadeOut;
	}

	inline Area Renderer::getWindow()
	{
		return _window;
	}

	// static members
	bool Renderer::doShake = false;
	
	/*-------------------------------------------*\
	|			  Fade Manager Class	   		  |
	\*-------------------------------------------*/

	Fade::Fade(Renderer* rendererPointer)
	{
		r = rendererPointer;
		thisCalledFade = false;
	}

	inline void Fade::fadeOutIfNecessary()
	{
		if (!thisCalledFade && r->finishedFade())
			r->startFadeOut();
	}

	inline bool Fade::fadeInFinished()
	{
		if (r->finishedFade() && thisCalledFade)
		{
			thisCalledFade = false;
			return true;
		}
		return false;
	}

	inline bool Fade::notFading()
	{
		return r->notFading();
	}

	inline void Fade::fadeIn()
	{
		if (notFading())
		{
			thisCalledFade = true;
			r->startFadeIn();
		}
	}
	
	/*-------------------------------------------*\
	|				   Menu Class	    		  |
	\*-------------------------------------------*/

	void Menu::drawOption(Option& op, Space _spOptions, const bool hovered)
	{
		if (_optionShadow)
			spDrawText(op.x + _shadowOffsetX, op.y + _shadowOffsetY, _spOptions, op.text.c_str(), _font, DarkGrey);

		spDrawText(op.x, op.y, _spOptions, op.text.c_str(), _font, calcColor(op.r, op.g, op.b));
	}

	inline void Menu::optionHovered(Option& op)
	{
		Color r, g, b;
		calcXterm(Red, &r, &g, &b);

		op.r = r;
		op.g = g;
		op.b = b;
	}

	inline void Menu::optionPressed(Option& op)
	{
		op.r = 255;
		op.g = 255;
		op.b = 255;

		_indexPressed = _highlighted;
	}

	inline Menu::Menu(Font optionFont, int normalR, int normalG, int normalB, int hoveredR, int hoveredG, int hoveredB, bool optionShadow, short shadowColor, bool fade, short fadeSpeed)
	{
		_font = optionFont;
		_font.spacingX = 2;

		_optionShadow = optionShadow;
		_opShadowColor = shadowColor;
		_optionShadow = optionShadow;

		hasTV = false;
		_tv = {0};
		_fade = fade;
		_fadeSpeed = fadeSpeed;
	}

	inline void Menu::addOption(std::string text)
	{
		_options.push_back({ text, 0,0 });
	}

	inline void Menu::setArea(Area area, int x, int y, float zoom)
	{
		hasTV = true;
		_tv = createAT(&area, x, y);
		setPivotAT(&_tv, Centered, Centered, false);
		setZoomAT(&_tv, zoom);
	}

	inline void Menu::drawArea()
	{
		if (hasTV)
			drawAT(&_tv);
	}

	inline void Menu::drawOptions(Space optionSpace)
	{
		for (auto op = _options.begin(); op < _options.end(); op++)
			drawOption(*op, optionSpace, (op - _options.begin()) == _highlighted);
	}

	inline void Menu::draw(Space optionSpace)
	{
		drawArea();
		drawOptions(optionSpace);
	}

	inline void Menu::keyboardCalculations()
	{
		if (key(Enter).pressed && _highlighted >= 0 && _highlighted <= _options.size() - 1)
			optionPressed(_options[_highlighted]);

		if ((key(W).pressed || key(Up).pressed))
		{
			_usingKeyboard = true;
			_highlighted--;

			if (_highlighted < 0)
				_highlighted = _options.size() - 1;

			optionHovered(_options[_highlighted]);
		}
		if ((key(S).pressed || key(Down).pressed))
		{
			_usingKeyboard = true;
			_highlighted++;

			if (_highlighted > _options.size() - 1)
				_highlighted = 0;

			optionHovered(_options[_highlighted]);
		}
	}

	inline void Menu::calculations(Space optionSpace)
	{
		int i = 0, y = _tv.y + _tv.area->height * _tv.zoom + 5;
		bool LMBPressed = key(LMB).pressed;

		for (Option& o : _options)
		{
			// correct Y in the case it was default
			o.y = i * (txtHeight("", _font) + _vSpace + _shadowOffsetX);
			o.x = Center(txtWidth(o.text.c_str(), _font) + _shadowOffsetX, spWidth(optionSpace));

			// calculate the collide space for that option
			Space textSpace = calcSpace(optionSpace, o.x, o.y, txtWidth(o.text.c_str(), _font), txtHeight(o.text.c_str(), _font));

			// adjust colision space by making bounding box bigger
			textSpace.xStart -= _hitSpace;
			textSpace.yStart -= _hitSpace;

			textSpace.xEnd += _shadowOffsetX + _hitSpace;
			textSpace.yEnd += _shadowOffsetY + _hitSpace;

			if (!_usingKeyboard)
				deselectOptions();

			if (pointSpaceOverlap(Mouse.x, Mouse.y, textSpace))
			{
				_usingKeyboard = false;
				_highlighted = i;
				optionHovered(o);

				if (LMBPressed)
					optionPressed(o);
			}

			if (_highlighted != i)
			{
				o.r += amntPerSec(_fadeSpeed);
				o.g += amntPerSec(_fadeSpeed);
				o.b += amntPerSec(_fadeSpeed);

				o.r = clampFloat(o.r, 0, 255);
				o.g = clampFloat(o.g, 0, 255);
				o.b = clampFloat(o.b, 0, 255);
			}
			i++;
		}

		keyboardCalculations();
	}

	inline void Menu::deselectOptions()
	{
		_highlighted = -1;
	}

	inline bool Menu::pressed() const
	{
		return _indexPressed != -1;
	}

	inline int Menu::indexPressed()
	{
		int val = _indexPressed;
		if (_indexPressed != -1)
			_indexPressed = -1;

		return val;
	}

	inline AreaTrans& Menu::getAT()
	{
		return _tv;
	}
	
	/*-------------------------------------------*\
	|			  Single State Class			  |
	\*-------------------------------------------*/

	State::State()
	{
		_thisState = nullptr;
		initalized = false;
		_currState = nullptr;
	}

	void State::setState(std::string state)
	{
		_currState->setState(state);
	}

	void State::runInit(std::string& state, States& states)
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
	inline void State::reset()
	{
		initalized = false;
	}
	inline State::~State()
	{
		terminator();
	}
	/*-------------------------------------------*\
	|				 States Class	    		  |
	\*-------------------------------------------*/

	States::States(std::string stateName) : states()
	{
		_running = true;
		currState = stateName;
	}

	States::~States()
	{
		for (auto& a : states)
			delete a.second;
	}

	void States::runState()
	{
		states[currState]->runInit(currState, *this);
	}

	void States::setState(std::string name)
	{
		currState = name;
	}

	void States::addState(std::string name, State* state)
	{
		states[name] = state;
	}
	
	bool States::isRunning()
	{
		return _running;
	}

	void States::stopRunning()
	{
		_running = false;
	}

	States& States::operator=(const States& other)
	{
		currState = other.currState;
		states = other.states;
		return *this;
	}

	class Interval
	{
		float time;
		float maxTime;
		float minTime;
		float waitTime;

		bool onlyOneTime;
		bool _timePassed;
		
		bool paused;
	public:
		Interval(int shortest, int longest, int startTime)
		{
			paused = false;
			minTime = shortest;
			maxTime = longest;
			onlyOneTime = false;
			time = startTime;
			_timePassed = false;
			calculateWait();
		}

		Interval(int wait, int startTime)
		{
			paused = false;
			minTime = 0;
			maxTime = wait;
			onlyOneTime = true;
			time = startTime;
			_timePassed = false;
			calculateWait();
		}

		bool getPaused()
		{
			return paused;
		}
		void resetTime()
		{
			time = 0;
		}
		void wait(float shortest, float longest)
		{
			time = 0;
			minTime = shortest;
			maxTime = longest;
			onlyOneTime = false;
			calculateWait();
		}

		void wait(float time)
		{
			time = 0;
			maxTime = time;
			onlyOneTime = true;
			calculateWait();
		}

		void calculateWait()
		{
			if (onlyOneTime)
				waitTime = maxTime;
			else
				waitTime = Random(minTime, maxTime);
		}

		bool calculate()
		{
			if (paused)
				return false;
			
			time += amntPerSec(1);

			if (time >= waitTime)
			{
				time = 0;
				_timePassed = true;
				return true;
			}
			return false;
		}

		bool timePassed()
		{
			if (_timePassed)
			{
				_timePassed = false;
				time = 0;
				calculateWait();
				return true;
			}
			return false;
		}

		bool dumbTimePassed()
		{
			return time > waitTime;
		}

		void pause()
		{
			paused = true;
		}
		void resume()
		{
			paused = false;
		}
		float getTime()
		{
			return time;
		}
	};
}

#endif

#else
#error You need to include ACRE_Transform.h before including ACRE_Gameplay.h!
#endif

#else
#error You need to use ACRE 3.1 and include it before!
#endif