#include "Engine/MapPortal.hpp"

MapPortal::MapPortal(std::array<sf::Vector2f,2> edges) :
	sf::VertexArray::VertexArray(sf::PrimitiveType::Lines,2)
{
	operator[](0) = sf::Vertex(edges[0],sf::Color::Red);
	operator[](1) = sf::Vertex(edges[1],sf::Color::Red);
}

sf::Vector2f MapPortal::getCenter() const
{
	return (operator[](0).position+operator[](1).position)/2.0f;
}
