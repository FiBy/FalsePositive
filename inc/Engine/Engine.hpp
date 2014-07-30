#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Map.hpp"
#include "Person.hpp"
#include "Resources.hpp"

class Engine
{
public:
	Engine(sf::RenderWindow* window, Resources* res, Map* map);

	~Engine();

	void run();

private:
	Map* _map;

	std::vector<Person*> _person;

	Resources* _res;

	sf::RenderWindow* _window;
};

#endif // ENGINE_HPP
