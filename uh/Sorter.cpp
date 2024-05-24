#include "Sorter.h"
#include <windows.h>

Sorter::Sorter() :
	nrOfNumbers(200),
	maxNumber(windowHeight),
	maxHeight(windowHeight),
	totalMaxWidth(windowWith),
	maxPitch(3)
{
	srand(time(NULL));
	Bars.resize(nrOfNumbers);
	float xSize = (float)totalMaxWidth/ (float)nrOfNumbers;
	float p = maxHeight / maxNumber;
	const sf::Vector2f startPosition(0, windowHeight);
	for (int i = 0; i < nrOfNumbers; i++)
	{
		Bars[i].nr = rand()% maxNumber;
		Bars[i].rectangle.setSize(sf::Vector2f(xSize, Bars[i].nr * p));
		Bars[i].rectangle.setPosition(startPosition + sf::Vector2f(i * (xSize), 0));
		Bars[i].rectangle.setFillColor(sf::Color::White);
		Bars[i].rectangle.setOrigin(sf::Vector2f(0, Bars[i].nr * p));//left down corner right?
	}
	sBuffer.loadFromFile("../Audio/Piano_Note_C4.wav");
	sound.setBuffer(sBuffer);
	sound.setVolume(20);
	PitchProcent = 3.f / maxNumber;
}

Sorter::~Sorter()
{
}

SCENECALLBACK Sorter::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		quickSort(0, Bars.size() - 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 1; i < Bars.size(); i++)
		{
			if (Bars[i].nr < Bars[i - 1].nr)
			{
				std::cout << "error not correct" << std::endl;
			}
		}
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

void Sorter::Render()
{
	win.clear();

	for (int i = 0; i < nrOfNumbers; i++)
	{
		win.draw(Bars[i].rectangle);
	}

	win.display();
}

void Sorter::HandleEvents()
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

//QUICK SORT// Geeks for geeks btw
//swap also show a frame
void Sorter::swap(const int& a, const int& b)
{
	//feel sad IDK if pointers would be a pain in the ass
	Bar tempPointer = Bars[a];
	Bars[a] = Bars[b];
	Bars[b] = tempPointer;

	sf::Vector2f tempPosition = Bars[a].rectangle.getPosition();
	Bars[a].rectangle.setPosition(Bars[b].rectangle.getPosition());
	Bars[b].rectangle.setPosition(tempPosition);
	
	sound.setPitch(1 + Bars[a].nr * PitchProcent);
	sound.play();

	Render();
	Sleep(1);
}

int Sorter::partition(int low, int high)
{
	int pivot = Bars[high].nr;
	int i = low - 1;//should this be +1 of just low?

	for (int j = low; j <= high; j++)
	{
		if (Bars[j].nr < pivot)
		{
			i++;
			swap(i, j);
		}
	}
	swap(i + 1, high);
	return (i+1);
}

void Sorter::quickSort(int low, int high)
{
	if (low < high)
	{
		int pi = partition(low, high);

		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}



