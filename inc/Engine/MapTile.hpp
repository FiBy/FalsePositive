#ifndef MAPTILE_HPP
#define MAPTILE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class MapTile : public sf::ConvexShape
{
public:
	MapTile(std::vector<sf::Vector2f> edges);

	bool setNeighbor(MapTile* tile, int n=-1);

private:
	 std::vector<MapTile*> _portal;
};

#endif // MAPTILE_HPP
