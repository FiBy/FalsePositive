#ifndef MAPTILE_HPP
#define MAPTILE_HPP

#include <climits>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Engine/MapComponent.hpp"

class MapTile : public MapComponent, public sf::ConvexShape
{
public:
	MapTile(std::vector<sf::Vector2f> edges);

	/**
	 * @brief setNeighbor
	 * @param tile: neigboring tile
	 * @return
	 */
	bool setNeighbor(MapTile* tile);

	/**
	 * @brief setNeighbor
	 * @param component
	 * @param n
	 */
	void setNeighbor(MapComponent* component, unsigned int n);

private:
	std::vector<MapComponent*> _portal;
};

#endif // MAPTILE_HPP
