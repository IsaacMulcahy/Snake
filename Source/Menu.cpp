#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>
#include <Engine/Platform.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include "Menu.h"


/**
*   @brief   Default Constructor.
*/
Menu::Menu()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Menu::~Menu()
{
	this->inputs->unregisterCallback(callback_id);

	if (background)
	{
		delete background;
		background = nullptr;
	}

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}
}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The input callback should also
be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool Menu::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Snake - Menu");

	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(ASGE::EventType::E_KEY, &Menu::input, this);

	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	// load snake background sprite
	background = renderer->createRawSprite();
	background->position[0] = 0;
	background->position[1] = 0;
	background->scalar = 1.10f;

	if (!background->loadTexture("..\\..\\Resources\\Textures\\snake-1200x627.png"))
	{
		return false;
	}

	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool Menu::shouldExit() const
{
	return (renderer->exit() || this->exit);
}


/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's
input. Key presseses are translated in to GameActions which
are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void Menu::input(ASGE::SharedEventData data) const
{
	auto key_event = static_cast<ASGE::KeyEvent*>(data.get());
	auto action = key_event->action;
	auto key = key_event->key;

	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			game_action = GameAction::START_GAME;
		}
	}
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
current frame. Once the current frame is has finished
the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void Menu::update(const ASGE::GameTime &)
{

	// gamepad input is polled
	auto& gamepad = inputs->getGamePad(0);
	if (gamepad.is_connected &&
		gamepad.buttons[1])
	{
		game_action = GameAction::EXIT;
	}

	// run the game loop
	processGameActions();

	// should we terminate the game?
	if (shouldExit())
	{
		signalExit();
	}
}


/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
Once the current frame is has finished the buffers are
swapped accordingly and the image shown.
*   @return  void
*/
void Menu::render(const ASGE::GameTime &)
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
	renderer->renderSprite(*background);
	renderer->renderText("\nPress Space to start", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
}


/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of
*            user input. It allows input to processed in a different
thread and the game actions performed in the main thread.
*   @return  void
*/
void Menu::processGameActions()
{

	switch (game_action)
	{
	case GameAction::EXIT:
	{
		this->exit = true;
		break;
	}
	case GameAction::START_GAME:
	{
		this->exit = true;
		break;
	}
	}
    game_action = GameAction::NONE;
}

