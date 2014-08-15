#ifndef MAPPORTAL_HPP
#define MAPPORTAL_HPP

#include <array>
#include <SFML/Graphics/VertexArray.hpp>

#include "Engine/MapComponent.hpp"
#include "Engine/MapTile.hpp"

class MapPortal : public MapComponent, public sf::VertexArray
{
public:
	MapPortal(std::array<sf::Vector2f,2> edges, MapTile* neighbor=nullptr);

	sf::Vector2f getCenter() const;

	MapComponent* getDirectionTo(MapComponent*) const
		{ return _neighbor; }

	MapComponent* getNeighbor(unsigned int) const
		{ return _neighbor; }

	unsigned int getNNeighbors() const
		{ return 1; }

private:
	MapTile* _neighbor;
};

#endif // MAPPORTAL_HPP
