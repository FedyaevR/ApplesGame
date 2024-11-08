#include "Math.h"
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Game.h"
#include "Player.h"
#include "Apple.h"
#include <iostream>

namespace ApplesGame
{
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		//Формула рассчета размера спрайта X = L / M. Где X - масштаб, L - требуемый размер, M - текущий размер
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };

		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();

		//Относительно левой верхней точки нужно сместить origin. Берем текущий размер и умножаем на относительные значения
		sprite.setOrigin(spriteRect.width * originX, spriteRect.height * originY);
	}

	void RotateSprite(sf::Sprite& sprite, PlayerDirection direction)
	{
		if (direction == PlayerDirection::Left )
		{
			SetSpriteSize(sprite, -PLAYER_SIZE, PLAYER_SIZE);
			sprite.setRotation(0.f);
		}
		else
		{
			SetSpriteSize(sprite, PLAYER_SIZE, PLAYER_SIZE);
			sprite.setRotation((float)direction * -90.f); 
		}
	}

	void DefineScreenPart(Player& player)
	{
		if (player.position.x > 0 && player.position.x <= LEFT_WIDTH_BORDER)
		{
			switch (CheckYPosition(player.position.y))
			{
				case 0:
					player.screenPart = ScreenPart::LeftTop;
					break;
				case 1:
					player.screenPart = ScreenPart::LeftCenter;
					break;
				case 2:
					player.screenPart = ScreenPart::LeftBottom;
					break;
			}
		}
		else if (player.position.x > LEFT_WIDTH_BORDER && player.position.x <= MIDDLE_WIDTH_BORDER)
		{
			switch (CheckYPosition(player.position.y))
			{
			case 0:
				player.screenPart = ScreenPart::MiddleTop;
				break;
			case 1:
				player.screenPart = ScreenPart::MiddleCenter;
				break;
			case 2:
				player.screenPart = ScreenPart::MiddleBottom;
				break;
			}
		}
		else if (player.position.x > MIDDLE_WIDTH_BORDER)
		{
			switch (CheckYPosition(player.position.y))
			{
			case 0:
				player.screenPart = ScreenPart::RightTop;
				break;
			case 1:
				player.screenPart = ScreenPart::RightCenter;
				break;
			case 2:
				player.screenPart = ScreenPart::RightBottom;
				break;
			}
		}
	}

	void DefineScreenPart(Apple* apple)
	{
		if (apple->position.x > 0 && apple->position.x <= LEFT_WIDTH_BORDER)
		{
			switch (CheckYPosition(apple->position.y))
			{
			case 0:
				apple->screenPart = ScreenPart::LeftTop;
				break;
			case 1:
				apple->screenPart = ScreenPart::LeftCenter;
				break;
			case 2:
				apple->screenPart = ScreenPart::LeftBottom;
				break;
			}
		}
		else if (apple->position.x > LEFT_WIDTH_BORDER && apple->position.x <= MIDDLE_WIDTH_BORDER)
		{
			switch (CheckYPosition(apple->position.y))
			{
			case 0:
				apple->screenPart = ScreenPart::MiddleTop;
				break;
			case 1:
				apple->screenPart = ScreenPart::MiddleCenter;
				break;
			case 2:
				apple->screenPart = ScreenPart::MiddleBottom;
				break;
			}
		}

		if (apple->position.x > MIDDLE_WIDTH_BORDER)
		{
			switch (CheckYPosition(apple->position.y))
			{
			case 0:
				apple->screenPart = ScreenPart::RightTop;
				break;
			case 1:
				apple->screenPart = ScreenPart::RightCenter;
				break;
			case 2:
				apple->screenPart = ScreenPart::RightBottom;
				break;
			}
		}
	}

	/// <summary>
	/// Определение высоты обьекта
	/// </summary>
	/// <param name="y"> координата обьекта в данный момент</param>
	/// <returns>0 - Верхняя граница, 1 - Центральная граница, 2 - Нижняя граница, -1 - Нет совпадений</returns>
	int CheckYPosition(float y)
	{
		if (y > 0 && y <= Y_TOP_BORDER)
		{
			return 0;
		}
		else if (y < Y_BOTTOM_BORDER && y <= Y_CENTER_BORDER)
		{
			return 1;
		}
		else if (y < SCREEN_HEIGHT && y <= Y_BOTTOM_BORDER)
		{
			return 2;
		}

		return -1;
	}
}
