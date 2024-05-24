#pragma once
#include "Mode.h"

class Menu : public Mode
{
public:
	Menu();
	SCENECALLBACK Update(float dt);
	void Render();
	void HandleEvents();
private:
	sf::Text text;
	sf::Font font;
};