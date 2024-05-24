#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

float getLenght(const sf::Vector2f& a, const sf::Vector2f& b);
float getLenght(const sf::Vector2f& a);

enum SCENECALLBACK
{
	NOTHING,
	QUIT,
	MENU,
	BOUNCING_BALLS,
	SORTER,
	FALLING_SAND
};

class Mode
{
public:
#define windowWith 800
#define windowHeight 600
	Mode();
	virtual ~Mode();
	virtual SCENECALLBACK Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents() = 0;
protected:
	bool done;
	sf::RenderWindow win;
};