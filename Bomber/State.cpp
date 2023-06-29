#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	quit = false;
	paused = false;
	keyTime = 0.f;
	keyTimeMax = 10.f;
}

State::~State()
{

}

//Functions
void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;

}

void State::unpauseState()
{
	paused = false;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax)
		keyTime += 100.f * dt;
}

//Accessors
const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}