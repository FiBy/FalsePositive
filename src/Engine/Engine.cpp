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
	std::random_device rdev{};
	static std::default_random_engine e{rdev()};
	std::normal_distribution<float> r(0,25);
	float speed;

	MapPortal* portal1;
	MapPortal* portal2;

	for (MapPortal* p : *(_map->getPortals()))
	{
		portal2 = _map->getPortal(p);
		speed = 75 + std::abs(r(e));
		_person.push_back(new Person(_map,p,&_person,portal2,speed));
	}

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
			switch (_person[i]->move(elapsed))
			{
			case Person::movement::arrived:
				;
				break;
			case Person::movement::moved:
				break;
			case Person::movement::none:
				delete _person[i];
				_person.erase(_person.begin()+i);
				portal1 = _map->getPortal();
				portal2 = _map->getPortal(portal1);
				speed = 75 + std::abs(r(e));
				_person.push_back(new Person(_map,portal1,&_person,portal2,speed));
				break;
			default:
				break;
			}
		}
	}
}
