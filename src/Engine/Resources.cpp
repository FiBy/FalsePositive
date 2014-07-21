#include "Engine/Resources.hpp"

Resources::Resources()
{
}

bool Resources::loadFonts()
{
	std::string mono = "/usr/share/fonts/truetype/ttf-liberation/LiberationMono-Regular.ttf";

	if (!debugfont.loadFromFile(mono))
	{
		return false;
	}
	return true;
}