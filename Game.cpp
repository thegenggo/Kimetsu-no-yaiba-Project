#include "Game.h"

void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");

	std::string title = "None";
	sf::VideoMode window_bounds(1920, 1080);
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = true;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"] = sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S;

	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys , &this->states));
}

//Constructors/Destructors
Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	/*while (this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}*/
}

//Functions
void Game::mainMenu()
{

}

void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame*/

	this->dt = this->dtClock.restart().asSeconds();

	//system("cls");
	//std::cout << this->dt << "\n";
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(sfEvent))
	{

		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render item
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();

}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
