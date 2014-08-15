#include "Engine/Map.hpp"

Map::Map(sf::RenderTarget* rendertarget,
		 Resources* resources) :
	_rendertarget(rendertarget),
	_resources(resources)
{
}

Map::~Map()
{
	for (MapTile* tile : _tile)
	{
		delete tile;
	}
	for (MapPortal* portal : _portal)
	{
		delete portal;
	}
}

void Map::draw()
{
	for(MapTile* tile : _tile)
	{
		_rendertarget->draw(*tile);
	}
	#ifdef DEBUG
	for(MapPortal* portal : _portal)
	{
		_rendertarget->draw(*portal);
	}
	for(sf::Text text : _enumerations)
	{
		_rendertarget->draw(text);
	}
#endif // DEBUG
}

MapPortal* Map::getPortal(MapPortal* veto) const
{
	return getRandomEntry<MapPortal*>(_portal,veto);
}

bool Map::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::string tmpString;
	#ifdef DEBUG
	std::stringstream tmpSstream;
	#endif // DEBUG
	int tmpIntX;
	int tmpIntY;
	unsigned int tmpUint;

	file >> tmpString;
	if (tmpString != "#FPMap_001")
	{
		return false;
	}
	unsigned int nTiles;
	file >> nTiles;
	unsigned int tileNumber=0;
	std::vector<sf::Vector2f> edges;
	std::vector<std::array<unsigned int,3>> portal;
	while (tileNumber <= nTiles)
	{
		char nxt = file.peek();
		switch (nxt)
		{
		case 'e':
			file >> tmpString;
			if (tmpString != "e")
			{
				return false;
			}
			file >> tmpIntX >> tmpIntY;
			edges.push_back(sf::Vector2f(tmpIntX,tmpIntY));
			file.ignore();
			nxt = file.peek();
			if (nxt == 'p')
			{
				file >> tmpString;
				if (tmpString != "p")
				{
					return false;
				}
				file >> tmpUint;
				portal.push_back(std::array<unsigned int,3>{{tileNumber,tmpUint,
									static_cast<unsigned int>(edges.size())}});
			}
			break;
		case 't':
			file >> tmpString;
			if (tmpString != "tile")
			{
				return false;
			}
			if (edges.size() > 0)
			{
				_tile.push_back(new MapTile(edges));
				#ifdef DEBUG
				tmpSstream.str("");
				tmpSstream << tileNumber;
				_enumerations.push_back(sf::Text(tmpSstream.str(),
												 _resources->debugfont));
				_enumerations.back().setPosition(_tile.back()->getCenter());
				_enumerations.back().setScale(0.5f,0.5f);
				#endif // DEBUG
			}
			edges.clear();
			file >> tileNumber;
			break;
		default:
		case '\n':
		case '\t':
			file.ignore();
			break;
		}
	}
	for (std::array<unsigned int,3> p : portal)
	{
		if (p[1] > 0)
		{
			_tile[p[0]-1]->setNeighbor(_tile[p[1]-1],p[2]-1);
		}
		else
		{
			std::array<sf::Vector2f,2> edges;
			edges[0] = _tile[p[0]-1]->getPoint(p[2]-1);
			if (p[2] < _tile[p[0]-1]->getPointCount())
			{
				edges[1] = _tile[p[0]-1]->getPoint(p[2]);
			}
			else
			{
				edges[1] = _tile[p[0]-1]->getPoint(0);
			}
			_portal.push_back(new MapPortal(edges,_tile[p[0]-1]));
			_tile[p[0]-1]->setNeighbor(_portal.back(),p[2]-1);
		}
	}
	return true;
}

std::vector<MapComponent*> Map::getAStarPath(MapComponent* from,
											 MapComponent* to,
											 const unsigned int maxlen) const
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

	std::vector<MapComponent*> path;

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
			if(maxlen > 0 && path.size() > maxlen )
			{
				path.resize(maxlen);
			}
			return path;
		}

		for (size_t i=0; i<currentnode->getField()->getNNeighbors(); i++)
		{
			MapComponent* tmpnbr=currentnode->getField()->getNeighbor(i);
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
