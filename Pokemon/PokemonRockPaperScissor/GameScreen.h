#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Response.h"
#include "Screen.h"
#include <string>

class GameScreen : public Screen
{
private:
	sf::String messages[6] = {
		"Squirtle (a water) is weak to Bulbasaur (a grass)",
		"Bulbasaur (a grass) is weak to Charmander (a fire)",
		"Charmander (a fire) is weak to Squirtle (a water)",
		"Squirtle (a water) is resistance to Squirtle",
		"Bulbasaur (a grass) is resistance to Bulbasaur",
		"Charmander (a fire) is resistance to Charmander"
	};

	sf::String monster_names[3] = {
		"Squirtle\ntype: water",
		"Bulbasaur\ntype: grass",
		"Charmander\ntype: fire",
	};

	GameResponse* response;
	sf::Sprite monsters[3];
	int human_score, comp_score;
	int humanSelection, computerSelection;
	sf::String win_message;
	sf::String win_tagline;
	int round;

	void computerPlay();
	void humanPlay(int monsterIdx);
	void getRoundWinner();
	void playGame(int humanMonsterIdx);

public:
	GameScreen(sf::Sprite monsters[3], GameResponse* response);
	virtual GameResponse* run(sf::RenderWindow& app, sf::Font font);
	void startGame();

};
