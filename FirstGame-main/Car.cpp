#include "Car.h"
#include "Math.h"
#include "Game.h"
#include <iostream>


float Car::convertSpaceCoordWidth(int _Coord)
{
	if (_Coord < 0.0f)
	{
		return WINDOW_WIDTH / 2 - abs(_Coord);
	}
	else {
		return WINDOW_WIDTH / 2 + _Coord;
	}
}

float Car::convertSpaceCoordHeight(int _Coord)
{
	if (_Coord < 0.0f)
	{
		return WINDOW_HEIGHT/ 2 + abs(_Coord);
	}
	else {
		return WINDOW_HEIGHT / 2 - _Coord;
	}
}


  void Car::update (float dt) 
{
	float nextCarX = position.x + cos(rotation) * velocity * dt;
	float nextCarY = position.y + sin(rotation) * velocity * dt;
	
	int nextCX = (int)floor(nextCarX);
	int nextCY = (int)floor(nextCarY);

	std::cout << "checkForTrackAtPixelCoord(" << nextCX << "," << nextCY << ") ;" << std::endl;

	if (checkForTrackAtPixelCoord(nextCX, nextCY))
	{
		setPosition(Vector3(nextCarX, nextCarY, 0.0f));
	}
	else
	{

		setVelocity(0.0f);
	}

	computeWorldTransform();
}

void Car::driveForward()
{
	velocity += 6;

	std::cout << "Velocity : " << velocity << std::endl;
}

void Car::slowDown(float v)
{
	velocity -= v;
}

void Car::brake()
{
	if (velocity > 0) velocity = velocity * 7 / 8;
	else if (velocity > -20) velocity -= 2;
}

float Car::getVelo()
{
	return velocity;
}

void Car::turnRight()
{
	rotate(-0.1f);
}
void Car::turnLeft()
{
	rotate(0.1f);
}

void Car::setVelocity(float _v)
{
	velocity = _v;
}

int Car::trackTileToIndex(int col, int row)
{
	return (col + TRACK_COLS * row);
}

bool Car::checkForTrackAtPixelCoord(int pixelX, int pixelY) {

	float tileCol = convertSpaceCoordWidth(pixelX); tileCol -= 30.0f; 
	float tileRow = convertSpaceCoordHeight(pixelY); tileRow -= 30.0f;

	tileCol /= TRACK_W;
	tileRow /= TRACK_H;


	// we'll use Math.floor to round down to the nearest whole number
	tileCol = floor(tileCol);
	tileRow = floor(tileRow);
	// first check whether the car is within any part of the track wall
	if (tileCol < 0 || tileCol >= TRACK_COLS || tileRow < 0 || tileRow >= TRACK_ROWS) {
		return false; // bail out of function to avoid illegal array position usage
	}
	int trackIndex = trackTileToIndex((int)tileCol, (int)tileRow);	
	int val = Game::instance().trackGrid[trackIndex];
	std::cout << "track index : " << trackIndex << std::endl;
	std::cout << " val : " << val << std::endl;
	bool tamere = ( val == 0 || val == 2);
	return tamere;
}

void Car::processInput(Key _k)
{
	switch (_k)
	{
	case Z:
		driveForward();
		break;
	case Q:
		turnLeft();
		break;
	case S:
		brake();
		break;
	case D:
		turnRight();
		break;
	};
}