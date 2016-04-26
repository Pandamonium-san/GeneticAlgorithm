#pragma once
#include "Game.h"
#include <SFML/System/Vector2.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void HandleEvents(sf::Event event){}
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow* window){}
	virtual void DoCollision(GameObject* other){};
	virtual bool IsColliding(GameObject* other);
	virtual void SetHitbox();

	sf::FloatRect hitbox;
	bool isActive = true;
	int type;

	enum
	{
		TYPE_NONE = 0x00000001,
		TYPE_CITY = 0x00000002,
		TYPE_TSALESMAN = 0x00000004,
	};
};