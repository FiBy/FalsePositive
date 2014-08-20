#include "Engine/SFMLext.hpp"


float sfe::abs(const sf::Vector2f v)
{
	return sqrt(v.x*v.x+v.y*v.y);
}

float sfe::scalar(const sf::Vector2f v1, const sf::Vector2f v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}


std::array<sf::Vector2f,2> sfe::normal( const sf::Vector2f p1,
										const sf::Vector2f p2,
										const sf::Vector2f sign)
{
	sf::Vector2f d = p1 - p2;
	sf::Vector2f n;
	n.x = d.y;
	n.y = -d.x;
	if (n.x*(p1.x-sign.x)+n.y*(p1.y-sign.y) > 0)
	{
		n = -1.0f*n;
	}
	float len_n = sqrt(pow(n.x,2)+pow(n.y,2));
	n.x /= len_n;
	n.y /= len_n;
	return std::array<sf::Vector2f,2>{n,0.5f*(p1+p2)};
}
