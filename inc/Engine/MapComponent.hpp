#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

#include <list>
#include <SFML/System/Vector2.hpp>
#include <vector>

class MapComponent
{
public:
	virtual sf::Vector2f getCenter() const =0;

	virtual MapComponent* getDirectionTo(MapComponent* goal) const =0;

	virtual MapComponent* getNeighbor(size_t) const =0;

	virtual size_t getNNeighbors() const =0;
};

#endif // MAPCOMPONENT_HPP
