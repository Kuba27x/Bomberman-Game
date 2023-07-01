#ifndef ENDGAMESTATE_H
#define ENDGAMESTATE_H
#include "State.h"

class EndGameState : public State
{
private:
	//Variables
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;

	sf::Text optionsText;
    std::vector<sf::VideoMode> modes;

	//Functions
	void initVariables();
	void initKeybinds();
	void initBackground();
	void initFonts();
	void initText();
public:
	EndGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EndGameState();

//Functions
void updateInput(const float& dt);
void update(const float& dt);
void render(sf::RenderTarget* target = nullptr);

};
#endif