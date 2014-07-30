#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

#include <SFML/System/Vector2.hpp>

class MapComponent
{
public:
	MapComponent();

	virtual sf::Vector2f getCenter() const =0;
};

#endif // MAPCOMPONENT_HPP
