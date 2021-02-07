#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Sarabun-Medium.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font, 
		"New Game",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 500, 150, 50, &this->font,
		"Quit",
		Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys,states)
{
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	

	this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::endState()
{
	cout << "Ending MainMenuState!" << "\n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();

	//Input
	
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
}
