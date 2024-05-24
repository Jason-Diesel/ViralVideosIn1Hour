#pragma once
#include "Mode.h"



class Game : public Mode {
private:
	const float backgroundRadius;
	sf::CircleShape background;

	float bounceBallRadius;
	sf::CircleShape bounceBall;
	const float theG;
	const float timeStep;
	const float sizeChanger;
	bool start;
	float rgb[3];
	float value[3];//UGLY ASS MF SOLUTION

public:
	Game();
	virtual ~Game();
	SCENECALLBACK Update(float dt);
	void Render();
	void HandleEvents();
private:
	sf::Vector2f bounceBallVelocity;
	void bounceBallMovement(float dt);
	void collisionBounceBall();
	void changeColor(float dt);
	sf::Vector2f rotate2DVector(sf::Vector2f vec, float rotation);
	void InitNotes();
private:
	//THIS GONNA BE UGLY
#define numberOfNotes 17
	sf::SoundBuffer buffer[numberOfNotes];
	sf::Sound sound[numberOfNotes];
	int currentNote;
	std::vector<int> notes;
};