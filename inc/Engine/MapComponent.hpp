#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

#include <list>
#include <SFML/System/Vector2.hpp>
#include <utility>
#include <vector>

class MapComponent
{
public:
	MapComponent(	bool accessible = true);

    inline bool accessible() const
		{return _accessible; }

    virtual inline bool accessibleFrom(MapComponent* other) const
        { return accessible(); }

	virtual sf::Vector2f getCenter() const =0;

	virtual MapComponent* getDirectionTo(MapComponent* goal) const =0;

	virtual std::pair<bool,sf::Vector2f> getForce(	sf::Vector2f position,
													sf::Vector2f direction,
													MapComponent* target,
													float size) const =0;

	virtual MapComponent* getNeighbor(unsigned int) const =0;

	virtual unsigned int getNNeighbors() const =0;

	virtual bool operator==(const sf::Vector2f pos) const =0;

	virtual bool operator!=(const sf::Vector2f pos) const =0;

	virtual bool toggleAccessible();

protected:
	bool _accessible;
};

#endif // MAPCOMPONENT_HPP
