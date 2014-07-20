#include "Engine/MapTile.hpp"

MapTile::MapTile(std::vector<sf::Vector2f> edges)
{
    setPointCount(edges.size());
    _side.resize(edges.size(),nullptr);
    for (unsigned int p=0; p<edges.size(); p++)
    {
        setPoint(p,edges[p]);
    }
    setFillColor(sf::Color(127,127,127));
}
