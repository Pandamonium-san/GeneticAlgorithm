#include "Utility.h"
#include <iostream>

sf::Vector2f Utility::AngleToVector(float angle)
{
	float radians = angle / 57.2958279088f;
	return sf::Vector2f(cos(radians), sin(radians));
}

float Utility::VectorToAngle(const sf::Vector2f& v)
{
	return (atan2(-v.y, -v.x) * 57.2958279088f) + 180;
}

float Utility::ScalarProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float Utility::LengthOfVector2(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

bool Utility::VectorsAreParallel(const sf::Vector2f& v1, const sf::Vector2f& v2, float tolerance)
{
	return ScalarProduct(v1, v2) / (LengthOfVector2(v1) * LengthOfVector2(v2)) > 1 - tolerance;
}

float Utility::DistanceBetweenVectors(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}

float Utility::DistanceSquared(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return (v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y);
}

sf::Vector2f Utility::Normalized(sf::Vector2f v)
{
	return v / LengthOfVector2(v);
}


