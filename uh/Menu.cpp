#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("../Font/Roboto-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setString("Hi! Press 'A' for Bouncing balls, 'S' for Sorting and 'D' for falling sand \n Then backspace to go back to menu, (sorter is kinda bugged)");
	text.setPosition(20, 20);
}

SCENECALLBACK Menu::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		return SCENECALLBACK::BOUNCING_BALLS;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		return SCENECALLBACK::SORTER;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		return SCENECALLBACK::FALLING_SAND;
	}
	if (done)
	{
		return SCENECALLBACK::QUIT;
	}
	return SCENECALLBACK::NOTHING;
}

void Menu::Render()
{
	win.clear();

	win.draw(text);

	win.display();
}

void Menu::HandleEvents()
{
	sf::Event event;
	while (win.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			win.close();
			done = true;
		}
	}
}
