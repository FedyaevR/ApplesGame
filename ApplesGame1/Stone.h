#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"
#include "Apple.h"

namespace ApplesGame
{
	struct Stone
	{
		Position2D position;
		sf::RectangleShape shape;

		sf::Sprite sprite;
	};
	
	struct Game;

	void InitStones(Stone stones[STONE_COUNT], Apple apples[APPLES_COUNT], const Game& game);

	void InitStone(Apple apples[APPLES_COUNT], Stone& stone, const Game& game);

	bool IsStoneTouched(sf::RectangleShape player, Stone stones[STONE_COUNT]);

	void StoneDraw(Stone& stone, sf::RenderWindow& window);
}
