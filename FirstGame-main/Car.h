#pragma once
#include "Actor.h"
#include "RendererOGL.h"

enum Key {
	Z,
	Q,
	S,
	D,
};

class Car : public Actor
{
public:
	Car(Vector2 scale, float v) : velocity(v), Actor(scale) {};
	Car() : velocity(0), Actor() {};
	Car(const Car&) = delete;
	Car& operator=(const Car&) = delete;
	~Car() {};

	void update(float dt) ;

	void driveForward();

	void slowDown(float v);

	void brake();

	float getVelo();

	void turnRight();

	void turnLeft();

	void setVelocity(float _v);

	void processInput(Key _k);

	int trackTileToIndex(int col, int row);

	bool checkForTrackAtPixelCoord(int pixelX, int pixelY);

	float convertSpaceCoordWidth(int _Coord);

	float convertSpaceCoordHeight(int _Coord);

	// Car Carac :
	const float V_MAX = 50.0f;

private:
	float velocity;
};