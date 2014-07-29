#ifndef MAPPORTAL_HPP
#define MAPPORTAL_HPP

#include <array>
#include <SFML/Graphics/VertexArray.hpp>

#include "Engine/MapComponent.hpp"

class MapPortal : public MapComponent, public sf::VertexArray
{
public:
	MapPortal(std::array<sf::Vector2f,2> edges);

	sf::Vector2f getCenter() const;
};

#endif // MAPPORTAL_HPP
