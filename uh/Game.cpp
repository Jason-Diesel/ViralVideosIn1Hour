#include "Game.h"

Game::Game():
	
	backgroundRadius(windowHeight/2),
	bounceBallRadius(10.0f),
	bounceBallVelocity(0,0),
	theG(9.4),
	timeStep(0.01),
	sizeChanger(1),
	start(false),
	currentNote(0)
{	
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	value[0] = 1;
	value[1] = 0;
	value[2] = 0;

	background.setFillColor(sf::Color::White);
	background.setRadius(backgroundRadius);
	background.setPosition(windowWith / 2, windowHeight / 2);
	background.setOrigin(backgroundRadius, backgroundRadius);

	bounceBall.setFillColor(sf::Color::Red);//start
	bounceBall.setRadius(bounceBallRadius);
	bounceBall.setPosition((windowWith / 2) - 30, windowHeight / 2);
	bounceBall.setOrigin(bounceBallRadius, bounceBallRadius);

	InitNotes();
}

Game::~Game()
{
}

SCENECALLBACK Game::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		start = true;
	}
	if (start)
	{
		bounceBallMovement(dt);
		collisionBounceBall();
		changeColor(dt);
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

void Game::Render()
{
	if (!start)
	{
		win.clear(sf::Color(0, 0, 0, 1));
		win.draw(background);
	}

	win.draw(bounceBall);

	win.display();
}

void Game::HandleEvents()
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


void Game::bounceBallMovement(float dt)
{
	//add gravity (y is flipped in OpenGL or SFML? so it's a '+')
	bounceBallVelocity.y += dt * theG * timeStep;
	bounceBall.move(bounceBallVelocity);
}

void Game::collisionBounceBall()
{
	//Check if ball is outside ring
	float L = getLenght(bounceBall.getPosition(), background.getPosition());
	if (L > backgroundRadius - bounceBallRadius)
	{
		sound[notes[currentNote++]].play();
		currentNote %= notes.size();
		//Get direction of how It should bounce, normalize it
		sf::Vector2f dir = (background.getPosition() - bounceBall.getPosition());
		dir.x = dir.x / L;
		dir.y = dir.y / L;

		float randomRotation = ( -1.0f + static_cast<float>(rand()) / (static_cast<double>(RAND_MAX / 2.0f))) * 0.5;
		sf::Vector2f changedDir = rotate2DVector(dir, randomRotation);

		//Get how it fast it should bounce back
		float lenghtOfVel = getLenght(bounceBallVelocity);

		//set velocity so it bounces back
		//bounceBallVelocity.x = dir.x * lenghtOfVel;
		//bounceBallVelocity.y = dir.y * lenghtOfVel;
		bounceBallVelocity.x = changedDir.x * lenghtOfVel * 1.01;
		bounceBallVelocity.y = changedDir.y * lenghtOfVel * 1.01;

		//make the ball bigger
		bounceBallRadius += sizeChanger;
		bounceBall.setRadius(bounceBallRadius);

		//move the ball so it doesn't get stuck in endless loop
		sf::Vector2f setPos = background.getPosition() + -dir * (backgroundRadius - bounceBallRadius);
		bounceBall.setPosition(setPos);
		bounceBall.setOrigin(bounceBall.getRadius(), bounceBall.getRadius());
	}
}

void Game::changeColor(float dt)
{

	value[0] += (dt * 1);
	value[1] += (dt * 3);
	value[2] += (dt * 7);
	for (uint8_t i = 0; i < 3; i++)
	{
		rgb[i] = ((cos(value[i]) + 1)/2) * 255;
	}

	bounceBall.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
}

sf::Vector2f Game::rotate2DVector(sf::Vector2f vec, float rotation)
{
	sf::Vector2f newVec;
	newVec.x = vec.x * cos(rotation) - vec.y * sin(rotation);
	newVec.y = vec.x * sin(rotation) + vec.y * cos(rotation);
	return newVec;
}

void Game::InitNotes()
{
	std::string noteFiles[] = {
		"../Audio/Piano_Note_Bm3.wav", //1
		"../Audio/Piano_Note_B3.wav",   //2
		"../Audio/Piano_Note_C4.wav",   //3
		"../Audio/Piano_Note_Dm4.wav",  //4
		"../Audio/Piano_Note_D4.wav",   //5
		"../Audio/Piano_Note_Em4.wav",  //6
		"../Audio/Piano_Note_E4.wav",   //7
		"../Audio/Piano_Note_F4.wav",	//8
		"../Audio/Piano_Note_Gm4.wav",  //9
		"../Audio/Piano_Note_G4.wav",   //10
		"../Audio/Piano_Note_Am4.wav",  //11
		"../Audio/Piano_Note_A4.wav",   //12
		"../Audio/Piano_Note_Bm4.wav",  //13
		"../Audio/Piano_Note_B4.wav",   //14
		"../Audio/Piano_Note_C5.wav",   //15
		"../Audio/Piano_Note_Dm5.wav",  //16
		"../Audio/Piano_Note_D5.wav",   //17
	};
	for (int i = 0; i < numberOfNotes; i++)
	{
		buffer[i].loadFromFile(noteFiles[i]);
		sound[i].setBuffer(buffer[i]);
	}

	notes.push_back(4);
	notes.push_back(4);
	notes.push_back(16);
	notes.push_back(11);
	notes.push_back(10);
	notes.push_back(9);
	notes.push_back(7);
	notes.push_back(4);
	notes.push_back(7);
	notes.push_back(9);

	notes.push_back(2);
	notes.push_back(2);
	notes.push_back(16);
	notes.push_back(11);
	notes.push_back(10);
	notes.push_back(9);
	notes.push_back(7);
	notes.push_back(4);
	notes.push_back(7);
	notes.push_back(9);

	notes.push_back(1);
	notes.push_back(1);
	notes.push_back(16);
	notes.push_back(11);
	notes.push_back(10);
	notes.push_back(9);
	notes.push_back(7);
	notes.push_back(4);
	notes.push_back(7);
	notes.push_back(9);

	notes.push_back(0);
	notes.push_back(0);
	notes.push_back(16);
	notes.push_back(11);
	notes.push_back(10);
	notes.push_back(9);
	notes.push_back(7);
	notes.push_back(4);
	notes.push_back(7);
	notes.push_back(9);
}
