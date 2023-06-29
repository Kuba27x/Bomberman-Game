#include "stdafx.h"
#include "PreGameState.h"

void PreGameState::initVariables()
{
	modes = sf::VideoMode::getFullscreenModes();
}

void PreGameState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	bgTexture.loadFromFile("Resources/Images/Bbackground.png");
	background.setTexture(&bgTexture);
}

void PreGameState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void PreGameState::initKeybinds()
{
	keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");
}

void PreGameState::initGui()
{
	buttons["BACK"] = new gui::Button(600.f, 700.f, 450.f, 200.f, &this->font, "Back", 70,
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

	// Initialize text fields
	this->serverAddressField = new gui::TextField(800.f, 270.f, 300.f, 50.f, &this->font,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color::Magenta);

	this->serverPortField = new gui::TextField(800.f, 520.f, 300.f, 50.f, &this->font,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color::Magenta);

	serverAddressField->wasPressedLastFrame = false;
	serverPortField->wasPressedLastFrame = false;


}

void PreGameState::initText()
{
	this->preGameText.setFont(font);
	preGameText.setPosition(sf::Vector2f(250.f, 250.f));
	preGameText.setCharacterSize(70);
	preGameText.setFillColor(sf::Color(25, 25, 25, 200));

	preGameText.setString(
		"Adress \n\n\nPort number \n\n\n"
	);
}



PreGameState::PreGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initGui();
	initText();
}

PreGameState::~PreGameState()
{
	auto i = buttons.begin();
	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}
	delete serverAddressField;
	delete serverPortField;
}

//Accessors


//Functions
void PreGameState::updateInput(const float& dt)
{
	//Checking input for text fields
	if (serverAddressField->isActive() || serverPortField->isActive())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (serverAddressField->isActive())
				{
					if (event.text.unicode == '\b') // handle backspace explicitly
						serverAddressField->removeCharacter();
					else
						serverAddressField->addCharacter(static_cast<char>(event.text.unicode));
				}
				else if (serverPortField->isActive())
				{
					if (event.text.unicode == '\b') // handle backspace explicitly
						serverPortField->removeCharacter();
					else if (isdigit(static_cast<char>(event.text.unicode))) // only allow digits in port field
						serverPortField->addCharacter(static_cast<char>(event.text.unicode));
				}
			}
		}
	}
}



void PreGameState::updateGui(const float& dt)
{

	serverAddressField->update(mousePosView);
	serverPortField->update(mousePosView);

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

}

void PreGameState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateGui(dt);

	serverAddressField->update(mousePosView);
	serverPortField->update(mousePosView);
}

void PreGameState::renderGui(sf::RenderTarget& target)
{
	serverAddressField->render(target);
	serverPortField->render(target);

	for (auto& i : buttons)
	{
		i.second->render(target);
	}

}

void PreGameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	renderGui(*target);
	target->draw(preGameText);

	serverAddressField->render(*target);
	serverPortField->render(*target);
}