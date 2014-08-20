#include "Engine/MapPortal.hpp"

MapPortal::MapPortal(std::array<sf::Vector2f,2> edges, MapTile* neighbor) :
	sf::VertexArray::VertexArray(sf::PrimitiveType::Lines,2),
	_neighbor(neighbor)
{
	operator[](0) = sf::Vertex(edges[0],sf::Color::Red);
	operator[](1) = sf::Vertex(edges[1],sf::Color::Red);
}

sf::Vector2f MapPortal::getCenter() const
{
	return (operator[](0).position+operator[](1).position)/2.0f;
}

bool MapPortal::operator==(const sf::Vector2f pos) const
{
	sf::Vector2f v = _normal[1] - pos;
	if ((v.x*_normal[0].x + v.y * _normal[0].y) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MapPortal::setNormal()
{
	_normal = sfe::normal(operator[](0).position,
						  operator[](1).position,
						  _neighbor->getCenter());
}
