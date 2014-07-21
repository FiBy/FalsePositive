#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Engine/Map.hpp"
#include "Engine/Resources.hpp"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "False Positive");

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


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		map.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
