#include "Game.h"
#include "GameStat.h"

namespace ApplesGame
{
	void RandomPlayersFill(GameStat* gameStat)
	{
		for (int i = 0; i < gameStat->playersCount; i++)
		{
			std::string playerScore = std::to_string(GenerateScore());
			std::string playerName = GenerateName(gameStat);
			PlayerStat player(playerName, playerScore, sf::Color::White);

			gameStat->playerStats[i] = player;
		}
	}

	int GenerateScore()
	{
		return 20 + rand() % (1000 - 1 + 20);;
	}

	std::string GenerateName(GameStat* gameStat)
	{
		int rnd = rand() % (MAX_PLAYER_COUNT - 1);
		return gameStat->playersName[rnd];
	}

	sf::Text InitText(const std::string& text, sf::Color color, const sf::Font& font, int fontSize)
	{
		sf::Text result;
		result.setFont(font);
		result.setFillColor(color);
		result.setCharacterSize(fontSize);

		result.setString(text);

		return result;
	}

	sf::Text InitText(const std::string& text, const std::string& score, sf::Color color, const sf::Font& font, int fontSize)
	{
		sf::Text result;
		result.setFont(font);
		result.setFillColor(color);
		result.setCharacterSize(fontSize);

		result.setString(text + ": " + score);

		return result;
	}

	void GenerateTable(GameStat* gameStat)
	{
		DropTable(gameStat);
		gameStat->table.lastElementX = SCREEN_WIDTH / 2.5f;
		gameStat->table.lastElementY = 55.f;

		for (int i = 0; i < gameStat->playersCount; i++)
		{
			auto name = std::to_string(gameStat->playerStats[i].playerIndex + 1) + ". " + gameStat->playerStats[i].playerName.getString();
			gameStat->table.players[i] = InitText(name, gameStat->playerStats[i].playerScore.getString(), gameStat->playerStats[i].textColor, gameStat->playerStats[i].font, 20);
			gameStat->table.lastElementY = gameStat->table.lastElementY + gameStat->table.marginTop;
			gameStat->table.players[i].setPosition(gameStat->table.lastElementX, gameStat->table.lastElementY);
		}
	}

	void AddPlayer(GameStat* gameStat, std::string score, std::string playerName)
	{
		if (gameStat->player == nullptr)
		{
			gameStat->player = &gameStat->playerStats[gameStat->playersCount - 1];
			gameStat->player->playerIndex = gameStat->playersCount - 1;
		}
		else
		{
			gameStat->player = &gameStat->playerStats[gameStat->player->playerIndex];
		}

		gameStat->playerStats[gameStat->player->playerIndex] = PlayerStat(playerName, score, sf::Color::Green);
		AddPlayerToTable(gameStat);
	}

	void AddPlayerToTable(GameStat* gameStat)
	{
		//тут не было индекса, вместо него был gameStat-> playersCount - 1
		PlayerStat* player = gameStat->player;
		gameStat->table.players[player->playerIndex] = InitText(player->playerName.getString(), player->playerScore.getString(), player->textColor, player->font, 20);
		gameStat->table.lastElementY = gameStat->table.lastElementY + gameStat->table.marginTop;
		gameStat->table.players[player->playerIndex].setPosition(gameStat->table.lastElementX, gameStat->table.lastElementY);
	}

	void InitGameStat(GameStat* gameStat, std::string playerName, std::string playerScore, sf::RenderWindow& window)
	{
		AddPlayer(gameStat, playerScore, playerName);
		SortPlayerStats(gameStat);
		GenerateTable(gameStat);
	}

