#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include "Player.h"
#include "Grid.h"
#include "ObjectPlacement.h"

struct GameFont;

/**
*  SnakeGame. An OpenGL Game based on ASGE.
*/

class SnakeGame:
	public ASGE::OGLGame
{
public:
	SnakeGame();
	~SnakeGame();
	virtual bool init() override;

private:
	void processGameActions(); 
	void input(ASGE::SharedEventData data) const;
	bool shouldExit() const;

	void menu(ASGE::Renderer*, const char*);

	// Snake Game
	void main();
	void obstacleAdd(ASGE::Renderer*, Grid*);

	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	int  callback_id = -1;             /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */
	double timer;					   /**< Aimed to make the game run at the same speed acroos other platforms */
	int current_obscale_increase;
	int state = 0;

	// Objects
	ASGE::Sprite* background;
	ASGE::Sprite* game_backdrop;
	ASGE::Colour text_colour = ASGE::COLOURS::LIGHTGREEN;
	Player* player;
	Grid* world;
	ObjectPlacement* world_placement;

};
