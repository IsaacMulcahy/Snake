#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"

// Objects
#include "ObjectPlacement.h"
#include "WorldObject.h"
#include "Player.h"
#include "Grid.h"


/**
*   @brief   Default Constructor.
*/
SnakeGame::SnakeGame()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
SnakeGame::~SnakeGame()
{
	this->inputs->unregisterCallback(callback_id);

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}

	delete player;
	delete world;
	delete world_placement;
}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool SnakeGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Snake - Game 2");

	renderer->setClearColour(ASGE::COLOURS::BLACK);
	//toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(ASGE::EventType::E_KEY, &SnakeGame::input, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
	renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	// Menu
	background = renderer->createRawSprite();
	background->position[0] = 0;
	background->position[1] = 0;
	background->loadTexture("..\\..\\Resources\\Textures\\background.png");

	// create player
	player = new Player();
	player->createBody(renderer.get());

	// create world
	world = new Grid();
	world_placement = new ObjectPlacement();
	world_placement->makeArea(renderer.get(), world);

	// Apples
	for (int i = 0; i < 3; i++)
	{
		world_placement->createObject(renderer.get(), world, Grid::OBJECT_TYPE::APPLE);
		world_placement->placeObject(ObjectPlacement::PLACEMENT_STYLE::RANDOM, world);
	}

	// Backdrop
	game_backdrop = renderer->createRawSprite();
	game_backdrop->position[0] = 0;
	game_backdrop->position[1] = 0;
	game_backdrop->loadTexture("..\\..\\Resources\\Textures\\Grid.png");

	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool SnakeGame::shouldExit() const
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
void SnakeGame::input(ASGE::SharedEventData data) const
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

		if (key == ASGE::KEYS::KEY_W)
		{
			game_action = GameAction::FACE_UP;
		}
		if (key == ASGE::KEYS::KEY_S)
		{
			game_action = GameAction::FACE_DOWN;
		}
		if (key == ASGE::KEYS::KEY_A)
		{
			game_action = GameAction::FACE_LEFT;
		}
		if (key == ASGE::KEYS::KEY_D)
		{
			game_action = GameAction::FACE_RIGHT;
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
void SnakeGame::update(const ASGE::GameTime &time)
{
	timer += (time.delta_time.count() / 1000) * 60;

	if (timer > 1)
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
		
		if (state == 1)
		{
			main();
		}
		// should we terminate the game?
		if (shouldExit())
		{
			signalExit();
		}

		timer = 0;

	}
}


/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
			 Once the current frame is has finished the buffers are 
			 swapped accordingly and the image shown.
*   @return  void
*/
void SnakeGame::render(const ASGE::GameTime &)
{
	
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
	
	ASGE::Colour text_colour = ASGE::COLOURS::LIGHTGREEN;

	static int timer;

	std::string score("Score:");
	score += std::to_string(player->getScore());

	switch (state)
	{
		case 0:
			menu(renderer.get(), "Press Space to Start");
		break;
		
		case 1:

			renderer->renderSprite(*game_backdrop);

			for (int i = 0; i < world_placement->getObjectCount(); i++)
			{
				renderer->renderSprite(*world_placement->getWorldObject(i)->getObject());
			}


			for (int i = 1; i < player->getLength(); i++)
			{
				renderer->renderSprite(*player->getBodyPart(i)->getObject());
			}

			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					//renderer->renderText("Score: " + score, 10, 25, 0.7, ASGE::COLOURS::LIGHTGREEN);
				}
			}

			//renderer->renderText(std::move(score), 10, 25, 0.7, ASGE::COLOURS::LIGHTGREEN);
		break;

		case 2:
			menu(renderer.get(), "Press Space to try again");
		break;
	}
}


/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void SnakeGame::processGameActions()
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
			state = 1;
		}
	}

	// if player change of direction > 30 then allow input else ignore
	//if (player->getPlayerMoved() > player->getBodyPart(0)->getObject()->dims[0])
	//{
		switch (game_action)
		{
			case GameAction::FACE_UP:
			{
				player->headControl(WorldObject::Direction::UP);
				obstacleAdd(renderer.get(), world);
				break;
			}

			case GameAction::FACE_DOWN:
			{
				player->headControl(WorldObject::Direction::DOWN);
				obstacleAdd(renderer.get(), world);
				break;
			}

			case GameAction::FACE_RIGHT:
			{
				player->headControl(WorldObject::Direction::RIGHT);
				obstacleAdd(renderer.get(), world);
				break;
			}

			case GameAction::FACE_LEFT:
			{
				player->headControl(WorldObject::Direction::LEFT);
				obstacleAdd(renderer.get(), world);
				break;
			}
		}
	//}

	game_action = GameAction::NONE;
}

void SnakeGame::menu(ASGE::Renderer* renderer, const char* text)
{
	
	timer++;

	if (timer == 0)
	{
		text_colour = ASGE::COLOURS::LIGHTGREEN;
	}

	if (timer > 30)
	{
		text_colour = ASGE::COLOURS::DARKGREEN;
	}

	if (timer > 60)
	{
		timer = 0;
	}

	renderer->renderSprite(*background);
	renderer->renderText(text, (WINDOW_WIDTH / 2) - 200, 700, 1.0, text_colour);
}



void SnakeGame::main()
{
	player->updateBody();

	int collision;

	for (int i = 2; i < player->getLength(); i++)
	{
		collision = world->updateObject(player->getBodyPart(i), world_placement);
	}

	collision = world->updateObject(player->getBodyPart(1), world_placement);

	if (collision == 1)
	{
		state = 2;
	}

	if (collision == 2)
	{
		player->addLength(renderer.get());
		player->addScore(10);
		current_obscale_increase = 0;
	}

}

void SnakeGame::obstacleAdd(ASGE::Renderer* renderer, Grid* world)
{

	for (int i = 0; i < current_obscale_increase; i++)
	{
		world_placement->createObject(renderer, world, Grid::OBJECT_TYPE::OBSTACLE);
		world_placement->placeObject(ObjectPlacement::PLACEMENT_STYLE::RANDOM, world);
	}

	if (current_obscale_increase < 5)
	{
		current_obscale_increase += 2;
	}

}

