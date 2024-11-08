#pragma once
#include "GameSettings.h"

namespace sf 
{
	class Sprite;
}

namespace ApplesGame
{
	const float LEFT_WIDTH_BORDER = SCREEN_WIDTH / 3.f;
	const float MIDDLE_WIDTH_BORDER = SCREEN_WIDTH / 1.5f;
	const float RIGHT_WIDTH_BORDER = SCREEN_WIDTH / 0.5f;

	const float Y_TOP_BORDER = SCREEN_HEIGHT / 3.f;
	const float Y_CENTER_BORDER = SCREEN_HEIGHT / 1.5f;
	const float Y_BOTTOM_BORDER = SCREEN_HEIGHT / 0.5f;


	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	struct Player;
	struct Apple;

	typedef Vector2D Position2D;
	enum class PlayerDirection: int;

	void SetSpriteSize(sf::Sprite& sprite, float desiredWIdth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	void RotateSprite(sf::Sprite& sprite, PlayerDirection direction);
	void DefineScreenPart(Player& player);
	void DefineScreenPart(Apple* apple);
	int CheckYPosition(float y);
}
