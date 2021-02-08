#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

using namespace sf;
using namespace std;

class MovementComponent
{
private:
	Sprite& sprite;

	float maxVelocity;
	Vector2f velocity;
	Vector2f acceleration;
	Vector2f deceleration;

	//Initializer functions

public:
	MovementComponent(Sprite& sprite, float maxVelocity);
	virtual ~MovementComponent();

	//Accessors
	const Vector2f& getVelocity() const;

	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

#endif