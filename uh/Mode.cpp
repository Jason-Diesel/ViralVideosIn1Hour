#include "Mode.h"

Mode::Mode():
	win(sf::VideoMode(windowWith, windowHeight), "SFML window"),
	done(false)
{
}

Mode::~Mode()
{
}

float getLenght(const sf::Vector2f& a, const sf::Vector2f& b)
{
	//a^2 + b^2 = c^2
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float getLenght(const sf::Vector2f& a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}
