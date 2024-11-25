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

	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return 
		{
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		// Calculate total height/width of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		totalRect.left = position.x - origin.x * totalRect.width;
		totalRect.top = position.y - origin.y * totalRect.height;
		sf::Vector2f currentPos = { totalRect.left, totalRect.top };

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();
			sf::Vector2f itemOrigin;

			if (orientation == Orientation::Horizontal)
			{
				itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				itemOrigin.x = 0.f;
				currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
			}
			else
			{
				itemOrigin.y = 0.f;
				itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
			}

			(*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
			(*it)->setPosition(currentPos);
			window.draw(**it);

			if (orientation == Orientation::Horizontal)
			{
				currentPos.x += itemRect.width + spacing;
			}
			else
			{
				currentPos.y += itemRect.height + spacing;
			}


		}
	}

	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition)
	{
		const sf::Vector2u textureSize = sprite.getTexture()->getSize();
		return { relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}
}
