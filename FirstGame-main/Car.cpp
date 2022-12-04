#include "Car.h"
#include "Math.h"

SDL_Texture* Car::loadText(Renderer* rend)
{
	SDL_Surface* surface = SDL_LoadBMP("rsc/myCar.bmp");
	SDL_Texture* text = SDL_CreateTextureFromSurface(rend->getRenderer(), surface);
	SDL_FreeSurface(surface);

	return text;
}

void Car::draw(Renderer* rend)
{
	Rectangle srcRect = { pos.x - carSize.x/2, pos.y - carSize.y/2, carSize.x, carSize.y };
	rend->drawImage(srcRect, loadText(rend), carAng);
}

void Car::update(float nextX, float nextY)
{
	pos.x = nextX;
	pos.y = nextY;
}

void Car::driveForward()
{
	velocity += 6;
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

Vector2 Car::getPos()
{
	return pos;
}

float Car::getVelo()
{
	return velocity;
}

Vector2 Car::getCarSize()
{
	return carSize;
}

float Car::getCarAng()
{
	return carAng;
}

void Car::turnRight(float rot)
{
	carAng += rot;
}
void Car::turnLeft(float rot)
{
	carAng -= rot;
}

void Car::setV(float v)
{
	velocity = v;
}

void Car::setP(Vector2 p)
{
	pos = p;
}

void Car::setCarSize(Vector2 carS)
{
	carSize = carS;
}

void Car::setCarAng(float a)
{
	carAng = a;
}