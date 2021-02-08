#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
	//Variables
	Texture backgroundTexture;
	RectangleShape background;
	Font font;

	map<string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void endState();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(RenderTarget* target = NULL);
	void render(RenderTarget* target = NULL);
};

#endif