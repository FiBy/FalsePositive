#include "Engine/Resources.hpp"

Resources::Resources()
{
}

bool Resources::loadFonts()
{
	std::string  mono="fonts/pt-mono/PTM55FT.ttf";
	if (debugfont.loadFromFile(mono))
	{
		return true;
	}
	return false;
}
