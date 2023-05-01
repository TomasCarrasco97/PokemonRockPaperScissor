#ifndef GAME_RESPONSE_H
#define GAME_RESPONSE_H

#include <SFML/Graphics.hpp>

class GameResponse
{
private:
	// an integer representing the index of the next screen
	//in Main's vector of screens.
	int nextScreen;
	// an integer representing a pokemon monster
	// 0 - squirtle, 1 - bulbasaur, 2 - charmander.
	int humanMonster;
	//Name of the human player.
	sf::String humanName;
	//Gender of the human player.
	sf::String gender;
	//Store scores for human, computer players.
	int human_score, computer_score;

public:
	GameResponse();
	int getNextScreen();
	int getHumanMonster();
	sf::String getHumanName();
	sf::String getHumanGender();
	int getHumanScore();
	int getComputerScore();

	void setNextScreen(int next);
	void setHumanMonster(int _humanMonster);
	void setHumanName(sf::String _humanName);
	void setHumanGender(sf::String _gender);
	void increaseHumanScore(int score);
	void increaseComputerScore(int score);
	void resetScores();
};

#endif // GAME_RESPONSE_H
