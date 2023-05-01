
#include <string>
#include <SFML/Graphics.hpp>

#include "StartScreen.h"

StartScreen::StartScreen(sf::Sprite _monsters[3], GameResponse* _response)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
	playerMonsterIndex = 0;
	for (int i = 0; i < 3; i++)
	{
		monsters[i] = _monsters[i];
	}
	response = _response;

}


bool StartScreen::isAlpha(sf::Uint32 ch)
{
	if ((ch > 96 && ch < 123) || (ch > 64 && ch < 91) || ch == 32) {
		return true;
	}
	return false;
}

GameResponse* StartScreen::run(sf::RenderWindow& app, sf::Font font)
{
	sf::Event event;

	sf::Texture texture;
	sf::Sprite sprite;
	
	sf::Text play_option, exit_option, continue_option;
	sf::Text welcome_msg, title, gender_prompt, name_prompt;
	sf::Text player_name, boy, girl, status;
	
	sf::Sprite squirtle = monsters[0];
	sf::Sprite bulbasaur = monsters[1]; 
	sf::Sprite charmander = monsters[2];

	sf::String name_input = "";
	sf::String gender = "";

	sf::Color *object_colors[4][3];
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			object_colors[row][col] = nullptr;
		}
	}

	bool Running = true;
	int horizontal_idx[4] = { 0, 0, 0, 0 };
	int alpha = 0, vertical = 0, horizontal = 0;
	unsigned int screen_width = app.getSize().x;
	float start_x;


	if (!texture.loadFromFile("Images/bg.jpg"))
	{
		std::cerr << "Error loading bg.gif" << std::endl;
		response->setNextScreen(-1);
		return response;
	}
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255, alpha));

	squirtle.setPosition({ 20.f, 300.f });
	bulbasaur.setPosition({ 270.f, 200.f });
	charmander.setPosition({ screen_width - 250.f, 300.f });

	welcome_msg.setFont(font);
	welcome_msg.setCharacterSize(20);
	welcome_msg.setString("Welcome to");
	welcome_msg.setFillColor(sf::Color(235, 155, 20, 255));

	start_x = calcStartX(welcome_msg, screen_width);
	welcome_msg.setPosition({ start_x, 10.f });

	title.setFont(font);
	title.setCharacterSize(24);
	title.setString("Pokemon Rock Paper Sciscor");
	title.setFillColor(sf::Color(243, 162, 9, 255));

	start_x = calcStartX(title, screen_width);
	title.setPosition({ start_x, 45.f });

	name_prompt.setFont(font);
	name_prompt.setCharacterSize(14);
	name_prompt.setString("What is your name?");
	name_prompt.setFillColor(sf::Color(149, 122, 0, 255));

	start_x = (screen_width / 2) - name_prompt.getLocalBounds().width - 10.f;
	name_prompt.setPosition({ start_x, 120.f });

	gender_prompt.setFont(font);
	gender_prompt.setCharacterSize(14);
	gender_prompt.setString("What is your gender?");
	gender_prompt.setFillColor(sf::Color(149, 122, 0, 255));

	start_x = (screen_width / 2) - gender_prompt.getLocalBounds().width - 10.f;
	gender_prompt.setPosition({ start_x, 160.f });

	player_name.setFont(font);
	player_name.setCharacterSize(16);
	player_name.setString(response->getHumanName());
	player_name.setFillColor(sf::Color(0, 0, 0, 255));

	start_x = (screen_width / 2) + 10.f;
	player_name.setPosition({ start_x, 120.f });

	sf::RectangleShape name_bg(sf::Vector2f(145.f, 25.f));
	name_bg.setFillColor(sf::Color(192, 192, 192, 255));
	name_bg.setOutlineThickness(1.f);

	boy.setFont(font);
	boy.setCharacterSize(16);
	boy.setString("Boy");
	boy.setFillColor(sf::Color(239, 253, 93, 255));
	boy.setPosition({ start_x, 160.f });

	girl.setFont(font);
	girl.setCharacterSize(16);
	girl.setString("Girl?");
	girl.setFillColor(sf::Color(239, 253, 93, 255));

	start_x += 10.f + boy.getLocalBounds().width;
	girl.setPosition({ start_x, 160.f });

	status.setFont(font);
	status.setCharacterSize(14);
	status.setString("Use Arrow keys to move and select option.\nEnter when 'Play' is seleted to start Game");
	status.setFillColor(sf::Color(253, 223, 0, 255));
	status.setPosition({ (screen_width / 2) - (status.getGlobalBounds().width / 2), 550.f });

	start_x = 50.f;
	play_option.setFont(font);
	play_option.setCharacterSize(20);
	play_option.setString("Play");
	play_option.setPosition({ start_x, 550.f });

	exit_option.setFont(font);
	exit_option.setCharacterSize(20);
	exit_option.setString("Exit");

	start_x = screen_width - 50.f - exit_option.getLocalBounds().width;
	exit_option.setPosition({ start_x, 550.f });

	start_x = 50.f;
	continue_option.setFont(font);
	continue_option.setCharacterSize(20);
	continue_option.setString("Continue");
	continue_option.setPosition({ start_x, 550.f });

	if (playing)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		//Verifying events
		while (app.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				response->setNextScreen(-1);
				return response;;
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (vertical == 0 && horizontal == 0)
				{
					//If alphabet characters
					if (isAlpha(event.text.unicode)) 
					{
						name_input += event.text.unicode;
						player_name.setString(" " + name_input);
					}
				}				
			}
			
			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (vertical > 0)
						vertical--;
					horizontal = 0;

					object_colors[vertical][horizontal] = new sf::Color(255, 0, 0, 150);
					break;
				case sf::Keyboard::Down:
					if (vertical < 3)
						vertical++;
					horizontal = 0;
					break;
				case sf::Keyboard::Left:
					if (vertical != 0 && horizontal > 0) 
					{
						horizontal--;
					}
					horizontal_idx[vertical] = horizontal;
					break;
				case sf::Keyboard::Right:
					if (vertical == 2 && horizontal < 2)
						horizontal++;
					else if (vertical != 0 && horizontal == 0)
					{
						horizontal = 1;
					}
					horizontal_idx[vertical] = horizontal;
					break;
				case sf::Keyboard::Return:
					if (vertical == 3)
					{
						if (horizontal == 0)
						{
							if (player_name.getString().isEmpty())
							{
								status.setString("Please enter your name");
								status.setPosition({ (screen_width / 2) - (status.getGlobalBounds().width / 2), 550.f });
							}
							else if (gender.isEmpty()) 
							{
								status.setString("Please select your gender");
								status.setPosition({ (screen_width / 2) - (status.getGlobalBounds().width / 2), 550.f });
							}
							else 
							{
								//Start game
								playing = true;

								response->setHumanMonster(playerMonsterIndex);
								response->setHumanName(player_name.getString());
								response->setNextScreen(1);

								return response;
							}
						}
						else
						{
							//exit
							response->setNextScreen(-1);
							return response;;
						}
					}
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha < alpha_max)
		{
			alpha++;
		}
		sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
		if (vertical == 0)
		{
			name_bg.setOutlineColor(sf::Color(255, 0, 0, 255));
			boy.setFillColor(sf::Color(239, 253, 93, 255));
			girl.setFillColor(sf::Color(239, 253, 93, 255));
			play_option.setFillColor(sf::Color(255, 255, 255, 255));
			exit_option.setFillColor(sf::Color(255, 255, 255, 255));
			continue_option.setFillColor(sf::Color(255, 255, 255, 255));
			squirtle.setColor(sf::Color(255, 255, 255, 255));
			bulbasaur.setColor(sf::Color(255, 255, 255, 255));
			charmander.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (vertical == 1)
		{
			if (horizontal_idx[vertical] == 0)
			{
				boy.setFillColor(sf::Color(255, 0, 0, 255));
				girl.setFillColor(sf::Color(239, 253, 93, 255));
				gender = "Boy";
			}
			else
			{
				boy.setFillColor(sf::Color(239, 253, 93, 255));
				girl.setFillColor(sf::Color(255, 0, 0, 255));
				gender = "Girl";
			}

			name_bg.setOutlineColor(sf::Color(255, 255, 255, 255));
			//play_option.setFillColor(sf::Color(255, 255, 255, 255));
			//exit_option.setFillColor(sf::Color(255, 255, 255, 255));
			//continue_option.setFillColor(sf::Color(255, 255, 255, 255));
			//squirtle.setColor(sf::Color(255, 255, 255, 255));
			//bulbasaur.setColor(sf::Color(255, 255, 255, 255));
			//charmander.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (vertical == 2)
		{
			if (horizontal_idx[vertical] == 0)
			{
				squirtle.setColor(sf::Color(252, 186, 187, 255));
				bulbasaur.setColor(sf::Color(255, 255, 255, 255));
				charmander.setColor(sf::Color(255, 255, 255, 255));
				playerMonsterIndex = 0;
			}
			else if (horizontal_idx[vertical] == 1)
			{
				squirtle.setColor(sf::Color(255, 255, 255, 255));
				bulbasaur.setColor(sf::Color(252, 186, 187, 255));
				charmander.setColor(sf::Color(255, 255, 255, 255));
				playerMonsterIndex = 1;
			}
			else
			{
				squirtle.setColor(sf::Color(255, 255, 255, 255));
				bulbasaur.setColor(sf::Color(255, 255, 255, 255));
				charmander.setColor(sf::Color(252, 186, 187, 255));
				playerMonsterIndex = 2;
			}

			name_bg.setOutlineColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			name_bg.setOutlineColor(sf::Color(255, 255, 255, 255));

			if (horizontal_idx[vertical] == 0)
			{
				play_option.setFillColor(sf::Color(255, 0, 0, 255));
				exit_option.setFillColor(sf::Color(255, 255, 255, 255));
				continue_option.setFillColor(sf::Color(255, 0, 0, 255));
			}
			else
			{
				play_option.setFillColor(sf::Color(255, 255, 255, 255));
				exit_option.setFillColor(sf::Color(255, 0, 0, 255));
				continue_option.setFillColor(sf::Color(255, 255, 255, 255));
			}
		}

		//Clearing screen
		app.clear();
		//Drawing
		app.draw(sprite);
		app.draw(squirtle);
		app.draw(bulbasaur);
		app.draw(charmander);
		
		if (alpha == alpha_max)
		{
			if (playing)
			{
				app.draw(continue_option);
			}
			else
			{
				app.draw(play_option);
			}
			app.draw(exit_option);
			app.draw(welcome_msg);
			app.draw(title);
			app.draw(gender_prompt);
			app.draw(name_prompt);
			app.draw(name_bg, player_name.getTransform());
			app.draw(player_name);
			app.draw(boy);
			app.draw(girl);
			app.draw(status);		

		}
		app.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	response->setNextScreen(-1);
	return response;
}