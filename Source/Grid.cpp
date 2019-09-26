#include "Grid.h"
#include "WorldObject.h"
#include "ObjectPlacement.h"
#include <Engine/Sprite.h>

Grid::Grid()
{
	grid_size.x = 30;
	grid_size.y = 30;

	for (int i = 0; i < grid_size.x; i++)
	{
		for (int j = 0; j < grid_size.y; j++)
		{
			grid_zone[i][j].id = 0;
			grid_zone[i][j].type = OBJECT_TYPE::EMPTY;
		}
	}
}

Grid::~Grid()
{
}

Grid::Vector2 Grid::getGridSize()
{
	return grid_size;
}

Grid::Vector2 Grid::getPosition(WorldObject* item)
{
	int id = item->getID();

	// Iterate through Grid
	for (int i = 0; i < grid_size.x; i++)
	{
		for (int j = 0; j < grid_size.y; j++)
		{
			if (grid_zone[i][j].id == id)
			{
				Vector2 returnValue;
				returnValue.x = i;
				returnValue.y = j;
				return returnValue;
			}
		}
	}
}

int Grid::updateObject(WorldObject* item, ObjectPlacement* object_placement)
{
	int id = item->getID();

	// Iterate through Grid to remove current position of object
	for (int i = 0; i < grid_size.x; i++)
	{
		for (int j = 0; j < grid_size.y; j++)
		{
			if (grid_zone[i][j].id == id)
			{
				grid_zone[i][j].id = 0;
				grid_zone[i][j].type = OBJECT_TYPE::EMPTY;
			}
		}
	}

	int collision = cellCheck(item);

	if (collision == 0 || collision == 2)
	{

		// Add data in new position
		int x = item->getObject()->position[0] / 30;
		int y = item->getObject()->position[1] / 30;

		if (collision == 2)
		{
			for (int i = 0; i < object_placement->getObjectCount(); i++)
			{
				if (object_placement->getWorldObject(i)->getID() == grid_zone[x][y].id)
				{
					object_placement->placeObject(ObjectPlacement::PLACEMENT_STYLE::RANDOM, this, i);
				}
			}
		}

		grid_zone[x][y].id = id;
		grid_zone[x][y].type = item->getType();

		return collision;

	}
	else
	{
		
		return true;
	}

}

Grid::gridData Grid::getGridPosition(int x, int y)
{
	return grid_zone[x][y];
}

int Grid::cellCheck(WorldObject* item)
{
	int x = item->getObject()->position[0] / 30;
	int y = item->getObject()->position[1] / 30;

	OBJECT_TYPE object_type = grid_zone[x][y].type;

	switch (object_type)
	{
		case OBJECT_TYPE::APPLE:
			return 2;
		break;
		case OBJECT_TYPE::OBSTACLE:
			return 1;
		break;
		case OBJECT_TYPE::SNAKE:
			return 1;
		break;
		default:
			return 0;
		break;
	}

}