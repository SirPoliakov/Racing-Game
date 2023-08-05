#include "Component.h"
#include "Actor.h"

Component::Component(Actor* ownerP, int updateOrderP) :
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::processInput(const InputState& inputState)
{
}

void Component::update(float dt)
{
}

std::string Component::getComponentName()
{
	return "Default";
}