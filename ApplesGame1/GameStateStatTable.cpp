#include "GameStateStatTable.h"
#include "Game.h"
#include <iostream>
#include <cassert>

namespace ApplesGame
{
	void UpdateGameStateStatTableData(GameSateStatTableData& data, Game& game, float timeDelta)
	{
		data.recordsTableText.setString("Records:");
		for (const RecordsTableItem& item : game.recordsTable)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
		}
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}

	void DrawGameStateStatTable(GameSateStatTableData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();
		data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
		window.draw(data.recordsTableText);
	}

	void ShutdownGameStatePlaying(GameSateStatTableData& data, Game& game)
	{

	}

	void HandleGameStateStatTableWindowEvent(GameSateStatTableData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}
	void InitGameStateStatTable(GameSateStatTableData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		game.recordsTable[0] = { "John", MAX_APPLES };
		game.recordsTable[1] = { "Alice", MAX_APPLES / 2 };
		game.recordsTable[2] = { "Bob", MAX_APPLES / 3 };
		game.recordsTable[3] = { "Clementine", MAX_APPLES / 4 };
		game.recordsTable[4] = { "You", 0 };

		data.recordsTableText.setString("Record table");
		data.recordsTableText.setFont(data.font);
		data.recordsTableText.setCharacterSize(24);
		data.hintText.setString("Record table");
		data.hintText.setFont(data.font);
		data.hintText.setCharacterSize(48);
		data.hintText.setFillColor(sf::Color::Red);
	}
}
