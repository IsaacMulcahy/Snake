#include <Engine/Sprite.h>

#include "Player.h"
#include "WorldObject.h"

Player::~Player()
{
	for (int i = 0; i < 50; i++)
	{
		delete player_body[i];
	}
}

void Player::createBody(ASGE::Renderer* renderer)
{
	player_body[0] = new WorldObject;
	player_body[0]->loadObject(renderer, "..\\..\\Resources\\Textures\\snakeBody.png");
	player_body[0]->setType(Grid::OBJECT_TYPE::SNAKE);
	for (int i = 1; i < length; i++)
	{
		player_body[i] = new WorldObject;
		player_body[i]->loadObject(renderer, "..\\..\\Resources\\Textures\\snakeBody.png");
		player_body[i]->moveForward(-30*i);
		player_body[i]->setType(Grid::OBJECT_TYPE::SNAKE);

	}
}

void Player::updateBody()
{

	player_body[0]->moveForward(1);
	player_moved++;
	
	for (int i = length-1; i > 0; i--)
	{
		if (player_moved == player_body[0]->getObject()->dims[0]/2)
		{
			player_body[i]->changeFacing(static_cast<WorldObject::Direction>(player_body[i - 1]->getFacing()));
		}
		player_body[i]->moveForward(2);
	}

	if (player_moved == player_body[0]->getObject()->dims[0] / 2)
	{
		player_moved = 0;
	}
}

void Player::headControl(WorldObject::Direction direction)
{
	switch (static_cast<WorldObject::Direction>(player_body[0]->getFacing()))
	{
		case WorldObject::Direction::LEFT:
			if (direction != WorldObject::Direction::RIGHT)
			{
				player_body[0]->changeFacing(direction);
			}
		break;
		case WorldObject::Direction::RIGHT:
			if (direction != WorldObject::Direction::LEFT)
			{
				player_body[0]->changeFacing(direction);
			}
		break;
		case WorldObject::Direction::UP:
			if (direction != WorldObject::Direction::DOWN)
			{
				player_body[0]->changeFacing(direction);
			}
		break;
		case WorldObject::Direction::DOWN:
			if (direction != WorldObject::Direction::UP)
			{
				player_body[0]->changeFacing(direction);
			}
		break;
	}

}

WorldObject* Player::getBodyPart(int part)
{
	return player_body[part];
}

void Player::addScore(int value)
{
	scoring += value;
}

void Player::addLength(ASGE::Renderer* renderer)
{
	player_body[length] = new WorldObject;
	player_body[length]->loadObject(renderer, "..\\..\\Resources\\Textures\\snakeBody.png");
	player_body[length]->changeFacing(static_cast<WorldObject::Direction>(player_body[length - 1]->getFacing()));
	player_body[length]->positionObject(player_body[length-1]->getObject()->position[0], player_body[length - 1]->getObject()->position[1]);
	player_body[length]->moveForward(-30);
	player_body[length]->setType(Grid::OBJECT_TYPE::SNAKE);
	length++;
}

void Player::addPlayerMoved(int value)
{
	player_moved += value;
}

int Player::getScore() const
{
	return scoring;
}

int Player::getLength() const
{
	return length;
}

int Player::getPlayerMoved() const
{
	return player_moved;
}

