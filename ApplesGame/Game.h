#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "GameStat.h"

namespace ApplesGame
{
	int GenerateApplesCount();
	sf::Text InitScore(const sf::Font& font);

	enum class ScreenPart : int
	{
		LeftTop = 0,
		LeftCenter,
		LeftBottom,
		MiddleTop,
		MiddleCenter,
		MiddleBottom,
		RightTop,
		RightCenter,
		RightBottom
	};

	struct Game
	{
		Player player;

		GameModes gameModes;
		GameSettings gameSettings;
		GameStat gameStat;


		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		sf::SoundBuffer appleEatBuffer;
		sf::SoundBuffer gameOverBuffer;

		sf::Sound appleEatSound;
		sf::Sound gameOverSound;


		int appleEatenCount = 0;

		std::vector<Apple> apples;
		int applesCount;

		std::vector<Stone> stones;

		sf::Font font;

		sf::Text score;
		sf::Text text;

		Game()
		{
			assert(playerTexture.loadFromFile(RESOURCES_PATH + "\Player.png"));
			assert(appleTexture.loadFromFile(RESOURCES_PATH + "\Apple.png"));
			assert(stoneTexture.loadFromFile(RESOURCES_PATH + "\Rock.png"));

			assert(appleEatBuffer.loadFromFile(RESOURCES_PATH + "\AppleEat.wav"));
			assert(gameOverBuffer.loadFromFile(RESOURCES_PATH + "\Death.wav"));

			appleEatSound.setBuffer(appleEatBuffer);
			gameOverSound.setBuffer(gameOverBuffer);

			player.position = { player.xStart, player.yStart };
			player.direction = PlayerDirection::Right;

			font.loadFromFile("konstantinopel.ttf");
			score = InitScore(font);

			applesCount = GenerateApplesCount();
			apples.reserve(applesCount);

			InitApples(apples, *this);

			stones.reserve(STONE_COUNT);
			InitStones(stones, apples, *this);
		}
	};

	void GameUpdate(Game& game, float deltaTime, sf::RenderWindow& window);

	void GameDraw(Game& game, sf::RenderWindow& window);

	void RestartGame(sf::Text& text, sf::RenderWindow& window, Game& game);

	sf::Text GameOver(const sf::Font& font, Game& game);

	bool IsScreenBorder(Game& game, sf::RenderWindow& window, float deltaTime, PlayerDirection direction);

	void AppleEat(Game& game, sf::RenderWindow& window);
	void StoneCheck(Game& game, sf::RenderWindow& window);
}