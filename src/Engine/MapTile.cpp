#include "Engine/MapTile.hpp"

MapTile::MapTile(std::vector<sf::Vector2f> edges)
{
    setPointCount(edges.size());
	_portal.resize(edges.size(),nullptr);
    for (unsigned int p=0; p<edges.size(); p++)
    {
		setPoint(p,edges[p]);
    }
	setFillColor(sf::Color(127,127,127));
	#ifdef DEBUG
	setOutlineColor(sf::Color::White);
	setOutlineThickness(1);
	#endif //DEBUG
}

sf::Vector2f MapTile::getCenter() const
{
	sf::Vector2f sum = sf::Vector2f(0,0);
	for (unsigned int i=0;i<getPointCount();i++)
	{
		sum += getPoint(i);
	}
	return sf::Vector2f(sum.x/getPointCount(),sum.y/getPointCount()-8);
}

const MapComponent* MapTile::getDirectionTo(const MapComponent* goal) const
{
	return _getAStarPath(this,goal)[0];
}

const MapComponent* MapTile::getNeighbor(size_t n) const
{
	return _portal[n];
}

const MapComponent *MapTile::getNeighbor(const MapComponent* veto) const
{
	return getRandomEntry<const MapComponent*>(_portal,veto);
}

bool MapTile::setNeighbor(MapTile *tile)
{
	for (unsigned int t=0; t<getPointCount(); t++)
	{
		for (unsigned int o=0; o<tile->getPointCount(); o++)
		{
			if (getPoint(t) == tile->getPoint(o))
			{
				_portal[t] = tile;
				return true;
			}
		}
	}
	return false;
}

void MapTile::setNeighbor(MapComponent* component, unsigned int n)
{
	_portal[n] = component;
}
