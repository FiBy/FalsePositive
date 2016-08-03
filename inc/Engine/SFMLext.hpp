#ifndef SFMLEXT_HPP
#define SFMLEXT_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "Engine/SFMLext.hpp"

namespace sfe
{

const float scalar(const sf::Vector2f v1, const sf::Vector2f v2);

const float length(const sf::Vector2f vec);

std::array<sf::Vector2f,2> normal(const sf::Vector2f p1,
								  const sf::Vector2f p2);

/**
 * @brief normal
 * @param p1
 * @param p2
 * @param sign
 * @return	first element is direction of the normal vector,
 *			second element is the center of the plane
 *			on which the normal is defined
 */
std::array<sf::Vector2f,2> normal(const sf::Vector2f p1,
								  const sf::Vector2f p2,
								  const sf::Vector2f direction);
}

/**
 * @brief operator << to print Vector2f
 * @param stream
 * @param vec
 * @return
 */
std::ostream& operator<< (std::ostream& stream, const sf::Vector2f vec);

#endif // SFMLEXT_HPP
