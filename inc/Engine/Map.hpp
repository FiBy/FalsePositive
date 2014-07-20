#ifndef MAP_HPP
#define MAP_HPP

#include <array>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Engine/MapTile.hpp"

class Map
{
public:
	Map(sf::RenderTarget* rendertarget);

	~Map();

	void draw();

	/**
	 * @brief loadFromFile
	 * @param filename
	 * @return Was map succesfully loaded?
	 */
	bool loadFromFile(const std::string& filename);

private:
	std::vector<MapTile*> _tile;

	sf::RenderTarget* _rendertarget;
};

#endif // MAP_HPP
