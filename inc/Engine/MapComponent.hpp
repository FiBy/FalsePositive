#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

#include <list>
#include <SFML/System/Vector2.hpp>
#include <utility>
#include <vector>

class MapComponent
{
public:
	virtual sf::Vector2f getCenter() const =0;

	virtual MapComponent* getDirectionTo(MapComponent* goal) const =0;

	virtual std::pair<bool,sf::Vector2f>
		getForce(sf::Vector2f pos,float comfortzone) const =0;

	virtual MapComponent* getNeighbor(unsigned int) const =0;

	virtual unsigned int getNNeighbors() const =0;

	virtual bool operator==(const sf::Vector2f pos) const =0;
};

#endif // MAPCOMPONENT_HPP
