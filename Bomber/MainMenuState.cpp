#include "stdafx.h"
#include "MainMenuState.h"
#include "ServerConnection.h"

//Initializers
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	bgTexture.loadFromFile("Resources/Images/Bbackground.png");
	background.setTexture(&bgTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void MainMenuState::initKeybinds()
{
	keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");
}

void MainMenuState::initButtons()
{
	buttons["GAME_STATE"] = new gui::Button(500.f, 400.f, 450.f, 50.f, &this->font, "New Game", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));

	buttons["SETTINGS_STATE"] = new gui::Button(500.f, 650.f, 450.f, 50.f, &this->font, "Settings", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));

	buttons["EDITOR_STATE"] = new gui::Button(500.f, 900.f, 450.f, 50.f, &this->font, "Editor", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));

	buttons["EXIT_STATE"] = new gui::Button(500.f, 1150.f, 450.f, 50.f, &this->font, "Quit", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));
}

//Con/Des
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	auto i = buttons.begin();
	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}
}

//Functions
void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	//Update all buttons
	for (auto& i : buttons)
	{
		i.second->update(mousePosView);
	}

	// New Game
	if (buttons["GAME_STATE"]->isPressed())
	{
		// GameState on stack
		this->states->push(new GameState(this->window, this->supportedKeys, this->states)); 
	}

	//Settings
	if (buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
	}

	//Editor
	if (buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}

	//Quit Game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}

}

void MainMenuState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	renderButtons(*target);
}