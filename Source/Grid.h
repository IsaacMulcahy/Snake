#pragma once

class ObjectPlacement;
class WorldObject;

class Grid
{
	public:
		Grid();
		~Grid();

		enum OBJECT_TYPE 
		{
			EMPTY = 0,
			SNAKE = 1,
			OBSTACLE = 2,
			APPLE = 3
		};

		struct gridData
		{
			int id;
			OBJECT_TYPE type;
		};

		struct Vector2
		{
			int x;
			int y;
		};

		Vector2 getGridSize();
		Vector2 getPosition(WorldObject*);
		int updateObject(WorldObject*, ObjectPlacement*);
		gridData getGridPosition(int x, int y);
		int cellCheck(WorldObject*);

	private:
		Vector2 grid_size;
		gridData grid_zone[30][30];
};
