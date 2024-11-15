#include "Game.h"
#include "GameStat.h"

namespace ApplesGame
{
	void GameUpdate(Game& game, float deltaTime, sf::RenderWindow& window)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.player.direction = PlayerDirection::Right;
			if (IsScreenBorder(game, window, deltaTime, game.player.direction) == false)
			{
				game.player.position.x += game.player.speed * deltaTime;
			}

			RotateSprite(game.player.sprite, game.player.direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
			if (IsScreenBorder(game, window, deltaTime, game.player.direction) == false)
			{
				game.player.position.y -= game.player.speed * deltaTime;
			}

			RotateSprite(game.player.sprite, game.player.direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
			if (IsScreenBorder(game, window, deltaTime, game.player.direction) == false)
			{
				game.player.position.x -= game.player.speed * deltaTime;
			}

			RotateSprite(game.player.sprite, game.player.direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
			if (IsScreenBorder(game, window, deltaTime, game.player.direction) == false)
			{
				game.player.position.y += game.player.speed * deltaTime;
			}

			RotateSprite(game.player.sprite, game.player.direction);
		}

		DefineScreenPart(game.player);
		AppleEat(game, window);
		StoneCheck(game, window);

		game.player.shape.setPosition(game.player.position.x, game.player.position.y);
	}

	void GameDraw(Game& game, sf::RenderWindow& window)
	{
		window.clear();

		PlayerDraw(game.player, window);

		window.draw(game.score);
		
		for(int i = 0; i < game.applesCount; i++)
		{ 
			AppleDraw(&game.apples[i], window);
		}

		for (int i = 0; i < STONE_COUNT; i++)
		{
			StoneDraw(game.stones[i], window);
		}

		window.display();
	}

	void RestartGame(sf::Text& text, sf::RenderWindow& window, Game& game)
	{
		window.clear();
		window.draw(text);

		window.display();

		sf::sleep(sf::seconds(1.0f));
		text.setString("");

		game.gameStates.emplace_back();
		game.gameStates.back() = GameState::GameStatTableShow;

		UpdatePlayer(&game.gameStat, game.appleEatenCount);
	}

	sf::Text InitScore(const sf::Font& font)
	{
		sf::Text score;
		score.setFont(font);
		score.setFillColor(sf::Color::White);
		score.setCharacterSize(55);

		score.setPosition(SCREEN_WIDTH / 2.f, -5.f);
		score.setString("0");

		return score;
	}

	sf::Text GameOver(const sf::Font& font, Game& game)
	{
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(85);

		text.setPosition(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 3.f);
		text.setString("GAME OVER");

		game.gameOverSound.play();

		return text;
	}

	sf::Text WinText(const sf::Font& font, Game& game)
	{
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::Green);
		text.setCharacterSize(85);

		text.setPosition(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 3.f);
		text.setString("YOU WIN!");

		return text;
	}

	sf::Text ShowEscapeText(const sf::Font& font, Game& game)
	{
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(45);

		text.setPosition(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 3.f);
		text.setString("You want to exit?\n\tYes = 1\tNo = 2");

		return text;
	}

	void Exit(Game& game, sf::RenderWindow& window)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			game.gameStates.pop_back();
		}

		sf::Text text = ShowEscapeText(game.font, game);
		window.clear();
		window.draw(text);

		window.display();
	}

	bool IsScreenBorder(Game& game, sf::RenderWindow& window, float deltaTime, PlayerDirection direction)
	{
		if (direction == PlayerDirection::Right || direction == PlayerDirection::Left)
		{
			if (IsScreenBorder(game.player.position.x, game.player.speed, game.player.direction, deltaTime, game) == false)
			{
				return false;
			}
		}

		if (direction == PlayerDirection::Up || direction == PlayerDirection::Down)
		{
			if (IsScreenBorder(game.player.position.y, game.player.speed, game.player.direction, deltaTime, game) == false)
			{
				return false;
			}
		}

		RestartSettings(game);
		
		InitStones(game.stones, game.apples, game);

		InitApples(game.apples, game);
		game.score.setString("0");

		game.player.position = { game.player.xStart, game.player.yStart };
		InitPlayer(game.player, game);

		game.text = GameOver(game.font, game);
		RestartGame(game.text, window, game);

		game.appleEatenCount = 0;
		game.player.speed = INITIAL_SPEED;

		return true;
	}

	void AppleEat(Game& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < game.applesCount; i++)
		{ 
			if (game.apples[i].screenPart != game.player.screenPart)
			{
				continue;
			}

			float squareDistance = (game.player.position.x - game.apples[i].position.x) * (game.player.position.x - game.apples[i].position.x) + (game.player.position.y - game.apples[i].position.y) * (game.player.position.y - game.apples[i].position.y);
			float squareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;

			if (squareDistance <= squareRadiusSum)
			{
				game.appleEatenCount++;
				game.player.speed += game.player.acceleration;
				game.appleEatSound.play();

				std::string appleEatenCountStr = std::to_string(game.appleEatenCount);

				game.score.setString(appleEatenCountStr);

				if (game.gameSettings.isEndedApplesTurned == false)
				{
					game.apples[i].position = GenerateApplePosition();
					AppleInit(&game.apples[i], game);
				}
				else 
				{
					game.apples[i].position.x = -100000.f;
					game.apples[i].position.y = -100000.f;
					if (game.appleEatenCount == game.applesCount)
					{
						RestartSettings(game);

						InitStones(game.stones, game.apples, game);
						InitApples(game.apples, game);

						game.score.setString("0");

						game.player.position = { game.player.xStart, game.player.yStart };
						InitPlayer(game.player, game);

						sf::Text text = WinText(game.font, game);
						RestartGame(text, window, game);

						game.appleEatenCount = 0;
						game.player.speed = INITIAL_SPEED;
					}
				}
			}
		}
	}

	void StoneCheck(Game& game, sf::RenderWindow& window)
	{
		if (IsStoneTouched(game.player.shape, game.stones))
		{
			RestartSettings(game);

			InitStones(game.stones, game.apples, game);
			InitApples(game.apples, game);

			game.score.setString("0");

			game.player.position = { game.player.xStart, game.player.yStart };
			InitPlayer(game.player, game);

			game.text = GameOver(game.font, game);
			RestartGame(game.text, window, game);

			game.appleEatenCount = 0;
			game.player.speed = INITIAL_SPEED;
		}
	}
}