#include "Engine/PathNode.hpp"

PathNode::PathNode(	MapComponent* pos,
					PathNode* last,
					MapComponent* to ) :
	_mymc(pos),
	l(last)
{

	sf::Vector2f way;
	float dist;
	if (l != nullptr)
	{
		way = pos->getCenter()-last->getField()->getCenter();
		dist  = sqrt(pow(way.x,2)+pow(way.y,2));
		kc = last->kc + dist;
	}
	else
	{
		kc = 0;
	}
	way = pos->getCenter() - to->getCenter();
	dist  = sqrt(pow(way.x,2)+pow(way.y,2));
	ec = kc + dist;
}

PathNode::PathNode(const PathNode & orig) :
	_mymc(orig._mymc),
	l(orig.l),
	kc(orig.kc),
	ec(orig.ec)
{
}

void PathNode::setLast(PathNode* last)
{
	sf::Vector2f way = _mymc->getCenter()-last->getField()->getCenter();
	float dist  = sqrt(pow(way.x,2)+pow(way.y,2));
	ec -= kc - last->kc + dist;
	kc = last->kc + dist;
	l = last;
}
