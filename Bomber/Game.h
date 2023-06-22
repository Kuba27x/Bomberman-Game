#ifndef GAME_H
#define GAME_H
#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings window_settings;

	sf::Font font;
	sf::Text playerText;
	sf::Text playerText2;

	//PlayerGUI
	sf::RectangleShape playerHPbar;
	sf::RectangleShape playerHPbarBack;

	sf::RectangleShape playerHPbar2;
	sf::RectangleShape playerHPbarBack2;

	//World
	sf::Texture WorldBackgroundTexture;
	sf::Sprite WorldBackground;

	bool fullscreen;

	sf::Clock dtClock; 
	float dt;

	std::stack<State*> states; 

	std::map<std::string, int> supportedKeys;

	//Init
	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();
	void initGUI();

public:
	//Con/Des
	Game();
	virtual ~Game();

	//Functions 

	void endApplication();
	//Update
	void updateDT();
	void updateSFMLEvents(); 
	void update();
	void updateGUI();

	//Render
	void render();

	//Main
	void run();
};

#endif // !GAME_H

