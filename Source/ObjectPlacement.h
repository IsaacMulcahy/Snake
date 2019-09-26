#pragma once
#include "Grid.h"
#include <Engine/OGLGame.h>

class WorldObject;

class ObjectPlacement
{
	public:
		ObjectPlacement() = default;
		~ObjectPlacement();

		enum PLACEMENT_STYLE
		{
			RANDOM = 0,
			NEXT_AVALIBLE = 1,
			LAST_AVALIBLE = 2,
			EXCACT = 3
		};

		void placeObject(PLACEMENT_STYLE, Grid*);
		void placeObject(Grid*, int, int);
		void placeObject(PLACEMENT_STYLE, Grid*, int);
		void createObject(ASGE::Renderer*, Grid*, Grid::OBJECT_TYPE);
		void makeArea(ASGE::Renderer*, Grid*);
		int getObjectCount();
		WorldObject* getWorldObject(int);
	private:
		static const int object_max = 500;
		int object_count = 0;
		WorldObject* object[object_max];
};