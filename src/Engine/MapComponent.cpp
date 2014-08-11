#include "Engine/MapComponent.hpp"

std::vector<const MapComponent*>
			MapComponent::_getAStarPath(	const MapComponent* from,
											const MapComponent* to) const
{
	// open list
	std::list<PathNode*> ol;
	// closed list
	std::list<PathNode*> cl;
	PathNode* currentnode;

	PathNode* newnode;

	// in list? (used for open and closed list)
	bool inl;
	// list iterator (used for open and closed list)
	std::list<PathNode*>::iterator lit;

	std::vector<const MapComponent*> path;

	currentnode = new PathNode(from, nullptr, to);
	ol.push_back( currentnode );

	while (! ol.empty() ) {
		currentnode = ol.front();
		cl.push_back(currentnode);
		ol.pop_front();

		if (currentnode->getField() == to) {
			// delete entries from open list
			for (lit = ol.begin(); lit != ol.end(); lit++) {
				delete *lit;
			}
			// reconstruct path
			while (currentnode->getField() != from) {
				path.push_back(currentnode->getField());
				currentnode = currentnode->getLast();
			}
			// delete entries from closed list
			for (lit = cl.begin(); lit != cl.end(); lit++) {
				delete *lit;
			}
			std::reverse(path.begin(),path.end());
			return path;
		}

		for (size_t i=0; i<currentnode->getField()->getNNeighbors(); i++)
		{
			const MapComponent* tmpnbr=currentnode->getField()->getNeighbor(i);
			if (tmpnbr != nullptr) {
				// check weather tmpneigbour has already been analyzed
				inl = false;
				for (lit = cl.begin(); lit != cl.end(); lit++) {
					if ((*lit)->getField() == tmpnbr) {
						inl = true;
						break;
					}
				}
				if (!inl) {
					newnode = new PathNode(tmpnbr, currentnode, to);
					for (lit = ol.begin(); lit!= ol.end(); lit++) {
						if ((*lit)->getField() == newnode->getField()) {
							inl = true;
							break;
						}
					}
					if (inl) {
						if (newnode->getCost() < (*lit)->getCost()) {
							(*lit)->setLast(currentnode);
						}
						delete newnode;
					} else {
						lit = ol.begin();
						while( lit != ol.end() &&
							  ((*lit)->getCost() < newnode->getCost()) ) {
							lit++;
						}
						ol.insert(lit,newnode);
					}
				}
			}
		}
	}
	// no path found
	return path;
}
