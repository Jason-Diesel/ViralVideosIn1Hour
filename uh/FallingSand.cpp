#include "FallingSand.h"

FallingSand::FallingSand():
	currentUpdateTime(0),
	updateTime(UpdateTime)
{
	for (int x = 0; x < GridWidth; x++) {
		for (int y = 0; y < GridHeight; y++) {
			sandGrid[x][y] = nullptr;
		}
	}
	winSize = sf::Vector2f(win.getSize().x, win.getSize().y);
}

FallingSand::~FallingSand()
{
	for (int i = 0; i < sand.size(); i++)
	{
		delete sand[i];
	}
}

SCENECALLBACK FallingSand::Update(float dt)
{
	currentUpdateTime += dt;

	while (currentUpdateTime >= updateTime)
	{
		currentUpdateTime -= updateTime;
		FixedUpdate(updateTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		return SCENECALLBACK::MENU;
	}
	if (done)
	{
		return SCENECALLBACK::QUIT;
	}
    return SCENECALLBACK::NOTHING;
}

void FallingSand::Render()
{
	win.clear();

	for (int i = 0; i < sand.size(); i++)
	{
		win.draw(*sand[i]);
	}

	win.display();
}

void FallingSand::HandleEvents()
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

void FallingSand::FixedUpdate(float dt)
{
	//Make sand Fall
	for (int i = 0; i < sand.size(); i++)
	{
		if (sand[i]->positionInArray.y < GridHeight)
		{
			if (sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y + 1] == nullptr)//fall down
			{
				//move in grid
				sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y + 1] = sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y];
				sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y] = nullptr;
				sand[i]->positionInArray.y += 1;
			}
			else if(sandGrid[sand[i]->positionInArray.x - 1][sand[i]->positionInArray.y + 1] == nullptr)//fall left first
			{
				sandGrid[sand[i]->positionInArray.x - 1][sand[i]->positionInArray.y + 1] = sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y];
				sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y] = nullptr;
				sand[i]->positionInArray.y += 1;
				sand[i]->positionInArray.x -= 1;
			}
			else if (sandGrid[sand[i]->positionInArray.x + 1][sand[i]->positionInArray.y + 1] == nullptr)//fall right later
			{
				sandGrid[sand[i]->positionInArray.x + 1][sand[i]->positionInArray.y + 1] = sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y];
				sandGrid[sand[i]->positionInArray.x][sand[i]->positionInArray.y] = nullptr;
				sand[i]->positionInArray.y += 1;
				sand[i]->positionInArray.x += 1;
			}
			//move in rendering
			sand[i]->move(winSize);
		}
	}

	//Spawn new sand
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Get mouse pos
		sf::Vector2i mousePos = sf::Mouse::getPosition(win);

		//Get position in grid
		int xPosition = (mousePos.x / winSize.x) * GridWidth;
		int yPosition = (mousePos.y / winSize.y) * GridHeight;

		if (!(xPosition < 0 || xPosition >= GridWidth) &&
			!(yPosition < 0 || yPosition >= GridHeight) &&
			sandGrid[xPosition][yPosition] == nullptr
			)
		{
			sand.push_back(new Sand(sf::Vector2i(xPosition, yPosition), winSize));
			sandGrid[xPosition][yPosition] = sand.back();
		}
	}
}

//////SAND CLASS////////
Sand::Sand(sf::Vector2i positionInArray, sf::Vector2f winSize)
{
	this->positionInArray = positionInArray;
	shape.setFillColor(sf::Color::Yellow);
	sf::Vector2f size(winSize.x/ GridWidth, winSize.y/GridHeight);
	shape.setSize(size);
	shape.setPosition(positionInArray.x * size.x, positionInArray.y * size.y);
}

void Sand::move(sf::Vector2f size)
{
	shape.setPosition(positionInArray.x * (size.x / GridWidth), positionInArray.y * (size.y / GridWidth));
}

void Sand::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}
