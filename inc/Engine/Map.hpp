#ifndef MAP_HPP
#define MAP_HPP

#include <array>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>

#include "Engine/MapTile.hpp"
#include "Engine/Resources.hpp"

class Map
{
public:
	Map(sf::RenderTarget* rendertarget,
		Resources* resources);

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

	Resources* _resources;

	#ifdef DEBUG
	std::vector<sf::Text> _enumerations;
	#endif // DEBUG
};

#endif // MAP_HPP
