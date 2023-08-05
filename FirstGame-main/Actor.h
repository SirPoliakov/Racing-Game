#pragma once
#include <vector>
#include "Vector3.h"
#include "Vector2.h"

#include <SDL_stdinc.h>
#include "Matrix4.h"
using std::vector;

class Game;
class Component;

class Actor
{
public:

	enum class ActorState
	{
		Active,
		Paused,
		Accomplished,
		Out,
		Dead
	};

	Actor();
	Actor(Vector2 _Scale, Vector3 _Pos = Vector3::zero);
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector3 getPosition() const { return position; }
	const float getRotation() const { return rotation; }
	const Vector2 getScale() const { return scale; }
	const Matrix4& getWorldTransform() const { return worldTransform; }

	void setPosition(Vector3 positionP);
	void setScale(Vector2 scaleP);
	void setState(ActorState stateP);

	void setRotation(float angle);
	void rotate(float angle);
	void computeWorldTransform();

	void processInput(const struct InputState& inputState);
	virtual void actorInput(const struct InputState& inputState);
	void update(float dt);

	inline vector<Component*> getComponents() { return components; }

	template <typename T>
	T* getComponent();

	void updateComponents(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

protected:
	Game& game;
	ActorState state;
	Vector3 position;
	float rotation;
	Vector2 scale;
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform;

	vector<Component*> components;
};