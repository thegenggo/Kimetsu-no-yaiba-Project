#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"

using namespace sf;
using namespace std;

enum button_states {BTN_ACTIVE = 0,BTN_HOVER , BTN_IDLE};

class Button
{
private:
	short unsigned buttonState;

	bool pressed;
	bool hover;

	RectangleShape shape;
	Font* font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

public:
	Button(float x, float y,float width,float height,Font* font, string text, Color idleColor, Color hoverColor, Color activeColor);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const Vector2f mousePos);
	void render(RenderTarget* target);
};

#endif