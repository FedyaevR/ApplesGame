#include "Stone.h"
#include "Game.h"

namespace ApplesGame
{
	void InitStones(std::vector<Stone>& stones, std::vector<Apple> apples, const Game& game)
	{
		for (int i = 0; i < STONE_COUNT; i++)
		{
			stones.emplace_back();
			InitStone(apples, stones[i], game);
		}
	}

	void InitStone(std::vector<Apple> apples, Stone& stone, const Game& game)
	{
		sf::RectangleShape shape;

		float width = 10 + rand() / (float)(RAND_MAX) * (STONE_WIDTH_MAX - 10);
		float height = 10 + rand() / (float)(RAND_MAX) * (STONE_HEIGHT_MAX - 10);

		float positionX = 0.f;
		float positionY = 0.f;

		while (true)
		{
			positionX = 5 + rand() / (float)(RAND_MAX) * (SCREEN_WIDTH - 5);
			positionY = 5 + rand() / (float)(RAND_MAX) * (SCREEN_HEIGHT - 5);

			//Если не совпадает с позицией яблока - выходим из цикла
			if (IsApplePosition(apples, positionX, positionY, game.applesCount) == false)
			{
				break;
			}
		}

		stone.sprite.setPosition(positionX, positionY);
		stone.sprite.setTexture(game.stoneTexture);

		SetSpriteSize(stone.sprite, width, height);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);

		stone.position.x = positionX;
		stone.position.y = positionY;
		stone.shape.setSize({ width - 5.f, height - 5.f });
	}

	bool IsStoneTouched(sf::RectangleShape player, std::vector<Stone> stones)
	{
		for (int i = 0; i < STONE_COUNT; i++)
		{
			float scaleX = stones[i].sprite.getScale().x;
			float scaleY = stones[i].sprite.getScale().y;

			float dx = fabs(player.getPosition().x - stones[i].position.x);
			float dy = fabs(player.getPosition().y - stones[i].position.y);

			float stoneSize = stones[i].shape.getSize().x * stones[i].shape.getSize().y;

			if (dx <= (stones[i].shape.getSize().x + PLAYER_SIZE) / 2.f &&
				dy <= (stones[i].shape.getSize().y + PLAYER_SIZE) / 2.f)
			{
				return true;
			}
		}

		return false;
	}

	void StoneDraw(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.position.x, stone.position.y);
		window.draw(stone.sprite);
	}
}
