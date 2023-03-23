#pragma once
#include "Vector2.h"
#include "RendererOGL.h"
#include "Rectangle.h"
#include "Matrix4.h"
#include "Vector3.h"


class Car
{
public:
	Car(Vector2 p, float v, Vector2 carS) : pos(p), velocity(v), carScale(carS), carAng(-90){}
	Car() : pos({ 60,300 }), velocity(0), carScale({ 0,0}), carAng(-90){}
	~Car() {}

	void draw(RendererOGL* rend, OGL_Texture* myText, const Matrix4 wtMat); //OGL_Texture n'existe pas. Trouver un moyen de charger la texture avec OpenGL

	void update(float nextX, float nextY);

	void driveForward();

	void slowDown(float v);

	void brake();

	Vector2 getPos();
	
	float getVelo();

	Vector2 getCarScale();

	float getCarAng();

	void turnRight(float rot);

	void turnLeft(float rot);
	
	void setV(float v);
	
	void setP(Vector2 p);

	void setCarAng(float a);
	
	void setCarScale(Vector2 carS);

private:

	Vector2 pos;
	float velocity;
	Vector2 carScale;
	float carAng;
};