#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Engine/MapTile.hpp"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "False Positive");

    std::vector<sf::Vector2f> edges;
    edges.push_back(sf::Vector2f(10,100));
    edges.push_back(sf::Vector2f(10,300));
    edges.push_back(sf::Vector2f(300,500));
    edges.push_back(sf::Vector2f(300,300));

    sf::Vector2f pos(5,5);

    MapTile tile(edges,pos);


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
        window.draw(tile);
        window.display();
    }

    return EXIT_SUCCESS;
}
