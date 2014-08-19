#ifndef SFMLEXT_HPP
#define SFMLEXT_HPP

#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "Engine/SFMLext.hpp"

namespace sfe
{

float abs(const sf::Vector2f v);

float scalar(const sf::Vector2f v1, const sf::Vector2f v2);
}
#endif // SFMLEXT_HPP
