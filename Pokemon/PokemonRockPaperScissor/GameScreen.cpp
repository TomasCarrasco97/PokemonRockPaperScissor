#include "GameScreen.h"
#include "Response.h"

GameScreen::GameScreen(sf::Sprite _monsters[3], GameResponse* _response)
{
	for (int i = 0; i < 3; i++) 
	{
		monsters[i] = _monsters[i];
		monsters[i].scale({ 0.7, 0.7 });
	}
	response = _response;
	win_message = "";
	win_tagline = "";
	round = 1;
}

void GameScreen::humanPlay(int monsterIdx)
{
	humanSelection = monsterIdx;
}

void GameScreen::computerPlay()
{
	computerSelection = rand() % 3;
}

void GameScreen::playGame(int humanMonsterIdx)
{
	humanPlay(humanMonsterIdx);
	computerPlay();
	getRoundWinner();
}

void GameScreen::startGame()
{
	int monsterIdx = response->getHumanMonster();
	playGame(monsterIdx);
}

void GameScreen::getRoundWinner() 
{
	//Type: water is weak to grass.
	//squirtle -> idx 0;

	//Type: grass is weak to fire.
	//bulbasaur -> idx 1;
	
	//Type: fire is weak to water, resistant to grass.
	//charmander -> idx 2

	//Human plays squirtle (water)
	if (humanSelection == 0)
	{
		//Computer plays bulbasaur (grass): human loses, computer wins.
		if (computerSelection == 1) {
			win_message = response->getHumanName() + " Lost, Computer Won";
			win_tagline = messages[0];
			response->increaseComputerScore(1);
		}

		//Computer plays charmander (fire): human wins, computer loses.
		else if (computerSelection == 2)
		{
			win_message = response->getHumanName() + " Won, Computer Lost";
			win_tagline = messages[2];
			response->increaseHumanScore(1);
		}
		//else it's draw.
		else
		{
			win_message = " It's a Draw";
			win_tagline = messages[3];
		}
	}
	//Human plays Bulbasaur (grass)
	else if (humanSelection == 1)
	{
		//Computer plays squirtle (water): human wins, computer Loses.
		if (computerSelection == 0) 
		{
			win_message = response->getHumanName() + " Won, Computer Lost";
			win_tagline = messages[0];
			response->increaseHumanScore(1);
		}

		//Computer plays charmander (fire): human loses, computer wins.
		else if (computerSelection == 2)
		{
			win_message = response->getHumanName() + " Lost, Computer Won";
			win_tagline = messages[1];
			response->increaseComputerScore(1);
		}
		//else it's draw.
		else
		{
			win_message = " It's a Draw";
			win_tagline = messages[4];
			response->resetScores();
		}		

	}
	//Human plays charmander (fire)
	else if (humanSelection == 2)
	{
		//Computer plays squirtle (water): human Loses, computer wins.
		if (computerSelection == 0)
		{
			win_message = response->getHumanName() + " Lost, Computer Won";
			win_tagline = messages[2];
			response->increaseComputerScore(1);
		}

		//Computer plays bulbasaur (fire): human wins, computer loses.
		else if (computerSelection == 1)
		{
			win_message = response->getHumanName() + "Won, Computer Lost";
			win_tagline = messages[1];
			response->increaseHumanScore(1);
		}
		//else it's draw.
		else
		{
			win_message = " It's a Draw";
			win_tagline = messages[5];
			response->resetScores();
		}
	}
}

