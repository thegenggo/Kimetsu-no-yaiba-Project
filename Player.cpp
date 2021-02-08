#include "Player.h"

//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	this->createMovementComponent(200.f);
}

//Constructors / Destructors
Player::Player(float x, float y, Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}
