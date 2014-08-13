#ifndef MAP_HPP
#define MAP_HPP

#include <array>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>

#include "Engine/MapPortal.hpp"
#include "Engine/MapTile.hpp"
#include "Engine/Resources.hpp"
#include "main.hpp"

class Map
{
public:
	Map(sf::RenderTarget* rendertarget,
		Resources* resources);

	~Map();

	void draw();

	/**
	 * @brief getAStarPath
	 * @param from
	 * @param to
	 * @param maxlen
	 * @return
	 * @todo: more efficient implementation for maxlen > 0
	 */
	std::vector<MapComponent*> getAStarPath( MapComponent* from,
											 MapComponent* to,
											 const size_t maxlen=0) const;

	MapComponent* getComponentAt(sf::Vector2f pos);

	MapPortal* getPortal(MapPortal* veto=nullptr) const;

	/**
	 * @brief loadFromFile
	 * @param filename
	 * @return Was map succesfully loaded?
	 */
	bool loadFromFile(const std::string& filename);

private:
	std::vector<MapTile*> _tile;

	std::vector<MapPortal*> _portal;

	sf::RenderTarget* _rendertarget;

	Resources* _resources;

	#ifdef DEBUG
	std::vector<sf::Text> _enumerations;
	#endif // DEBUG
};

#endif // MAP_HPP
