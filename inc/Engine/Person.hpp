#ifndef PERSON_HPP
#define PERSON_HPP

#include <cmath>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

// forward declaration
class Person;

#include "Engine/Map.hpp"
#include "Engine/MapPortal.hpp"
#include "Engine/MapTile.hpp"
#include "main.hpp"

class Person : public sf::CircleShape
{
public:
	Person(Map* map, MapComponent* spawn,
		   std::vector<Person*>* all=nullptr,
		   MapComponent* goal=nullptr, float speed=50.0f);

	enum class movement
		{ none, moved, arrived };

	MapComponent* getCurrentTile() const
		{ return _ct; }

	inline MapComponent* getGoal() const
		{ return _goal; }

	inline const sf::Time getLifetime() const
		{ return _lifetime.getElapsedTime(); }

	inline MapComponent* getStart() const
		{ return _start; }

	/**
	 * @brief move
	 * @param elapsed
	 * @return last waypoint reached?
	 */
	movement move(sf::Time elapsed);

private:
	float _acceleration;

	std::vector<Person*>* _allpersons;

	std::queue<MapComponent*> _checkpoint;

	MapComponent* _ct;

	sf::Vector2f _direction;

	MapComponent* _goal;

	sf::Clock _lifetime;

	Map* _map;

	sf::Vector2f _pos;

	static constexpr float _radius = 7.5f;

	static constexpr float _rotationangle = 0.75f;

	float _speed;

    MapComponent* _start;

    void addNewCheckpoint();

    void clearCheckpoints();
};

#endif // PERSON_HPP
