#include <iostream>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Response.h"

class StartScreen : public Screen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
	int playerMonsterIndex;
	sf::Sprite monsters[3];
	GameResponse* response;

	bool isAlpha(sf::Uint32 ch);

public:
    StartScreen(sf::Sprite monsters[3], GameResponse* response);
    virtual GameResponse* run(sf::RenderWindow& App, sf::Font font);
};