	void DrawGameStat(GameStat* gameStat, sf::RenderWindow& window, Game& game)
	{
		auto players = gameStat->table.players;
		window.clear();

		for (auto ptr = players; ptr < players + gameStat->playersCount; ptr++)
		{
			window.draw(*ptr);
		}

		sf::Text exitFromTable;
		exitFromTable.setCharacterSize(35);
		exitFromTable.setFillColor(sf::Color::White);
		exitFromTable.setFont(gameStat->playerStats[0].font);
		exitFromTable.setPosition(SCREEN_WIDTH / 3.5f, SCREEN_HEIGHT - 75.f);
		exitFromTable.setString("For exit press Enter");
		window.draw(exitFromTable);

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			game.gameStates.pop_back();
		}
	}

	void Merge(std::vector<PlayerStat>& players, int left, int mid, int right)
	{
		int number1 = mid - left + 1;
		int number2 = right - mid;

		// Создаем временные массивы
		std::vector<PlayerStat> leftPart(number1);
		std::vector<PlayerStat> rightPart(number2);

		// Копируем данные во временные массивы
		for (int i = 0; i < number1; i++)
		{
			leftPart[i] = players[left + i];
		}

		for (int j = 0; j < number2; j++)
		{
			rightPart[j] = players[mid + 1 + j];
		}

		// Слияние временных массивов
		int i = 0; // Индекс первого подмассива
		int j = 0; // Индекс второго подмассива
		int k = left; // Индекс сливаемого массива

		while (i < number1 && j < number2) 
		{
			int scoreL = std::stoi(leftPart[i].playerScore.getString().toAnsiString());
			int scoreR = std::stoi(rightPart[j].playerScore.getString().toAnsiString());
			if (scoreL >= scoreR)
			{
				players[k] = leftPart[i];
				i++;
			}
			else 
			{
				players[k] = rightPart[j];
				j++;
			}
			k++;
		}

		while (i < number1) 
		{
			players[k] = leftPart[i];
			i++;
			k++;
		}

		while (j < number2) 
		{
			players[k] = rightPart[j];
			j++;
			k++;
		}
	}

	void MergeSort(std::vector<PlayerStat>& players, int left, int right, GameStat* gameStat)
	{
		if (left < right) 
		{
			int mid = left + (right - left) / 2;

			MergeSort(players, left, mid, gameStat);
			MergeSort(players, mid + 1, right, gameStat);

			Merge(players, left, mid, right);
		}

		// Обновление индексов после сортировки
		for (int i = left; i <= right; ++i)
		{
			players[i].playerIndex = i; // Устанавливаем playerIndex

			// Проверяем, является ли текущий игрок тем же самым, который хранится в gameStat->player
			if (gameStat->player && gameStat->player->playerName.getString() == players[i].playerName.getString())
			{
				gameStat->player = &players[i]; // Обновляем указатель
			}
		}
	}

	void BubbleSort(std::vector<PlayerStat>& players, int n)
	{
		bool swapped;
		for (int i = 0; i < n - 1; i++) 
		{
			swapped = false; 
			for (int j = 0; j < n - i - 1; j++) 
			{
				int scoreL = std::stoi(players[j].playerScore.getString().toAnsiString());
				int scoreR = std::stoi(players[j + 1].playerScore.getString().toAnsiString());

				if (scoreL > scoreR) 
				{ 
					std::swap(players[j], players[j + 1]);
					swapped = true; 
				}
			}

			// Если за проход не было обменов, массив отсортирован
			if (!swapped)
			{
				break;
			}
		}
	}

	void UpdatePlayer(GameStat* gameStat, int score)
	{
		gameStat->isFirst = false;
		PlayerStat* player = gameStat->player;
		//player->playerName = InitText(player->playerName.getString(), player->textColor, player->font, 35);
		player->playerScore = InitText(std::to_string(score), player->textColor, player->font, 35);
		SortPlayerStats(gameStat);

		GenerateTable(gameStat);
	}

	void DropTable(GameStat* gameStat)
	{
		delete[] gameStat->table.players;
		gameStat->table.players = new sf::Text[gameStat->playersCount];
	}

	void SortPlayerStats(GameStat* gameStat)
	{
		/*BubbleSort(gameStat->playerStats, gameStat->playersCount);*/
		MergeSort(gameStat->playerStats, 0, gameStat->playersCount - 1, gameStat);
	}
}
