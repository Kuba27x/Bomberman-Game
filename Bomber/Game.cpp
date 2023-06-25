#include "stdafx.h"
#include "Game.h"

//Static functions

//Init functions

void Game::initVariables()
{
	window = NULL;
	fullscreen = false;
	dt = 0.f;

}

void Game::initWindow()
{
	//Create window (config from Config/window.txt file)
	std::ifstream fs("Config/window.txt");
	videoModes = sf::VideoMode::getFullscreenModes();
	std::string title = "BOMBERMAN";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned fps_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (fs.is_open())
	{
		std::getline(fs, title);
		fs >> window_bounds.width >> window_bounds.height;
		fs >> fullscreen;
		fs >> fps_limit;
		fs >> vertical_sync_enabled;
		fs >> antialiasing_level;
	}
	fs.close();

	this->fullscreen = fullscreen;
	window_settings.antialiasingLevel = antialiasing_level;
	if(this->fullscreen)
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen ,window_settings); 
	else
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, window_settings);

	window->setFramerateLimit(fps_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);

	sf::Image icon;
	icon.loadFromFile("Resources/Images/Game_Icon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initKeys()
{	
	supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	supportedKeys["A"] = sf::Keyboard::Key::A;
	supportedKeys["D"] = sf::Keyboard::Key::D;
	supportedKeys["W"] = sf::Keyboard::Key::W;
	supportedKeys["S"] = sf::Keyboard::Key::S;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window , &this->supportedKeys, &this->states));
}

//Con/Des 

Game::Game()
{
	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
	delete window;
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

//Functions

void Game::endApplication()
{

}

void Game::updateDT()
{	
	//Delta time (time to render one frame)
	dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update()
{
	updateSFMLEvents();

	if (!states.empty())
	{
		states.top()->update(dt);

		if (states.top()->getQuit())
		{
			states.top()->endState();
			delete states.top();
			states.pop();
		}
	}
	//App end
	else
	{
		endApplication();
		window->close();
	}

}

void Game::render()
{
	window->clear();

	//Render stuff
	if (!states.empty())
		states.top()->render();

	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDT();
		update();
		render();
	}
}



