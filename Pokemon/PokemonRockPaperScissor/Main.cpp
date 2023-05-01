//Tomas Carrasco 
// COP 3003 Tomas Carrasco TR - 3:00 - 4:15pm
// Created a "Pocket-Monster themed rock, paper, scissor game
// where the player can chose between boy and girl


#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
#include <vector>

#include "Screens.h"
#include "Response.h"

int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));


	sf::Font font;
	sf::Texture squirtle, bulbasaur, charmander;
	sf::Sprite monsters[3];

	//Create window.
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Rock Paper Scissor");

	//window.setMouseCursorVisible(false);

	if (!font.loadFromFile("Fonts/verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	// Load the squirtle Pokemon
	if (!squirtle.loadFromFile("Images/squirtle.png"))
	{
		std::cerr << "Error loading squirtle.png" << std::endl;
		return (-1);
	}
	//monsters[0] -> squirtle
	monsters[0].setTexture(squirtle);


	// Load the bulbasaur Pokemon
	if (!bulbasaur.loadFromFile("Images/bulbasaur.png"))
	{
		std::cerr << "Error loading bulbasaur.jpeg" << std::endl;
		return (-1);
	}
	//monsters[1] -> bulbasaur
	monsters[1].setTexture(bulbasaur);

	// Load the charmander Pokemon
	if (!charmander.loadFromFile("Images/charmander.png"))
	{
		std::cerr << "Error loading charmander.png" << std::endl;
		return (-1);
	}
	//monsters[2] ->charmander
	monsters[2].setTexture(charmander);

	int screenIdx = 0;
	std::vector<Screen*> screens;
	

	GameResponse* response = new GameResponse();

	StartScreen startScreen(monsters, response);
	GameScreen gameScreen(monsters, response);
	EndScreen endScreen(monsters, response);

	// Put the screens into the vector data structure.
	screens.push_back(&startScreen);
	screens.push_back(&gameScreen);
	screens.push_back(&endScreen);

	int playerMonster = 0;

	//The main loop.
	while (screenIdx >= 0)
	{
		response = screens[screenIdx]->run(window, font);

		if (response == NULL)
			screenIdx = -1;
		else
			screenIdx = response->getNextScreen();
	}

	if (response != NULL)
		delete response;

	return EXIT_SUCCESS;
}