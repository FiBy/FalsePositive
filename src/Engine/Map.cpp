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
}

void Map::draw()
{
	for(MapTile* tile : _tile)
	{
		_rendertarget->draw(*tile);
	}
	#ifdef DEBUG
	for(sf::Text text : _enumerations)
	{
		_rendertarget->draw(text);
	}
	#endif // DEBUG
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
	std::vector<std::array<unsigned int,2>> portal;
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
				portal.push_back(std::array<unsigned int,2>{{tileNumber,tmpUint}});
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
				_enumerations.back().setPosition(edges.front());
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
	for (std::array<unsigned int,2> p : portal)
	{
		_tile[p[0]-1]->setNeighbor(_tile[p[1]-1]);
	}
	return true;
}
