#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		if (game.gameSettings.isAccelerationTurned)
		{
			player.acceleration = ACCELERATION;
		}
		else
		{
			player.acceleration = 0.f;
		}

		player.direction = PlayerDirection::Right;
		player.sprite.setPosition(player.position.x, player.position.y);
		player.sprite.setTexture(game.playerTexture);

		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void PlayerDraw(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		window.draw(player.sprite);
	}

	bool IsScreenBorder(float position, float playerSpeed, PlayerDirection playerDirection, float deltaTime, Game& game)
	{
		float acceleration = 0.f;
		if (game.gameSettings.isAccelerationTurned)
		{
			acceleration = ACCELERATION;
		}

		float step = (playerSpeed * deltaTime) + (acceleration * deltaTime) + (PLAYER_SIZE / 2.f);

		switch (playerDirection)
		{
		case PlayerDirection::Right:
			if (position + step >= SCREEN_WIDTH)
			{
				return true;
			}

			return false;
			break;
		case PlayerDirection::Up:
			if (position - step <= 0.f)
			{
				return true;
			}

			return false;
			break;
		case PlayerDirection::Left:
			if (position - step <= 0.f)
			{
				return true;
			}

			return false;
			break;
		case PlayerDirection::Down:
			if (position + step >= SCREEN_HEIGHT)
			{
				return true;
			}

			return false;
			break;
		default:
			return false;
			break;
		}
	}
}
