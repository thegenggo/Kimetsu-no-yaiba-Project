#ifndef  GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	RenderWindow *window;
	Event sfEvent;

	Clock dtClock;
	float dt;
	int choice;
	bool playing;

	stack<State*> states;

	map<string, int> supportedKeys;

	//Initialization
	void initWindow();
	void initKeys();
	void initStates();
public:
	Game();
	virtual ~Game();
	
	//Functions
	void mainMenu();
	void endApplication();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();

	//Accressors
	inline bool getPlaying() const { return this->playing; }
};

#endif