#include "Response.h"

GameResponse::GameResponse()
{
	nextScreen = 0;
	humanMonster = 0;
	human_score = 0;
	computer_score = 0;
	humanName = "Player";
	gender = "";
}

int GameResponse::getNextScreen() {
	return nextScreen;
}

int GameResponse::getHumanMonster() {
	return humanMonster;
}

sf::String GameResponse::getHumanName()
{
	return humanName;
}

sf::String GameResponse::getHumanGender()
{
	return gender;
}

int GameResponse::getHumanScore()
{
	return human_score;
}

int GameResponse::getComputerScore()
{
	return computer_score;
}

void GameResponse::setNextScreen(int next)
{
	nextScreen = next;
}

void GameResponse::setHumanMonster(int _humanMonster)
{
	humanMonster = _humanMonster;
}

void GameResponse::setHumanName(sf::String _humanName)
{
	humanName = std::move(_humanName);
}

void GameResponse::setHumanGender(sf::String _gender)
{
	gender = std::move(_gender);
}

void GameResponse::increaseHumanScore(int score)
{
	human_score += score;
}

void GameResponse::increaseComputerScore(int score)
{
	computer_score += score;
}

void GameResponse::resetScores()
{
	human_score = 0;
	computer_score = 0;
}