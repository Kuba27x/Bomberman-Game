#include "stdafx.h"
#include "GameState.h"

void GameState::initTextures()
{
	textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Player_Spritesheet/Player_Animation_Sheet.png");
	textures["PLAYER2_SHEET"].loadFromFile("Resources/Images/Player_Spritesheet/Player2_Animation_Sheet.png");
	textures["WALL_SHEET"].loadFromFile("Resources/Images/Wall.png");
	textures["BOMB_SHEET"].loadFromFile("Resources/Images/Bomb-export.png");
	textures["EXPLOSION_SHEET_VERTICAL"].loadFromFile("Resources/Images/Explosion_Vertical-export.png");
	textures["EXPLOSION_SHEET_HORIZONTAL"].loadFromFile("Resources/Images/Explosion_Horizontal-export.png");
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

void GameState::initFloor()
{
	floor.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	FloorTexture.loadFromFile("Resources/Images/Floor.png");
	floor.setTexture(&FloorTexture);
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
	player = new Player(300, 300, textures["PLAYER_SHEET"]);
	player2 = new Player(1555, 135, textures["PLAYER2_SHEET"]);
}

void GameState::addWall(float x, float y)
{
	Wall* new_wall = new Wall(x, y, textures["WALL_SHEET"]);
	player->addCollisionObject(new_wall->getHitboxComponent()->getGlobalBounds(), new_wall);
	player2->addCollisionObject(new_wall->getHitboxComponent()->getGlobalBounds(), new_wall);
	walls.push_back(new_wall);
}

void GameState::initObstacles()
{
	std::ifstream file("Resources/map.txt");
	if (!file) {
		std::cout << "COULD NOT OPEN FILE!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line, '.')) 
	{
		std::istringstream iss(line);
		float x, y;
		char comma;
		if (!(iss >> x >> comma >> y)) {
			std::cout << "DATA ERROR!" << std::endl;
			continue;
		}

		addWall(x, y);
	}

	file.close();

}


void GameState::addBomb(float x, float y, Player* owner)
{
	Bomb* new_bomb = new Bomb(x, y, 130, 130, textures["BOMB_SHEET"], owner);
	bombs.push_back(new_bomb);
	owner->avaibleBombs -= 1;
}

std::vector<Bomb*>::iterator GameState::removeBomb(Bomb* bomb)
{
	auto it = std::find(bombs.begin(), bombs.end(), bomb);
	if (it != bombs.end())
	{

		Explosion* new_explosion1 = new Explosion(bomb->sprite.getPosition().x + -65, bomb->sprite.getPosition().y + 32, 260, 65, textures["EXPLOSION_SHEET_VERTICAL"], bomb->bombOwner, 200, 1);
		Explosion* new_explosion2 = new Explosion(bomb->sprite.getPosition().x + 32, bomb->sprite.getPosition().y - 65, 65, 260, textures["EXPLOSION_SHEET_HORIZONTAL"], bomb->bombOwner, 200, 2);
		addExplosion(new_explosion1);
		addExplosion(new_explosion2);

		player->removeCollisionObject(bomb);
		player2->removeCollisionObject(bomb);
		delete bomb;
		it = bombs.erase(it);
	}
	return it;
}

void GameState::addExplosion(Explosion* explosion)
{
	explosions.push_back(explosion);
	player->addCollisionObject(explosion->getHitboxComponent()->getGlobalBounds(), explosion);
	player2->addCollisionObject(explosion->getHitboxComponent()->getGlobalBounds(), explosion);
}

std::vector<Explosion*>::iterator GameState::removeExplosion(Explosion* explosion)
{
	auto it = std::find(explosions.begin(), explosions.end(), explosion);
	if (it != explosions.end())
	{
		player->removeCollisionObject(explosion);
		player2->removeCollisionObject(explosion);
		delete explosion;
		it = explosions.erase(it);
	}
	return it;
}



GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initFloor();
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
	for (Bomb* bomb : bombs)
	{
		delete bomb;
	}
	for (Wall* wall : walls)
	{
		delete wall;
	}
	for (Explosion* explosion : explosions)
	{
		delete explosion;
	}
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

	bool spaceIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (spaceIsPressed && !spaceWasPressed && player->avaibleBombs > 0) 
	{
		float bombX = player->sprite.getPosition().x;
		float bombY = player->sprite.getPosition().y + 40;
		addBomb(bombX, bombY, player);
	}
	spaceWasPressed = spaceIsPressed;

	//Without keybinds for second player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player2->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player2->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player2->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player2->move(0.f, 1.f, dt);

	bool rightShiftIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	if (rightShiftIsPressed && !rightShiftWasPressed && player2->avaibleBombs > 0) 
	{
		float bombX = player2->sprite.getPosition().x;
		float bombY = player2->sprite.getPosition().y + 40;
		addBomb(bombX, bombY, player2);
	}
	spaceWasPressed = spaceIsPressed;

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

		for (auto it = explosions.begin(); it != explosions.end();)
		{
			(*it)->update(dt, window->getSize().x, window->getSize().y);
			if ((*it)->lifeTime <= 0)
			{
				it = removeExplosion(*it);
			}
			else
			{
				++it;
			}
		}

		for (auto it = bombs.begin(); it != bombs.end();)
		{
			(*it)->update(dt, window->getSize().x, window->getSize().y);
			if ((*it)->freePass <= 0)
			{
				player->addCollisionObject((*it)->getHitboxComponent()->getGlobalBounds(), *it);
				player2->addCollisionObject((*it)->getHitboxComponent()->getGlobalBounds(), *it);
			}
			if ((*it)->lifeTime <= 0)
			{
				it = removeBomb(*it);
			}
			else
			{
				++it;
			}
		}

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

	target->draw(floor);
	player->render(*target);
	player2->render(*target);
	for (auto it = bombs.begin(); it != bombs.end(); ++it)
	{
		(*it)->render(*target);
	}
	for (auto it = walls.begin(); it != walls.end(); ++it)
	{
		(*it)->render(*target);
	}
	for (auto it = explosions.begin(); it != explosions.end(); ++it)
	{
		(*it)->render(*target);
	}

	if (paused)
	{
		pmenu->render(*target);
	}
}

void GameState::endGame()
{
	delete player;
	delete player2;
	for (Bomb* bomb : bombs)
	{
		delete bomb;
	}
	for (Wall* wall : walls)
	{
		delete wall;
	}
	std::exit(0);
}