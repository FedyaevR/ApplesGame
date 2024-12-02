#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace ApplesGame
{
	struct Game;

	struct GameSateStatTableData
	{
		Menu menu;
		// Resources
		sf::Font font;
		sf::Text hintText;
		sf::Text recordsTableText;
	};


	void UpdateGameStateStatTableData(GameSateStatTableData& data, Game& game, float timeDelta);
	void DrawGameStateStatTable(GameSateStatTableData& data, Game& game, sf::RenderWindow& window);
	void ShutdownGameStatePlaying(GameSateStatTableData& data, Game& game);
	void HandleGameStateStatTableWindowEvent(GameSateStatTableData& data, Game& game, const sf::Event& event);
	void InitGameStateStatTable(GameSateStatTableData& data, Game& game);
}