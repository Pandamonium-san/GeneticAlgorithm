#pragma once
#include "GameObject.h"

class City : public GameObject
{
public:
	City(sf::Vector2f pos);

	void Draw(sf::RenderWindow* window) override;
	void SetHitbox() override;

	sf::RectangleShape body;
};