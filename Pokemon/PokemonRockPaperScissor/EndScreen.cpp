
#include <string>
#include <SFML/Graphics.hpp>

#include "EndScreen.h"

EndScreen::EndScreen(sf::Sprite _monsters[3], GameResponse* _response)
{
	response = _response;
	message = "";
}


void EndScreen::saveEndMessage()
{
	if (response->getComputerScore() > response->getHumanScore())
		message = response->getHumanName() + ", you are a real champ. Thank you for losing";
	else if (response->getComputerScore() < response->getHumanScore())
		message = "Congratulation " + response->getHumanName() + ". You won";
	else
		message = "After all those tries you still draw with a machine";
}

GameResponse* EndScreen::run(sf::RenderWindow& app, sf::Font font)
{
	sf::Event event;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Text exit_option, title, message_txt;
	sf::Text player_name, player_score, computer_score, status;

	unsigned int screen_width = app.getSize().x;
	float start_x;
	bool Running = true;

	saveEndMessage();

	if (!texture.loadFromFile("Images/presentation.png"))
	{
		std::cerr << "Error loading presentation.gif" << std::endl;
		response->setNextScreen(-1);
		return response;
	}
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255, 255));

	title.setFont(font);
	title.setCharacterSize(24);
	title.setString("Game Over");
	title.setFillColor(sf::Color(252, 216, 0, 255));

	start_x = calcStartX(title, screen_width);
	title.setPosition({ start_x, 45.f });

	player_name.setFont(font);
	player_name.setCharacterSize(16);
	player_name.setString(response->getHumanName());
	player_name.setFillColor(sf::Color(0, 0, 0, 255));

	start_x = (screen_width / 2) + 10.f;
	player_name.setPosition({ start_x, 120.f });

	sf::RectangleShape name_bg(sf::Vector2f(145.f, 25.f));
	name_bg.setFillColor(sf::Color(192, 192, 192, 255));
	name_bg.setOutlineThickness(1.f);

	player_score.setFont(font);
	player_score.setCharacterSize(24);
	player_score.setString(response->getHumanName() + " scored " + std::to_string(response->getHumanScore()));
	player_score.setFillColor(sf::Color(192, 192, 192, 255));
	player_score.setPosition({ getStartX(screen_width, player_score), 150.f });

	computer_score.setFont(font);
	computer_score.setCharacterSize(24);
	computer_score.setString("Computer scored " + std::to_string(response->getComputerScore()));
	computer_score.setFillColor(sf::Color(192, 192, 192, 255));

	start_x += 10.f + player_score.getLocalBounds().width;
	computer_score.setPosition({ getStartX(screen_width, computer_score), 190.f });

	message_txt.setFont(font);
	message_txt.setCharacterSize(16);
	message_txt.setString(message);
	message_txt.setFillColor(sf::Color(192, 192, 192, 255));
	message_txt.setPosition({ getStartX(screen_width, message_txt), 260.f });


	status.setFont(font);
	status.setCharacterSize(14);
	status.setString("Press Enter key to exit");
	status.setFillColor(sf::Color(253, 223, 0, 255));
	status.setPosition({ (screen_width / 2) - (status.getGlobalBounds().width / 2), 550.f });

	exit_option.setFont(font);
	exit_option.setCharacterSize(20);
	exit_option.setString("Exit");
	exit_option.setFillColor(sf::Color(255, 0, 0, 255));

	start_x = screen_width - 50.f - exit_option.getLocalBounds().width;
	exit_option.setPosition({ start_x, 550.f });

	int cursor = 0;

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

			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					//exit
					response->setNextScreen(-1);
					return response;
				}
			}
		}
		
		sprite.setColor(sf::Color(255, 255, 255, 200));

		//Clearing screen
		app.clear();
		//Drawing
		app.draw(sprite);
		app.draw(title);	
		app.draw(player_name);
		app.draw(player_score);
		app.draw(computer_score);
		app.draw(message_txt);
		app.draw(exit_option);
		app.draw(status);

		app.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	response->setNextScreen(-1);
	return response;
}