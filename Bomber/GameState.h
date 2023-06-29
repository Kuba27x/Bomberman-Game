#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"

class GameState : public State
{
private:

	sf::Font font;
	PauseMenu* pmenu;
	Player* player;
	Player* player2;
	std::vector<Bomb*> bombs;
	std::vector<Wall*> walls;
	std::vector<Explosion*> explosions;
	sf::Texture FloorTexture;
	sf::RectangleShape floor;
	bool spaceWasPressed = false;
	bool rightShiftWasPressed = false;

	//Functions
	void initFloor();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initObstacles();
	void initPauseMenu();
	void initPlayers();

public:

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
	void endGame();
	void addBomb(float x, float y, Player* owner);
	void addWall(float x, float y);
	std::vector<Bomb*>::iterator removeBomb(Bomb* bomb);
	void addExplosion(Explosion* explosion);
	std::vector<Explosion*>::iterator removeExplosion(Explosion* explosion);

};

#endif // !GAMESTATE_H