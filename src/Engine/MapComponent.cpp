#include "Engine/MapComponent.hpp"


MapComponent::MapComponent(bool accessible) :
	_accessible(accessible)
{
}

bool MapComponent::toggleAccessible()
{
	_accessible = !_accessible;
	return _accessible;
}
