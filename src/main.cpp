#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Engine/Engine.hpp"
#include "Engine/Map.hpp"
#include "Engine/Resources.hpp"

int main(int argc, char* argv[])
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "False Positive",
							sf::Style::Default,settings);

	Resources res;

	if (!res.loadFonts())
	{
		return EXIT_FAILURE;
	}

	Map map(&window,&res);
	if (!map.loadFromFile("maps/chessboard.map"))
	{
		return EXIT_FAILURE;
	}

	window.setFramerateLimit(30);

	Engine engine(&window,&res,&map);

	engine.run();

    return EXIT_SUCCESS;
}
