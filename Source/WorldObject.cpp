#include "WorldObject.h"
#include <Engine/Sprite.h>

int WorldObject::new_id = 1;

WorldObject::WorldObject() : id(new_id++)
{
	
}

void WorldObject::loadObject(ASGE::Renderer* renderer)
{
	object = renderer->createRawSprite();
	object->loadTexture("..\\..\\Resources\\Textures\\error.png");
	object->position[0] = 60;
	object->position[1] = 60;
}

void WorldObject::loadObject(ASGE::Renderer* renderer, char filename[])
{
	object = renderer->createRawSprite();

	if (!object->loadTexture(filename))
	{
		object->loadTexture("..\\..\\Resources\\Textures\\error.png");
	}
	
	object->position[0] = 60;
	object->position[1] = 60;
}

bool WorldObject::passableCheck() const
{
	if (passable == true) {
		return true;
	}
	else
	{
		return false;
	}
}

int WorldObject::getID() const
{
	return id;
}

Grid::OBJECT_TYPE WorldObject::getType() const
{
	return type;
}

int WorldObject::getFacing() const
{
	return facing;
}

ASGE::Sprite* WorldObject::getObject() const
{
	return object;
}

void WorldObject::setType(Grid::OBJECT_TYPE new_type)
{
	type = new_type;
}

void WorldObject::setPassable(bool value)
{
	passable = value;
}

void WorldObject::positionObject(int x, int y)
{
	object->position[0] = x;
	object->position[1] = y;
}

void WorldObject::moveForward(int value) 
{

	switch (facing) {
		case WorldObject::Direction::RIGHT:
			object->position[0] = object->position[0] + value;
			break;
		case WorldObject::Direction::LEFT:
			object->position[0] = object->position[0] - value;
			break;
		case WorldObject::Direction::UP:
			object->position[1] = object->position[1] - value;
			break;
		case WorldObject::Direction::DOWN:
			object->position[1] = object->position[1] + value;
			break;
	}
}

void WorldObject::moveLeft(int value)
{
	switch (facing) {
	case WorldObject::Direction::RIGHT:
		object->position[0] = object->position[1] - value;
		break;
	case WorldObject::Direction::LEFT:
		object->position[0] = object->position[1] + value;
		break;
	case WorldObject::Direction::UP:
		object->position[1] = object->position[0] + value;
		break;
	case WorldObject::Direction::DOWN:
		object->position[1] = object->position[0] - value;
		break;
	}
}

void WorldObject::changeFacing(WorldObject::Direction change)
{
	facing = change;
}