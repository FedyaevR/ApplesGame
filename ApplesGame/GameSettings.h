#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{

	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 20.f;
	const float PLAYER_SIZE = 20.f;

	const float APPLE_SIZE = 20.f;
	const int APPLES_COUNT = 20;

	const int STONE_COUNT = 5;
	const float STONE_HEIGHT_MAX = 50.f;
	const float STONE_WIDTH_MAX = 40.f;

	enum class GameModes : int
	{
		None = 0,
		WithEndedApples = 1 << 0,
		WithEndlessApples = 1 << 1,
		WithPlayerAcceleration = 1 << 2,
		WithoutPlayerAcceleration = 1 << 3
	};

	struct GameSettings
	{
		sf::Text chooseGameModeText;
		int* selectModes;
		int startSelectMode = 0;
		bool isAccelerationTurned = false;
		bool isEndedApplesTurned = false;
		bool isGameStart = false;

		GameSettings()
		{
			selectModes = &startSelectMode;
		}
	};

	struct Game;

	bool HasGameMode(int* modes, GameModes mode);

	void SetupGameMode(Game& game, sf::RenderWindow& window);

	void HandleSettingsInput(sf::RenderWindow& window, Game& game);

	sf::Text InitGameModeText(const sf::Font& font);

	void RestartSettings(Game& game);
}