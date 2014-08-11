#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

class MapComponent;

#include <list>
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "PathNode.hpp"

class MapComponent
{
public:
	virtual sf::Vector2f getCenter() const =0;

	virtual const MapComponent* getDirectionTo(const MapComponent* goal) const =0;

	virtual const MapComponent* getNeighbor(size_t) const =0;

	virtual size_t getNNeighbors() const =0;

protected:
	std::vector<const MapComponent*>
					_getAStarPath(	const MapComponent* from,
									const MapComponent* to) const;
};

#endif // MAPCOMPONENT_HPP
