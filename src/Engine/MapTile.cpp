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

MapComponent* MapTile::getDirectionTo(MapComponent* goal) const
{
	for (MapComponent* mc : _portal)
	{
		if (mc == goal)
		{
			return mc;
		}
	}
	return getRandomEntry<MapComponent*>(_portal,nullptr);
}

sf::Vector2f MapTile::getForce(sf::Vector2f pos) const
{
	sf::Vector2f rv;
	for (std::array<sf::Vector2f,2> n : _normal)
	{
		sf::Vector2f fv = sfe::scalar(pos-n[1],n[0])*n[0];
		rv += float(pow(sfe::abs(fv),-8))*fv;
	}
	return rv;
}

MapComponent* MapTile::getNeighbor(unsigned int n) const
{
	return _portal[n];
}

MapComponent *MapTile::getNeighbor(MapComponent* veto) const
{
	return getRandomEntry<MapComponent*>(_portal,veto);
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

void MapTile::setNormals()
{
	for (unsigned int i=0; i<_portal.size(); i++)
	{
		if (_portal[i] == nullptr)
		{
			_normal.push_back(sfe::normal(getPoint(i),
										  getPoint((i+1)%getPointCount()),
										  getCenter()));
		}
	}
}

bool MapTile::operator==(const sf::Vector2f pos) const
{
	return getGlobalBounds().contains(pos);
}
