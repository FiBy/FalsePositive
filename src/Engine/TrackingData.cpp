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
	std::cout << _lifetime.asMilliseconds() << std::endl;
#endif
}
