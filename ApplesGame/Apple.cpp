#include "Apple.h"
#include "Game.h"
#include "Math.h"

namespace ApplesGame
{
	int GenerateApplesCount()
	{
		return 5 + rand() % (20 - 5 + 1);
	}

	void AppleInit(Apple* apple, const Game& game)
	{
		(*apple).sprite.setPosition((*apple).position.x, (*apple).position.y);
		(*apple).sprite.setTexture(game.appleTexture);

		SetSpriteSize((*apple).sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin((*apple).sprite, 0.5f, 0.5f);
		DefineScreenPart(apple);
	}

	void InitApples(std::vector<Apple>& apples, const Game& game)
	{
		for (int i = 0; i < game.applesCount; i++)
		{
			apples.emplace_back();
			apples[i].position = GenerateApplePosition();
			AppleInit(&apples[i], game);
		}
	}

	bool IsApplePosition(std::vector<Apple> apples, float positionX, float positionY, int applesCount)
	{
		float appleStartX = 0.f;
		float appleEndX = 0.f;
		float appleStartY = 0.f;
		float appleEndY = 0.f;

		for (int i = 0; i < applesCount; i++)
		{
			appleStartX = apples[i].shape.getPosition().x - APPLE_SIZE / 2.f;
			appleEndX = apples[i].shape.getPosition().x + APPLE_SIZE / 2.f;

			appleStartY = apples[i].shape.getPosition().y - APPLE_SIZE / 2.f;
			appleEndY = apples[i].shape.getPosition().y + APPLE_SIZE / 2.f;

			if (positionX >= appleStartX && positionX <= appleEndX + STONE_WIDTH_MAX)
			{
				return true;
			}
			else if (positionY >= appleStartY && positionY <= appleEndY + STONE_HEIGHT_MAX)
			{
				return true;
			}
		}

		return false;
	}

	Position2D GenerateApplePosition()
	{
		Position2D result;
		result.x = 1 + rand() / (float)(RAND_MAX) * (SCREEN_WIDTH - 1);
		result.y = 1 + rand() / (float)(RAND_MAX) * (SCREEN_HEIGHT - 1);

		return result;
	}

	void AppleDraw(Apple* apple, sf::RenderWindow& window)
	{
		apple->sprite.setPosition(apple->position.x, apple->position.y);
		window.draw(apple->sprite);
	}
}
