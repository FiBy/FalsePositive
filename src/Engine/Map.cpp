#include "Engine/Map.hpp"

Map::Map(sf::RenderTarget* rendertarget) :
	_rendertarget(rendertarget)
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
}

bool Map::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::string tmpString;
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
			file >> tileNumber;
			if (edges.size() > 0)
				_tile.push_back(new MapTile(edges));
			edges.clear();
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
