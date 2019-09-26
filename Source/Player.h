#pragma once

#include "WorldObject.h"

class Player
{
	protected:
		int scoring = 0;
		int length = 5;
		int player_moved = 0;
		WorldObject* player_body[50];
	public:
		Player() = default;
		~Player();

		void createBody(ASGE::Renderer*);
		void updateBody();
		void headControl(WorldObject::Direction);
		WorldObject* getBodyPart(int);
		void addScore(int);
		void addLength(ASGE::Renderer*);
		void addPlayerMoved(int);
		int getScore() const;
		int getLength() const;
		int getPlayerMoved() const;
};