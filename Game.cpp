#include "Game.h"

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow()
{
	ifstream ifs("Config/window.ini");
	this->videoModes = VideoMode::getFullscreenModes();

	string title = "None";
	VideoMode window_bounds = VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = true;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();


	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if(this->fullscreen)
		this->window = new RenderWindow(window_bounds, title,Style::Fullscreen,windowSettings);
	else
		this->window = new RenderWindow(window_bounds, title,Style::Titlebar | Style::Close, windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		string key = "";
		int key_value = 0;
		
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	this->supportedKeys["Escape"] = Keyboard::Key::Escape;
	this->supportedKeys["A"] = Keyboard::Key::A;
	this->supportedKeys["D"] = Keyboard::Key::D;
	this->supportedKeys["W"] = Keyboard::Key::W;
	this->supportedKeys["S"] = Keyboard::Key::S;

	for (auto i : this->supportedKeys)
	{
		cout << i.first << " " << i.second << "\n";
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
	cout << "Ending Application!" << "\n";
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
