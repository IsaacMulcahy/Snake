#include "ObjectPlacement.h"
#include "WorldObject.h"
#include <Engine/Sprite.h>

ObjectPlacement::~ObjectPlacement()
{
	for (int i = 0; i < object_max; i++)
	{
		delete object[i];
	}
}

void ObjectPlacement::placeObject(ObjectPlacement::PLACEMENT_STYLE method, Grid* world)
{
	int x = 0;
	int y = 0;
	
	switch (method)
	{
		case ObjectPlacement::RANDOM:
			
			x = std::rand() % 29;
			y = std::rand() % 29;

			Grid::gridData data = world->getGridPosition(x, y);

			if (data.type == Grid::OBJECT_TYPE::EMPTY)
			{
				object[object_count-1]->getObject()->position[0] = (x * 30) - x;
				object[object_count-1]->getObject()->position[1] = (y * 30) - y;
				world->updateObject(object[object_count-1], this);
			}
		break;
		case ObjectPlacement::NEXT_AVALIBLE:
		break;
		case ObjectPlacement::LAST_AVALIBLE:
		break;
	}
}

void ObjectPlacement::placeObject(Grid* world, int x, int y)
{
	Grid::gridData data = world->getGridPosition(x, y);
	object[object_count-1]->getObject()->position[0] = (x * 30) - x;
	object[object_count-1]->getObject()->position[1] = (y * 30) - y;
	world->updateObject(object[object_count-1], this);
}

void ObjectPlacement::placeObject(ObjectPlacement::PLACEMENT_STYLE method, Grid* world, int id)
{
	int x = 0;
	int y = 0;

	switch (method)
	{
	case ObjectPlacement::RANDOM:
		x = std::rand() % 29;
		y = std::rand() % 29;

		Grid::gridData data = world->getGridPosition(x, y);

		if (data.type == Grid::OBJECT_TYPE::EMPTY)
		{
			object[id]->getObject()->position[0] = (x * 30) - x;
			object[id]->getObject()->position[1] = (y * 30) - y;
			world->updateObject(object[id], this);
		}
		break;
	case ObjectPlacement::NEXT_AVALIBLE:
		break;
	case ObjectPlacement::LAST_AVALIBLE:
		break;
	}
}

void ObjectPlacement::createObject(ASGE::Renderer* renderer, Grid* world, Grid::OBJECT_TYPE type)
{

	switch (type)
	{
		case Grid::OBSTACLE:
			object[object_count] = new WorldObject;
			object[object_count]->loadObject(renderer, "..\\..\\Resources\\Textures\\obstacle.png");
			object[object_count]->setType(Grid::OBJECT_TYPE::OBSTACLE);
		break;
		case Grid::APPLE:
			object[object_count] = new WorldObject;
			object[object_count]->loadObject(renderer, "..\\..\\Resources\\Textures\\apple.png");
			object[object_count]->setType(Grid::OBJECT_TYPE::APPLE);
			object[object_count]->setPassable(true);
		break;
	}

	object_count++;

}

int ObjectPlacement::getObjectCount()
{
	return object_count;
}

WorldObject* ObjectPlacement::getWorldObject(int value)
{
	return object[value];
}

void ObjectPlacement::makeArea(ASGE::Renderer* renderer, Grid* world)
{
	Grid::Vector2 grid_size = world->getGridSize();

	for (int i = 0; i < grid_size.x; i++)
	{
		for (int j = 0; j < grid_size.y; j++)
		{
			if (i == 0 || j == 0 || i == grid_size.x-1 || j == grid_size.y-1)
			{
				createObject(renderer, world, Grid::OBJECT_TYPE::OBSTACLE);
				placeObject(world, i, j);
			}
		}
	}
}