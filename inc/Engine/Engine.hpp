#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <random>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Map.hpp"
#include "Person.hpp"
#include "Resources.hpp"
#include "TrackingData.hpp"

class Engine
{
public:
	Engine(sf::RenderWindow* window, Resources* res, Map* map);

	~Engine();

	void run();

private:
    void _scroll();

private:
	Map* _map;

	std::vector<Person*> _person;

    sf::Vector2i _pointerpos;

	std::vector<TrackingData*> _records;

	Resources* _res;

    sf::View _view;

    sf::RenderWindow* _window;
};

#endif // ENGINE_HPP
