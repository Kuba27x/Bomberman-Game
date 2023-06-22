#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "Wall.h"

class GameState : public State
{
private:

	sf::Font font;
	PauseMenu* pmenu;
	Wall* wall1;
	Player* player;
	Player* player2;

	//Functions
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initObstacles();
public:

	

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !GAMESTATE_H