#include "Game.h"
#include "Timer.h"
#include <random>
#include <Math.h>

#include <iostream>
using namespace std;


bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();
	




	Track tmpB({ 0, 0 }, TRACK_W, TRACK_H);
	for (int i = 0; i < TRACK_ROWS; i++)
	{
		for (int j = 0; j < TRACK_COLS; j++)
		{
			tracks.push_back(tmpB);
			tmpB.pos.x += TRACK_W;
		}
		tmpB.pos.x = 0;
		tmpB.pos.y += TRACK_H;

	}

	for (int i = 0; i < TRACK_ROWS * TRACK_COLS; i++)
	{
		if (trackGrid[i] == 2)
		{
			tileRow = floor(i / TRACK_COLS);
			tileCol = i % TRACK_COLS;
			BEGIN_POS = {tileCol*40,tileRow*40};
			break;
		}
		
	}
	myCar = Car(BEGIN_POS, 0.0f, { 25, 13 });

	CONCRETE_TEXT = renderer.loadConcreteText();
	CAR_TEXT = renderer.loadCarText();
	TREE_TEXT = renderer.loadTreeText();

	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

int Game::trackTileToIndex(int col, int row)
{
	return (col + TRACK_COLS * row);
}

bool Game::checkForTrackAtPixelCoord(int pixelX, int pixelY) {
	float tileCol = pixelX / TRACK_W;
	float tileRow = pixelY / TRACK_H;
	// we'll use Math.floor to round down to the nearest whole number
	tileCol = floor(tileCol);
	tileRow = floor(tileRow);
	// first check whether the car is within any part of the track wall
	if (tileCol < 0 || tileCol >= TRACK_COLS ||
		tileRow < 0 || tileRow >= TRACK_ROWS) {
		return false; // bail out of function to avoid illegal array position usage
	}
	int trackIndex = trackTileToIndex(tileCol, tileRow);
	return (trackGrid[trackIndex] == 0);
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);


	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	// Car launch
	if (keyboardState[SDL_SCANCODE_UP])
	{
		myCar.driveForward();
	}else if(myCar.getVelo() > 0)
	{
		myCar.slowDown(0.5);
	}

	// Car drive
	float velo = myCar.getVelo();
	if (velo > 50) velo = 50;
	float rot = 3*velo / 50;
	if (velo < 25) rot = 0;

	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		myCar.turnLeft(rot);
	}
	if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		myCar.turnRight(rot);
	}
	
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		myCar.brake();
	}

	// Car reset
	if (keyboardState[SDL_SCANCODE_SPACE])
	{
		myCar.setP(BEGIN_POS);
		myCar.setV(0);
		myCar.setCarAng(-90);
	}
}

void Game::update(float dt)
{
	

	// Car move
	float nextCarX = myCar.getPos().x + cos(myCar.getCarAng() * M_PI / 180) * myCar.getVelo()*dt;
	float nextCarY = myCar.getPos().y + sin(myCar.getCarAng()* M_PI / 180) * myCar.getVelo()*dt;

	if (checkForTrackAtPixelCoord(nextCarX, nextCarY))
	{
		myCar.update(nextCarX, nextCarY);
	}
	else
	{
		myCar.setV(0);
	}
	// Car - rect collision
	

	// Restart automatically
	
}

void Game::render()
{
	renderer.beginDraw();

	for (int i = 0; i < TRACK_ROWS * TRACK_COLS; i++)
	{
		Rectangle rect = { tracks[i].pos.x, tracks[i].pos.y, tracks[i].width /* - TRACK_GAP */, tracks[i].height /* - TRACK_GAP */};
		if (trackGrid[i] == 0 || trackGrid[i] == 2)
		{
			renderer.drawImage(rect, CONCRETE_TEXT, 0);
		}
		else
		{
			renderer.drawImage(rect, TREE_TEXT, 0);
		}
	}
	
	myCar.draw(&renderer, CAR_TEXT);

	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		cout << "dt = " << dt << endl;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}