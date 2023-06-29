#pragma once
#include "stdafx.h"
#include "State.h"
#include "Gui.h"

class NewGameState : public State
{
public:
	NewGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~NewGameState();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);

private:
	sf::RectangleShape background;
	sf::Texture bgTexture;
	std::map<std::string, gui::Button*> buttons;

	void initBackground();
	void initFonts();
	void initButtons();
};