#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void EditorState::initKeybinds()
{
	keybinds["CLOSE"] = supportedKeys->at("Escape");
}

void EditorState::initButtons()
{

}

//Con/Des
EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();

}

EditorState::~EditorState()
{
	auto i = buttons.begin();
	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}
}


//Functions
void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
		endState();
}

void EditorState::updateButtons()
{
	//Update all buttons
	for (auto& i : buttons)
	{
		i.second->update(mousePosView);
	}
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateButtons();

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : buttons)
	{
		i.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	renderButtons(*target);
}