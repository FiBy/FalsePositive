#include "Engine/Engine.hpp"

Engine::Engine(sf::RenderWindow* window, Resources* res, Map* map) :
	_map(map),
	_res(res),
	_window(window)
{
}

Engine::~Engine()
{
	for (Person* p : _person)
	{
		delete p;
	}
}

void Engine::run()
{
	MapPortal* portal1 = _map->getPortal();
	MapPortal* portal2 = _map->getPortal(portal1);

	_person.push_back(new Person(portal1,portal2));

	_person.back()->addWaypoint(portal2->getCenter()-sf::Vector2f(12,12));

	sf::Clock clock;
	// run the program as long as the window is open
	while (_window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (_window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				_window->close();
		}
		_window->clear();
		_map->draw();
		for (Person* p : _person)
		{
			_window->draw(*p);
		}
		_window->display();

		sf::Time elapsed = clock.restart();
		for (unsigned int i=0; i<_person.size(); i++)
		{
			if (_person[i]->move(elapsed))
			{
				delete _person[i];
				_person.erase(_person.begin()+i);
			}
		}
	}
}
