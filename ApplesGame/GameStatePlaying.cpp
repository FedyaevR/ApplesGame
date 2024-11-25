#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{	
		// Init game resources (terminate if error)
		assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// Init player
		InitPlayer(data.player, data.playerTexture);

		// Init apples
		data.apples.clear();
		ClearApplesGrid(data.applesGrid);
		int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.appleTexture);
			ResetAppleState(apple);
			AddAppleToGrid(data.applesGrid, apple);
		}

		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to exit");
		data.inputHintText.setOrigin(GetItemOrigin(data.inputHintText, { 1.f, 0.f }));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			data.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			data.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			data.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			data.player.direction = PlayerDirection::Left;
		}

		// Update player
		UpdatePlayer(data.player, timeDelta);

		Apple* collidingApples[MAX_APPLES_IN_CELL] = { nullptr };
		int numCollidingApples = 0;

		if (FindPlayerCollisionWithApples(data.player.position, data.applesGrid, collidingApples, numCollidingApples))
		{
			for (int i = 0; i < numCollidingApples; i++)
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples)
				{
					// Move apple to a new random position
					ResetAppleState(*collidingApples[i]);
					AddAppleToGrid(data.applesGrid, *collidingApples[i]);
				}
				else
				{
					// Mark apple as eaten
					MarkAppleAsEaten(*collidingApples[i]);
					RemoveAppleFromGrid(data.applesGrid, *collidingApples[i]);
				}

				// Increase eaten apples counter
				data.numEatenApples++;
				// Increase player speed
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration)
				{
					data.player.speed += ACCELERATION;
				}
			}
		}

		bool isGameFinished = (data.numEatenApples == data.apples.size())
			&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);
		// Check collision with screen border
		if (isGameFinished || HasPlayerCollisionWithScreenBorder(data.player))
		{
			// Find player in records table and update his score
			for (RecordsTableItem& item : game.recordsTable)
			{
				if (item.name == "You")
				{
					item.score = data.numEatenApples;
					break;
				}
			}

			// Sort records table
			std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));

			PushGameState(game, GameStateType::GameOver, false);
		}
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(data.player, window);
		// Draw apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}

		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}