GameResponse* GameScreen::run(sf::RenderWindow& app, sf::Font font)
{
	unsigned int screen_width = app.getSize().x;
	bool Running = true;
	float start_x;
	int human_sprite_width, computer_sprite_width;
	
	sf::Event Event;
	
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Text guide, txt_human_name, txt_ai_name, result, tagline; //,
	sf::Text human_monster_name, comp_monster_name, round_text;

	startGame();

	//Type: water
	//Weak to grass.
	sf::Sprite squirtle = monsters[0];
	//Type: grass
	//Weak to fire.
	sf::Sprite bulbasaur = monsters[1];
	//Type: fire
	//Weak to water, resistant to grass.
	sf::Sprite charmander = monsters[2];

	sf::Sprite human_sprite = monsters[humanSelection];
	sf::Sprite computer_sprite = monsters[computerSelection];

	if (!texture.loadFromFile("Images/game-bg.jpg"))
	{
		std::cerr << "Error loading bg.gif" << std::endl;
		response->setNextScreen(-1);
		return response;
	}
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255, 200));

	txt_human_name.setFont(font);
	txt_human_name.setCharacterSize(16);
	txt_human_name.setString(response->getHumanName() + " played");
	txt_human_name.setFillColor(sf::Color(0, 0, 0, 255));
	txt_human_name.setPosition({ 40.f, 20.f });

	txt_ai_name.setFont(font);
	txt_ai_name.setCharacterSize(16);
	txt_ai_name.setString("Computer played");
	txt_ai_name.setFillColor(sf::Color(0, 0, 0, 255));
	start_x = (screen_width / 2) + 60.f;
	txt_ai_name.setPosition({ start_x, 20.f });


	human_monster_name.setFont(font);
	human_monster_name.setCharacterSize(16);
	human_monster_name.setString(monster_names[humanSelection]);
	human_monster_name.setFillColor(sf::Color(0, 0, 0, 255));
	human_monster_name.setPosition({ 20.f, 120.f });

	comp_monster_name.setFont(font);
	comp_monster_name.setCharacterSize(16);
	comp_monster_name.setString(monster_names[computerSelection]);
	comp_monster_name.setFillColor(sf::Color(0, 0, 0, 255));
	start_x = screen_width - 20.f - comp_monster_name.getGlobalBounds().width;
	comp_monster_name.setPosition({ start_x, 120.f });

	round_text.setFont(font);
	round_text.setCharacterSize(16);
	round_text.setString("Round\n" + std::to_string(round) + "/10");
	round_text.setFillColor(sf::Color(0, 0, 0, 255));
	round_text.setPosition({ getStartX(screen_width, round_text), 120.f });
	

	human_sprite_width = human_sprite.getGlobalBounds().width;
	human_sprite.setPosition({ human_monster_name.getGlobalBounds().width + 40.f, 60.f });

	computer_sprite_width = computer_sprite.getGlobalBounds().width;
	computer_sprite.setPosition({ screen_width - comp_monster_name.getGlobalBounds().width
		- computer_sprite.getGlobalBounds().width - 40.f, 60.f });


	result.setFont(font);
	result.setCharacterSize(16);
	result.setString(win_message);
	result.setFillColor(sf::Color(0, 0, 0, 255));
	result.setPosition({ getStartX(screen_width, result), 250.f });

	tagline.setFont(font);
	tagline.setCharacterSize(16);
	tagline.setString(win_tagline);
	tagline.setFillColor(sf::Color(0, 0, 0, 255));
	tagline.setPosition({ getStartX(screen_width, tagline), 290.f });

	squirtle.scale({ 0.4, 0.4 });
	squirtle.setColor(sf::Color(255, 255, 255, 150));
	squirtle.setPosition({ 40.f, 420.f });

	bulbasaur.scale({ 0.4, 0.4 });
	bulbasaur.setColor(sf::Color(255, 255, 255, 150));
	bulbasaur.setPosition({ (screen_width/2) - bulbasaur.getGlobalBounds().width + 20, 420.f });

	charmander.scale({ 0.4, 0.4 });
	charmander.setColor(sf::Color(252, 255, 255, 150));
	charmander.setPosition({ screen_width - charmander.getGlobalBounds().width - 40.f, 420.f });


	guide.setFont(font);
	guide.setCharacterSize(14);
	guide.setString("Use Left/Right Arrow keys to select monster.\nPress Enter key to play next round.");
	guide.setFillColor(sf::Color(235, 155, 20, 255));
	guide.setPosition({ (screen_width / 2) - (guide.getGlobalBounds().width / 2), 550.f });


	int cursor = -1;

	while (Running)
	{
		//Verifying events
		while (app.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				response->setNextScreen(0);
				return response;
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
					response->setNextScreen(0);
					return response;
					break;
				case sf::Keyboard::Up:
					cursor = 0;
					break;
				case sf::Keyboard::Down:
					cursor = 0;
					break;
				case sf::Keyboard::Left:
					cursor = (cursor - 1) % 3;
					break;
				case sf::Keyboard::Right:
					cursor = (cursor + 1) % 3;
					break;
				case sf::Keyboard::Return:
					if (round < 10) {
						if (cursor < 0 || cursor > 2)
							break;

						round++;

						playGame(cursor);

						human_sprite = monsters[humanSelection];
						computer_sprite = monsters[computerSelection];

						human_sprite_width = human_sprite.getGlobalBounds().width;
						human_sprite.setPosition({ human_monster_name.getGlobalBounds().width + 40.f, 60.f });

						computer_sprite_width = computer_sprite.getGlobalBounds().width;
						computer_sprite.setPosition({ screen_width - comp_monster_name.getGlobalBounds().width
							- computer_sprite.getGlobalBounds().width - 40.f, 60.f });

						human_monster_name.setString(monster_names[humanSelection]);
						comp_monster_name.setString(monster_names[computerSelection]);

						round_text.setString("Round\n" + std::to_string(round) + "/10");

						result.setString(win_message);
						result.setPosition({ getStartX(screen_width, result), 250.f });

						tagline.setString(win_tagline);
						tagline.setPosition({ getStartX(screen_width, tagline), 290.f });
					}
					else {
						Running = false;
						response->setNextScreen(2);
						return response;
					}
					break;
				default:
					break;
				}
			}
		}

		if (cursor == 0)
		{
			squirtle.setColor(sf::Color(252, 186, 187, 255));
			bulbasaur.setColor(sf::Color(255, 255, 255, 255));
			charmander.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (cursor == 1)
		{
			squirtle.setColor(sf::Color(255, 255, 255, 255));
			bulbasaur.setColor(sf::Color(252, 186, 187, 255));
			charmander.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (cursor == 2)
		{
			squirtle.setColor(sf::Color(255, 255, 255, 255));
			bulbasaur.setColor(sf::Color(255, 255, 255, 255));
			charmander.setColor(sf::Color(251, 139, 139, 255));
		}

		//Clearing screen
		app.clear(sf::Color(255, 255, 255, 255));
		//Drawing
		app.draw(sprite);		
		app.draw(squirtle);
		app.draw(bulbasaur);
		app.draw(charmander);

		app.draw(human_sprite);
		app.draw(computer_sprite);
		app.draw(guide);
		app.draw(txt_human_name);
		app.draw(txt_ai_name);
		app.draw(human_monster_name);
		app.draw(comp_monster_name);
		app.draw(result);
		app.draw(tagline); 
		app.draw(round_text);
		app.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	response->setNextScreen(-1);
	return response;;
}


