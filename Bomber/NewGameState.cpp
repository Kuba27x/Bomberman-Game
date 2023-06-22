#include "stdafx.h"
#include "NewGameState.h"
#include "GameState.h"

NewGameState::NewGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initBackground();
	initFonts();
	initButtons();
}

NewGameState::~NewGameState()
{
	for (auto& button : buttons)
	{
		delete button.second;
	}
}

void NewGameState::updateInput(const float& dt)
{
	
}

void NewGameState::updateButtons()
{
	for (auto& button : buttons)
	{
		button.second->update(mousePosView);
	}

	if (buttons["START_GAME"]->isPressed())
	{
		states->push(new GameState(window, supportedKeys, states));
	}

	if (buttons["BACK"]->isPressed())
	{
		endState();
	}
}

void NewGameState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void NewGameState::renderButtons(sf::RenderTarget& target)
{
	for (auto& button : buttons)
	{
		button.second->render(target);
	}
}

void NewGameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	renderButtons(*target);
}

void NewGameState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	bgTexture.loadFromFile("Resources/Images/Background.png");
	background.setTexture(&bgTexture);
}

void NewGameState::initFonts()
{
	
}

void NewGameState::initButtons()
{
	buttons["START_GAME"] = new gui::Button(500.f, 400.f, 450.f, 50.f, nullptr, "Start Game", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));

	buttons["BACK"] = new gui::Button(500.f, 650.f, 450.f, 50.f, nullptr, "Back", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));
}