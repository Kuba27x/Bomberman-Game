#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "Wall.h"
#include "Bomb.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Accessor
	const bool& getQuit() const;
	const bool getKeyTime();

	//Functions
	void endState();
	void pauseState();
	void unpauseState();
	virtual void updateMousePositions();
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

};

#endif // !STATE_H