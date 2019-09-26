#pragma once

#include "Grid.h"
#include <Engine/OGLGame.h>

class WorldObject
{
	public:
		WorldObject();
		~WorldObject() = default;

		enum Direction {
			RIGHT = 1,
			LEFT = 2,
			UP = 3,
			DOWN = 4
		};

		bool passableCheck() const;
		int getID() const;
		Grid::OBJECT_TYPE getType() const;
		int getFacing() const;
		ASGE::Sprite* getObject() const;
		void setType(Grid::OBJECT_TYPE);
		void setPassable(bool);
		void changeFacing(Direction);
		void positionObject(int, int);
		void moveForward(int);
		void moveLeft(int);
		void loadObject(ASGE::Renderer*);
		void loadObject(ASGE::Renderer*, char[]);
	protected:
		bool passable = false;
		ASGE::Sprite* object = nullptr;
		Grid::OBJECT_TYPE type = Grid::OBJECT_TYPE::EMPTY;
		Direction facing = RIGHT;
		static int new_id;
		const int id;

};