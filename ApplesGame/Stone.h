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

	void InitStones(std::vector<Stone>& stones, std::vector<Apple> apples, const Game& game);

	void InitStone(std::vector<Apple> apples, Stone& stone, const Game& game);

	bool IsStoneTouched(sf::RectangleShape player, std::vector<Stone> stones);

	void StoneDraw(Stone& stone, sf::RenderWindow& window);
}
