#ifndef PREGAMESTATE_H
#define PREGAMESTATE_H

#include "State.h"
#include "Gui.h"

class PreGameState : public State
{
private:
	//Variables
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text preGameText;

	std::vector<sf::VideoMode> modes;
	//TextFields
	gui::TextField* serverAddressField;
	gui::TextField* serverPortField;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();

public:
	PreGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~PreGameState();

	//Accessors

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif