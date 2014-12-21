#ifndef TRACKINGDATA_HPP
#define TRACKINGDATA_HPP

#include <iostream>
#include <SFML/System/Clock.hpp>

#include "MapComponent.hpp"
#include "Person.hpp"

class TrackingData
{
public:
	TrackingData(Person* p);

	~TrackingData();

private:
	MapComponent* _goal;

	sf::Time _lifetime;

	MapComponent* _start;
};

#endif // TRACKINGDATA_HPP
