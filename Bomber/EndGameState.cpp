#include "stdafx.h"
#include "EndGameState.h"

void EndGameState::initVariables()
{
	modes = sf::VideoMode::getFullscreenModes();
}

void EndGameState::initKeybinds()
{

}

void EndGameState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	bgTexture.loadFromFile("Resources/Images/Bbackground.png");
	background.setTexture(&bgTexture);
}

void EndGameState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void EndGameState::initText()
{
	this->optionsText.setFont(font);
	optionsText.setPosition(sf::Vector2f(500.f, 500.f));
	optionsText.setCharacterSize(70);
	optionsText.setFillColor(sf::Color(25, 25, 25, 200));

	optionsText.setString(
		"GAME OVER!"
	);
}

EndGameState::EndGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initText();
}

EndGameState::~EndGameState()
{

}

void EndGameState::updateInput(const float& dt)
{

}

void EndGameState::update(const float& dt)
{

}

void EndGameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	target->draw(optionsText);
}
