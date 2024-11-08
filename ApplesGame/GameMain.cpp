// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Game.h"

using namespace ApplesGame;

int main()
{
	sf::sleep(sf::milliseconds(15));

	int seed = (int)time(nullptr);
	srand(seed);

	Game game;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples games!");

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime; 

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}

		}

		if (game.gameStat.isTableShow)
		{
			DrawGameStat(&game.gameStat, window);
			
		}
		else if (game.gameSettings.isGameStart == false)
		{
			SetupGameMode(game, window);
			InitPlayer(game.player, game);
			InitGameStat(&game.gameStat, "Real player", game.score.getString(), window);
		}
		else 
		{
			GameUpdate(game, deltaTime, window);
			GameDraw(game, window);
		}
	}

	delete[] game.apples;

	return 0;
}
