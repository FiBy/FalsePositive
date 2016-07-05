#include "Engine/Engine.hpp"

Engine::Engine(sf::RenderWindow* window, Resources* res, Map* map) :
	_map(map),
	_res(res),
	_window(window)
{
    _view.setSize(map->getSize().x,map->getSize().y);
    _view.setCenter(map->getSize().x/2,map->getSize().y/2);
}

Engine::~Engine()
{
	for (Person* p : _person)
	{
		delete p;
	}
	for (TrackingData* d : _records)
	{
		delete d;
	}
}

void Engine::run()
{
	std::random_device rdev{};
	static std::default_random_engine e{rdev()};
	std::normal_distribution<float> r(0,25);
    float speed;

    _window->setView(_view);

	MapPortal* portal1;
	MapPortal* portal2;

	for (MapPortal* p : *(_map->getPortals()))
	{
		portal2 = _map->getPortal(p);
		speed = 75 + std::abs(r(e));
		_person.push_back(new Person(_map,p,&_person,portal2,speed));
	}

	sf::Clock clock;
	sf::Clock personspawntime;
	personspawntime.restart();
	sf::Clock tileswitchtime;
    tileswitchtime.restart();
    sf::Vector2f worldPos;
	// run the program as long as the window is open
	while (_window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (_window->pollEvent(event))
        {
            MapComponent* cc = nullptr;
			switch (event.type) {
			case sf::Event::Closed:
				// "close requested" event: we close the window
				_window->close();
				break;
            case sf::Event::MouseButtonPressed:
                worldPos = _window->mapPixelToCoords(_pointerpos);
                cc = _map->getComponentAt(worldPos);
				if (cc != nullptr)
				{
					cc ->toggleAccessible();
				}
                break;
            case sf::Event::MouseMoved:
                _pointerpos = sf::Mouse::getPosition(*_window);
                break;
            case sf::Event::Resized:
                _view.setSize(event.size.width, event.size.height);
                _window->setView(_view);
                break;
			default:
				break;
			}
        }
        _scroll();
		_window->clear();
		_map->draw();
		for (Person* p : _person)
		{
			_window->draw(*p);
		}
		_window->display();

		if (tileswitchtime.getElapsedTime().asSeconds() > 1.5f)
		{
			tileswitchtime.restart();
			_map->getTile()->toggleAccessible();
		}

		if (personspawntime.getElapsedTime().asSeconds() > 0.5f)
		{
			personspawntime.restart();
			portal1 = _map->getPortal();
			portal2 = _map->getPortal(portal1);
			speed = 75 + std::abs(r(e));
			_person.push_back(new Person(_map,portal1,&_person,portal2,speed));
		}

		sf::Time elapsed = clock.restart();
		for (unsigned int i=0; i<_person.size(); i++)
		{
			switch (_person[i]->move(elapsed))
			{
			case Person::movement::arrived:
				break;
			case Person::movement::moved:
				break;
			case Person::movement::none:
				_records.push_back(new TrackingData(_person[i]));
				delete _person[i];
				_person.erase(_person.begin()+i);
				break;
			default:
				break;
			}
		}
    }
}

void Engine::_scroll()
{
    if (_map->getSize().x > _window->getSize().x) {
        if (_pointerpos.x < 20) {
            _view.move(-3, 0);
        }
        if (_pointerpos.x > static_cast<int>(_window->getSize().x)-20) {
            _view.move( 3, 0);
        }
    }
    if (_map->getSize().y > _window->getSize().y) {
        if (_pointerpos.y < 20) {
            _view.move( 0,-3);
        }
        if (_pointerpos.y > static_cast<int>(_window->getSize().y)-20) {
            _view.move( 0, 3);
        }
        _window->setView(_view);
    }
}
