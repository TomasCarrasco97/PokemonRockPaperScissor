
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Response.h"

class EndScreen : public Screen
{
private:
	GameResponse* response;
	sf::String message;

public:
	EndScreen(sf::Sprite monsters[3], GameResponse* response);
	virtual GameResponse* run(sf::RenderWindow& App, sf::Font font);
	void saveEndMessage();

};

