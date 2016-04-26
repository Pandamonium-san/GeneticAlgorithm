#pragma once
#include <SFML/System/Vector2.hpp>
#include <sstream>

class Utility
{
public:
	template<class T>
	static std::string ToString(T x)
	{
		std::stringstream type;
		type << x;
		return type.str();
	}

	static sf::Vector2f AngleToVector(float angle);
	static float VectorToAngle(const sf::Vector2f& v);
	static bool VectorsAreParallel(const sf::Vector2f& v1, const sf::Vector2f& v2, float tolerance);
	static float ScalarProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static float LengthOfVector2(const sf::Vector2f& v);
	static float DistanceBetweenVectors(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static float DistanceSquared(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static sf::Vector2f Normalized(sf::Vector2f v);
};