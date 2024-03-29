#pragma once
#include <SDL_stdinc.h>
#include <string>


class Actor;

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void processInput(const struct InputState& inputState);
	virtual void update(float dt);
	virtual void onUpdateWorldTransform() {}

	virtual std::string getComponentName();

protected:
	Actor& owner;
	int updateOrder;		// Order of the component in the actor's updateComponent method
};
