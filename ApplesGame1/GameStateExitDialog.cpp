#include "GameStateExitDialog.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		//assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		//data.hintText.setString("Are you want to continue game? Enter - Yes, Esc - No");
		//data.hintText.setFont(data.font);
		//data.hintText.setCharacterSize(24);
		//data.hintText.setFillColor(sf::Color::White);
		//data.hintText.setOrigin(GetItemOrigin(data.hintText, { 0.5f, 0.5f }));

		//data.background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black


		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.menu.rootItem.hintText.setString("Pause menu");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.continueItem);
		data.menu.rootItem.children.push_back(&data.exitItem);


		data.continueItem.text.setString("Continue Game");
		data.continueItem.text.setFont(data.font);
		data.continueItem.text.setCharacterSize(24);

		data.exitItem.text.setString("Exit Game");
		data.exitItem.text.setFont(data.font);
		data.exitItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.continueItem);
	}

	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.continueItem)
				{
					//SwitchGameState(game, GameStateType::Playing);
					PopGameState(game);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.exitItem)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window)
	{
		//sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
		//
		//data.background.setSize(windowSize);
		//window.draw(data.background);

		//data.hintText.setPosition(windowSize / 2.f);
		//window.draw(data.hintText);

		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}

}
