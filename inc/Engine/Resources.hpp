#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Resources
{
public:
	Resources();

	bool loadFonts();

	sf::Font debugfont;
};

#endif // RESOURCES_HPP
