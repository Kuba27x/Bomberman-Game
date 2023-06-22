#include "stdafx.h"
#include "GameState.h"
#include "Wall.h"

void GameState::initTextures()
{
	textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Player_Spritesheet/Player_Animation_Sheet.png");
	textures["PLAYER2_SHEET"].loadFromFile("Resources/Images/Player_Spritesheet/Player2_Animation_Sheet.png");
	textures["WALL_SHEET"].loadFromFile("Resources/Images/Player_Spritesheet/Wall.png");
}

void GameState::initPauseMenu()
{
	pmenu = new PauseMenu(*window, font);
	pmenu->addButton("QUIT", 600.f, "Quit");
}

void GameState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void GameState::initKeybinds()
{
	keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");

}

void GameState::initPlayers()
{
	player = new Player(0, 0, textures["PLAYER_SHEET"]);
	player2 = new Player(1500, 0, textures["PLAYER2_SHEET"]);
}

void GameState::initObstacles()
{
	wall1 = new Wall(500, 500, textures["WALL_SHEET"]);

	player->addCollisionObject(wall1->getHitboxComponent()->getGlobalBounds());
	player2->addCollisionObject(wall1->getHitboxComponent()->getGlobalBounds());
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
	initFonts();
	initPauseMenu();
	initPlayers();
	initObstacles();
}

GameState::~GameState()
{
	delete pmenu;
	delete player;
	delete player2;
	delete wall1;
}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyTime())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

//Functions
void GameState::updatePlayerInput(const float& dt)
{

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(0.f, 1.f, dt);
	//drugi sposob, bez uzycia mapy keybinds
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player2->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player2->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player2->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player2->move(0.f, 1.f, dt);


}

void GameState::updatePauseMenuButtons()
{
	if (pmenu->isButtonPressed("QUIT"))
		endState();
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateKeyTime(dt);
	updateInput(dt);

	if (!paused) //Unpaused update
	{
		updatePlayerInput(dt);
		player->update(dt, window->getSize().x, window->getSize().y);
		player2->update(dt, window->getSize().x, window->getSize().y);

	}
	else //Paused update
	{
		pmenu->update(mousePosView);
		updatePauseMenuButtons();

	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	player->render(*target);
	player2->render(*target);
	wall1->render(*target);

	if (paused) //Pause menu render
	{
		pmenu->render(*target);
	}
}