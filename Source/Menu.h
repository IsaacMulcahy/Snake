#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include "Player.h"

struct GameFont;

/**
*  SnakeGame. An OpenGL Game based on ASGE.
*/

class Menu :
	public ASGE::OGLGame
{
public:
	Menu();
	~Menu();
	virtual bool init() override;

private:
	void processGameActions();
	void input(ASGE::SharedEventData data) const;
	bool shouldExit() const;

	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	int  callback_id = -2;             /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */

	// Objects
	ASGE::Sprite* background = nullptr;    /**< Sprite Object. The background sprite. */
};
