#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
	SetHitbox();
}

void GameObject::SetHitbox()
{
	throw std::exception("SetHitbox Not Implemented");
}

bool GameObject::IsColliding(GameObject* other)
{
	if (hitbox.intersects(other->hitbox))
		return true;
	else
		return false;
}

