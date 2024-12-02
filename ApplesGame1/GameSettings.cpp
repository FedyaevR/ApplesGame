#include "GameSettings.h"
#include "Game.h"

namespace ApplesGame
{
	bool HasGameMode(int* modes, GameModes mode) 
	{
		return (*modes & static_cast<int>(mode)) != 0;
	}

	void SetupGameMode(Game& game, sf::RenderWindow& window)
	{
		int* selectModes = game.gameSettings.selectModes;

		HandleSettingsInput(window, game);
		
		if (HasGameMode(selectModes, GameModes::WithEndedApples)) {
			game.gameSettings.isEndedApplesTurned = true;
		}
		if (HasGameMode(selectModes, GameModes::WithEndlessApples)) {
			game.gameSettings.isEndedApplesTurned = false;
		}
		if (HasGameMode(selectModes, GameModes::WithPlayerAcceleration)) {
			game.gameSettings.isAccelerationTurned = true;
		}
		if (HasGameMode(selectModes, GameModes::WithoutPlayerAcceleration)) {
			game.gameSettings.isAccelerationTurned = false;
		}
		if (*selectModes == static_cast<int>(GameModes::None)) {
			game.gameSettings.isEndedApplesTurned = false;
			game.gameSettings.isAccelerationTurned = false;
		}
	}

	void HandleSettingsInput(sf::RenderWindow& window, Game& game)
	{
		int input = 0;
		int* selectModes = game.gameSettings.selectModes;

		game.gameSettings.chooseGameModeText = InitGameModeText(game.font);

		window.clear();

		window.draw(game.gameSettings.chooseGameModeText);
		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			input = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			input = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			input = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			input = 4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			game.gameSettings.isGameStart = true;
		}

		switch (input) 
		{
			case 0:
				break; // Без режимов
			case 1:
				*selectModes ^= static_cast<int>(GameModes::WithEndedApples);
				break;
			case 2:
				*selectModes ^= static_cast<int>(GameModes::WithEndlessApples);
				break;
			case 3:
				*selectModes ^= static_cast<int>(GameModes::WithPlayerAcceleration);
				break;
			case 4:
				*selectModes ^= static_cast<int>(GameModes::WithoutPlayerAcceleration);
				break;
			case 5:
				break;
		}
	}

	sf::Text InitGameModeText(const sf::Font& font)
	{
		
			sf::Text text;
			text.setFont(font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(35);

			text.setPosition(SCREEN_WIDTH / 5.f, SCREEN_HEIGHT / 3.f);
			text.setString("Choose game mode: \n1 - With ended apples count;\n2 - With endles apples count;\n3 - With player acceleration;\n4 - Without player acceleration;\n5 - Start game;\n");

			return text;
	}

	void RestartSettings(Game& game)
	{
		game.gameSettings.isGameStart = false;
		game.gameSettings.startSelectMode = 0;
		game.gameSettings.selectModes = &game.gameSettings.startSelectMode;
	}

}
