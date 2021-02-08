#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h";

class Entity
{
private:
	void initVariables();

protected:
	Texture* texture;
	Sprite sprite;
	
	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(Texture& texture);
	void createMovementComponent(const float maxVelocity);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt,const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(RenderTarget* target);
};

#endif