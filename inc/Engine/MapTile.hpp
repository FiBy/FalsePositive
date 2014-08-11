#ifndef MAPTILE_HPP
#define MAPTILE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Engine/MapComponent.hpp"
#include "main.hpp"

class MapTile : public MapComponent, public sf::ConvexShape
{
public:
	MapTile(std::vector<sf::Vector2f> edges);

	sf::Vector2f getCenter() const;

	/**
	 * @brief getDirectionTo
	 * @param goal
	 * @return correct direction in goal is close by, random neighbor otherwise
	 */
	MapComponent* getDirectionTo(MapComponent* goal) const;

	MapComponent* getNeighbor(size_t n) const;

	/**
	 * @brief getNeighbor
	 * @param veto
	 * @return random Neighbor (but not veto)
	 */
	MapComponent* getNeighbor(MapComponent* veto=nullptr) const;

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
