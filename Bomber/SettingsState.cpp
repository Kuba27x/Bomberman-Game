#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	bgTexture.loadFromFile("Resources/Images/Bbackground.png");
	background.setTexture(&bgTexture);
}

void SettingsState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void SettingsState::initKeybinds()
{
	keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");
}

void SettingsState::initGui()
{
	buttons["BACK"] = new gui::Button(1000.f, 1000.f, 450.f, 200.f, &this->font, "Back", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));

	buttons["APPLY"] = new gui::Button(1000.f, 700.f, 450.f, 200.f, &this->font, "Apply", 70,
		sf::Color(80, 80, 80, 210), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 0), sf::Color(160, 160, 160, 0), sf::Color(25, 25, 25, 0));

	std::vector<std::string> modes_str;
	for (auto& i : modes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}
	dropDownLists["RESOLUTION"] = new gui::DropDownList(700, 440, 350, 100, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(font);
	optionsText.setPosition(sf::Vector2f(250.f, 450.f));
	optionsText.setCharacterSize(70);
	optionsText.setFillColor(sf::Color(25, 25, 25, 200));

	optionsText.setString(
		"Resolution \n\n\nFullscreen \n\n\nVsync \n\n\nAntialiasing \n\n\n"
	);
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initGui();
	initText();
}

SettingsState::~SettingsState()
{
	auto i = buttons.begin();
	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}

	auto i2 = dropDownLists.begin();
	for (i2 = dropDownLists.begin(); i2 != dropDownLists.end(); ++i2)
	{
		delete i2->second;
	}

}

//Accessors


//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	//Update all buttons and gui 
	for (auto& i : buttons)
	{
		i.second->update(mousePosView);
	}

	//Quit Game
	if (buttons["BACK"]->isPressed())
	{
		endState();
	}

	//Apply settings
	if (buttons["APPLY"]->isPressed())
	{
		window->create(modes[dropDownLists["RESOLUTION"]->getActiveElementId()], "test", sf::Style::Default);
	}

	for (auto& i : dropDownLists)
	{
		i.second->update(mousePosView, dt);
	}
}

void SettingsState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& i : buttons)
	{
		i.second->render(target);
	}

	for (auto& i : dropDownLists)
	{
		i.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	renderGui(*target);
	target->draw(optionsText);
}