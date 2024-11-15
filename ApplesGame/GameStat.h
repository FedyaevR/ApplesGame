#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <cassert>

namespace ApplesGame
{
	//Добавил константы для разработки, так как вынужден генерировать остальных игроков
	const int MIN_PLAYER_COUNT = 5;
	const int MAX_PLAYER_COUNT = 15;
	struct GameStat;
	void GenerateTable(GameStat* gameStat);
	sf::Text InitText(const std::string& text, sf::Color color, const sf::Font& font, int fontSize);
	sf::Text InitText(const std::string& text, const std::string& score, sf::Color color, const sf::Font& font, int fontSize);
	
	struct Game;

	struct Table
	{
		sf::Text* players;

		float lastElementY;
		float lastElementX;
		float marginTop = 20.f;

		Table(int playersCount)
		{
			players = new sf::Text[playersCount];
		}

		~Table() 
		{
			if (players != nullptr)
			{
				delete[] players;
			}
		}
	};

	struct PlayerStat
	{
		sf::Text playerName;
		sf::Text playerScore;
		sf::Color textColor;
		sf::Font font;
		int playerIndex = 0;
		
		PlayerStat() 
		{
			assert(font.loadFromFile("konstantinopel.ttf"));
		}

		PlayerStat(std::string sourceName, std::string sourceScore, sf::Color color)
		{
			assert(font.loadFromFile("konstantinopel.ttf"));
			playerName = InitText(sourceName, color, font, 35);
			playerScore = InitText(sourceScore, color, font, 35);
			textColor = color;
		}
	};

	struct GameStat
	{
		std::vector<PlayerStat> playerStats;
		PlayerStat* player = nullptr;

		bool isFirst = true;
		int playersCount = MIN_PLAYER_COUNT + rand() % (MAX_PLAYER_COUNT - MIN_PLAYER_COUNT + 1) + 1;

		std::string playersName[MAX_PLAYER_COUNT] = {"First 1", "Player 2", "SuperPac", "Pppappq", "qweqwe", "Player 6", "Player 7", "Player 8", "Player 9", "Player 10",
													 "Player 11", "Player 12", "Player 13", "Player 14", "Player 15"};

		Table table = Table(playersCount);

		GameStat()
		{
			playerStats.reserve(playersCount);

			//Иммитация игроков, сам игрок попадает в таблицу позднее. Оставляем под него ячейку
			for (int i = 0; i < playersCount - 1; i++)
			{
				playerStats.emplace_back();

				auto rnd = MIN_PLAYER_COUNT + rand() % ((MAX_PLAYER_COUNT - 1) - MIN_PLAYER_COUNT + 1);
				std::string rndName;

				if (rnd < MAX_PLAYER_COUNT)
				{
					rndName = playersName[rnd];
				}
				else
				{
					rndName = playersName[1];
				}

				auto rndScore = 1 + rand() % (10 - 1 + 1);

				playerStats[i].playerName = InitText(rndName, sf::Color::White, playerStats[i].font, 35);
				playerStats[i].playerScore = InitText(std::to_string(rndScore), sf::Color::White, playerStats[i].font, 35);
				playerStats[i].textColor = sf::Color::White;
			}

			//Костыль по добавлению обьекта самого игрока в массив
			playerStats.emplace_back();
			GenerateTable(this);
		}
	};

	void RandomPlayersFill(GameStat* gameStat);
	int GenerateScore();
	std::string GenerateName(GameStat* gameStat);
	void GenerateTable(GameStat* gameStat);
	void AddPlayer(GameStat* gameStat, std::string score = "", std::string playerName = "");
	void AddPlayerToTable(GameStat* gameStat);
	void InitGameStat(GameStat* gameStat, std::string playerName, std::string playerScore, sf::RenderWindow& window);
	void DrawGameStat(GameStat* gameStat, sf::RenderWindow& window, Game& game);
	void SortPlayerStats(GameStat* gameStat);
	void Merge(std::vector<PlayerStat>& arr, int left, int mid, int right);
	void MergeSort(std::vector<PlayerStat>& arr, int left, int right, GameStat* gameStat);
	void UpdatePlayer(GameStat* gameStat, int score);
	void DropTable(GameStat* gameStat);
	void BubbleSort(std::vector<PlayerStat>& players, int n);
}