#include "Apple.h"
#include "GameSettings.h"

#include <cstdlib>
#include <assert.h>

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}
			
		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void ResetAppleState(Apple& apple)
	{
		// init apple state
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEGHT);
		apple.isEaten = false;
	}

	void ClearApplesGrid(ApplesGrid& applesGrid)
	{
		for (int i = 0; i < APPLES_GRID_CELLS_HORIZONTAL; i++)
		{
			for (int j = 0; j < APPLES_GRID_CELLS_VERTICAL; j++)
			{
				ApplesGridCell& cell = applesGrid.cells[i][j];
				for (int k = 0; k < MAX_APPLES_IN_CELL; k++)
				{
					Apple* apple = cell.apples[k];
					if (apple != nullptr)
					{
						for (int i = apple->numGridCells - 1; i >= 0; --i)
						{
							apple->gridCells[i] = nullptr;
						}
						apple->numGridCells = 0;
					}

					cell.apples[k] = nullptr;
				}
				cell.numApplesInCell = 0;
			}
		}
	}

	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		Vector2D appleCornerTL = apple.position + Vector2D{ -APPLE_SIZE / 2, -APPLE_SIZE / 2 };
		Vector2D appleCornerBR = apple.position + Vector2D{ APPLE_SIZE / 2, APPLE_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(appleCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(appleCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(appleCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(appleCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		ApplesGridCell* newCells[4] = {nullptr};
		int numNewCells = 0;
		// Add apple to new cells	
		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				ApplesGridCell& cell = applesGrid.cells[cellX][cellY];

				bool isAppleInCell = false;
				for (ApplesGridCell* oldCell : apple.gridCells)
				{
					if (oldCell == &cell)
					{
						isAppleInCell = true;
						break;
					}
				}

				if (!isAppleInCell)
				{
					cell.apples[cell.numApplesInCell++] = &apple;
					newCells[numNewCells++] = &cell;
					assert(cell.numApplesInCell <= MAX_APPLES_IN_CELL);
				}
			}
		}

		// Remove apple from old cells
		for (int i = 0; i < apple.numGridCells; ++i)
		{
			ApplesGridCell* cell = apple.gridCells[i];
			bool needRemoveFromCell = true;
			for (int j = 0; j < numNewCells; ++j)
			{
				if (cell == newCells[j])
				{
					needRemoveFromCell = false;
					break;
				}
			}

			if (needRemoveFromCell)
			{
				for (int j = 0; j < cell->numApplesInCell; ++j)
				{
					if (cell->apples[i] == &apple)
					{
						cell->apples[i] = cell->apples[cell->numApplesInCell - 1];
						cell->numApplesInCell--;
						break;
					}
				}
				apple.gridCells[i] = apple.gridCells[apple.numGridCells - 1];
				--apple.numGridCells;
			}
		}
	}

	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		for (int i = 0; i < apple.numGridCells; ++i)
		{
			ApplesGridCell* cell = apple.gridCells[i];
			for (int j = 0; j < cell->numApplesInCell; ++j)
			{
				if (cell->apples[i] == &apple)
				{
					cell->apples[i] = cell->apples[cell->numApplesInCell - 1];
					cell->numApplesInCell--;
					break;
				}
			}
			apple.gridCells[i] = nullptr;
		}
		apple.numGridCells = 0;
	}

	bool FindPlayerCollisionWithApples(const Vector2D& playerPosition, const ApplesGrid& grid, Apple** result, int& numFoundApples)
	{
		Vector2D playerCornerTL = playerPosition + Vector2D{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
		Vector2D playerCornerBR = playerPosition + Vector2D{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(playerCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(playerCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(playerCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(playerCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		numFoundApples = 0;
		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				for (int i = 0; i < grid.cells[cellX][cellY].numApplesInCell; ++i)
				{
					Apple* apple = grid.cells[cellX][cellY].apples[i];
					if (!apple->isEaten)
					{
						float dx = playerPosition.x - apple->position.x;
						float dy = playerPosition.y - apple->position.y;
						float distance = sqrt(dx * dx + dy * dy);
						if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2)
						{
							result[numFoundApples] = apple;
							++numFoundApples;
						}
					}
				}
			}
		}

		return numFoundApples > 0;
	}
}
