#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"

namespace ApplesGame
{
	struct Game;
	enum class ScreenPart : int;

	struct Apple
	{
		Position2D position;
		sf::CircleShape shape;

		sf::Sprite sprite;

		ScreenPart screenPart;
	};


	void AppleInit(Apple* apple, const Game& game);

	void InitApples(Apple* apples, const Game& game);

	bool IsApplePosition(Apple* apples, float positionX, float positionY, int applesCount);

	Position2D GenerateApplePosition();

	void AppleDraw(Apple* apple, sf::RenderWindow& window);
}