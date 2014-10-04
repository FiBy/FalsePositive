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

	std::pair<bool,sf::Vector2f>
		getForce(sf::Vector2f pos,float comfortzone) const
		{ return std::pair<bool,sf::Vector2f>(false,sf::Vector2f()); }

	MapComponent* getNeighbor(unsigned int) const
		{ return _neighbor; }

	unsigned int getNNeighbors() const
		{ return 1; }

	std::array<sf::Vector2f,2> getNormal() const
		{ return _normal; }

	bool operator==(const sf::Vector2f pos) const;

	inline bool operator!=(const sf::Vector2f pos) const
		{ return !operator==(pos); }

	void setNormal();

private:
	MapTile* _neighbor;

	std::array<sf::Vector2f,2> _normal;
};

#endif // MAPPORTAL_HPP
