#pragma once
#include "Mode.h"

#define GridWidth 200
#define GridHeight 200

class Sand : public sf::Drawable
{
public:
	Sand(sf::Vector2i positionInArray, sf::Vector2f winSize);
	void move(sf::Vector2f size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2i positionInArray;//bcs I am lazy
private:
	sf::RectangleShape shape;
};

class FallingSand : public Mode
{
public:
	FallingSand();
	~FallingSand();
	SCENECALLBACK Update(float dt);
	void Render();
	void HandleEvents();
private:
#define UpdateTime 0.01

	Sand* sandGrid[GridWidth][GridHeight];
	std::vector<Sand*> sand;

	sf::Vector2f winSize;

	void FixedUpdate(float dt);
	float currentUpdateTime;
	const float updateTime;//like 16ms
};