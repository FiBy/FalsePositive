#include "Engine/TrackingData.hpp"

TrackingData::TrackingData(Person* p) :
	_goal(p->getGoal()),
	_lifetime(p->getLifetime()),
	_start(p->getStart())
{
}

TrackingData::~TrackingData()
{
#ifdef DEBUG
    std::cout << _start->getCenter() << '\t'
              << _goal->getCenter() << '\t'
              << _lifetime.asMilliseconds() << std::endl;
#endif
}
