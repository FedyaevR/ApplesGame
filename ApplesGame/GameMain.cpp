// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Game.h"
#include "GameStateMainMenu.h"

using namespace ApplesGame;

int main()
{
	sf::sleep(sf::milliseconds(15));

	int seed = (int)time(nullptr);
	srand(seed);

	Game game;
	GameStateMainMenuData gameStateMenu;

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
				game.gameStates.emplace_back();
				game.gameStates.back() = GameState::EscapeDialogMenu;
			}

		}

		if (game.gameStates.back() == GameState::GameStatTableShow)
		{
			DrawGameStat(&game.gameStat, window, game);
		}
		else if (game.gameStates.back() == GameState::MainMenu)
		{
			//SetupGameMode(game, window);
			InitGameStateMainMenu(gameStateMenu, game);
			InitPlayer(game.player, game);
			InitGameStat(&game.gameStat, "Real player", game.score.getString(), window);
		}
		else if(game.gameStates.back() == GameState::Playing)
		{
			GameUpdate(game, deltaTime, window);
			GameDraw(game, window);
		}
		else if (game.gameStates.back() == GameState::EscapeDialogMenu)
		{
			Exit(game, window);
		}
	}

	return 0;
}
