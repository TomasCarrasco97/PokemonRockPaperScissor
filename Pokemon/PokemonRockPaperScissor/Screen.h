#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "Response.h"

class Screen
{
public:
	virtual GameResponse* run(sf::RenderWindow& App, sf::Font font) = 0;

	float calcStartX(sf::Text text, int screen_width)
	{
		return ((float)screen_width - text.getLocalBounds().width) / 2;
	}

	float getStartX(float screenWidth, sf::Text text) {
		return (screenWidth / 2) - (text.getGlobalBounds().width / 2);
	}

};

#endif // !SCREEN_H
