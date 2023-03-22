#pragma once
#include "Vector2.h"
#include "RendererSDL.h"
#include "Rectangle.h"
#include "Matrix4.h"


class Car
{
public:
	Car(Vector2 p, float v, Vector2 carS) : pos(p), velocity(v), carSize(carS), carAng(-90){}
	Car() : pos({ 60,300 }), velocity(0), carSize({ 0,0}), carAng(-90){}
	~Car() {}

	void draw(RendererSDL* rend, SDL_Texture* myText);

	void update(float nextX, float nextY);

	void driveForward();

	void slowDown(float v);

	void brake();

	Vector2 getPos();
	
	float getVelo();

	Vector2 getCarSize();

	float getCarAng();

	void turnRight(float rot);

	void turnLeft(float rot);
	
	void setV(float v);
	
	void setP(Vector2 p);

	void setCarAng(float a);
	
	void setCarSize(Vector2 carS);

	void computeWorldTransform(); //Voir Page 17/54 

	const Matrix4& getWorldTransform() const { return worldTransform; }
	

private:

	Vector2 pos;
	float velocity;
	Vector2 carSize;
	float carAng;
	Matrix4 worldTransform;
	bool mustRecomputeTransform;
};