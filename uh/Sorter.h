#pragma once
#include "Mode.h"
#include <cstdlib> 

class Sorter : public Mode
{
public:
	Sorter();
	~Sorter();
	SCENECALLBACK Update(float dt);
	void Render();
	void HandleEvents();
private:
	const int nrOfNumbers;
	const int maxNumber;
	const int maxHeight;
	const int totalMaxWidth;
	const float maxPitch;

	float PitchProcent;
	sf::SoundBuffer sBuffer;
	sf::Sound sound;

	struct Bar{
		int nr;
		sf::RectangleShape rectangle;
	};
	std::vector<Bar> Bars;

	//QUICK SORT
private:
	void swap(const int &a, const int &b);
	int partition(int low, int high);
	void quickSort(int low, int high);
};