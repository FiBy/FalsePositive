#include "Engine/SFMLext.hpp"


float sfe::abs(const sf::Vector2f v)
{
	return sqrt(v.x*v.x+v.y*v.y);
}

float sfe::scalar(const sf::Vector2f v1, const sf::Vector2f v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}
