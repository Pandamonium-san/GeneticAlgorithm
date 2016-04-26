#include "City.h"

City::City(sf::Vector2f pos)
{
	body = sf::RectangleShape(sf::Vector2f(30, 30));
	body.setOrigin(sf::Vector2f(15, 15));
	body.setPosition(pos);
	type = TYPE_CITY;
}

void City::Draw(sf::RenderWindow* window)
{
	window->draw(body);
}

void City::SetHitbox()
{
	hitbox = body.getGlobalBounds();
}
