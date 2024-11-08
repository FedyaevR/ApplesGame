#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"

namespace ApplesGame 
{
	enum class PlayerDirection : int
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Game;
	enum class ScreenPart : int;

	struct Player
	{
		const float xStart = SCREEN_WIDTH / 2.f;
		const float yStart = SCREEN_HEIGHT / 2.f;

		float speed = INITIAL_SPEED;
		float acceleration = 0.f;

		Position2D position;
		sf::RectangleShape shape;
		PlayerDirection direction;

		sf::Sprite sprite;

		ScreenPart screenPart;
	};


	void InitPlayer(Player& player, const Game& game);

	void PlayerDraw(Player& player, sf::RenderWindow& window);

	bool IsScreenBorder(float position, float playerSpeed, PlayerDirection playerDirection, float deltaTime, Game& game);
}