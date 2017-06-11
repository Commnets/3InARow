#include "GameApp.hpp"
#include "EntitiesBuilder.hpp"
#include "MovementsBuilder.hpp"
#include "Movements.hpp"
#include "Timer.hpp"
#include "BoardBuilder.hpp"
#include "Game.hpp"
#include "GameAppStates.hpp"
#include "Player.hpp"
#include "Defs.hpp"
#include <Common/resourcesreader.hpp>
#include <SDL/sdlformbuilder.hpp>
#include <SDL/sdlsoundbuilder.hpp>

// ---
GameApplication::GameApplication ()
		: QGAMES::BoardGameApplication (new GameApplicationImpl ())
{
#ifdef NDEBUG
	// If the data parameter exists, then changes the default temporal file...
	// It makes sen se only when running release version of the app!
	if (dynamic_cast <QGAMES::InZipResourceReader*> (QGAMES::ResourceReader::resourceReader ()) != NULL)
		((QGAMES::InZipResourceReader*) QGAMES::ResourceReader::resourceReader ()) -> 
			setTempLocation (parameter (std::string (__GAME_DATADIRPROPERTYNAME__)));
#endif
}

// ---
void GameApplication::addScoreObjects ()
{
}

// ---
void GameApplication::removeScoreObjects ()
{
}

// ---
void GameApplication::reset ()
{
	((TheGame*) _boardGame) -> reset ();
}

// ---
QGAMES::FormBuilder* GameApplication::createFormBuilder ()
{
	return (new SDL2DSpriteBuilder (std::string (__FORMSFILE__), 
		(SDLScreen*) mainScreen ())); 
}

// ---
QGAMES::ObjectBuilder* GameApplication::createObjectBuilder ()
{
	return (new QGAMES::ObjectBuilder (std::string (__OBJECTSFILE__), formBuilder ()));
}

// ---
QGAMES::EntityBuilder* GameApplication::createEntityBuilder ()
{
	return (new EntitiesBuilder (__ENTITIESFILE__, 
		formBuilder (), movementBuilder ())); 
}

// ---
QGAMES::MovementBuilder* GameApplication::createMovementBuilder ()
{
	return (new MovementsBuilder (__MOVEMENTSFILE__)); 
}

// ---
QGAMES::SoundBuilder* GameApplication::createSoundBuilder ()
{
	return (new SDLSoundBuilder (__SOUNDSFILE__)); 
}

// ---
QGAMES::Timer* GameApplication::createTimer ()
{
	return (new Timer ()); 
}

// ---
QGAMES::Screens GameApplication::createScreens ()
{
	QGAMES::Screens r;
	SDLScreen* scr = new SDLScreen (__GAMESNAME__, 
		 QGAMES::Position (0,0), __SCREENWIDTH__, __SCREENHEIGHT__, __SCREENXPOS__, __SCREENYPOS__);
	scr -> windowAtCenter ();
	r.insert (QGAMES::Screens::value_type (__QGAMES_MAINSCREEN__, scr));
	return (r); 
}

// ---
QGAMES::BoardBuilder* GameApplication::createBoardBuilder ()
{
	QGAMES::BoardBuilder* result = new QGAMES::BoardBuilder (__BOARDBUILDERDEFFILE__);
	result -> addAddsOn (new BoardBuilderAddsOn ());
	return (result);
}

// ---
QGAMES::BoardGame* GameApplication::createBoardGame ()
{
	// The game has only one board (the board where the pieces are set)
	QGAMES::Boards boards;
	boards.insert (QGAMES::Boards::value_type (__MAINBOARDID__, 
		boardBuilder () -> board (__MAINBOARDID__))); 
	// When the board is built, the resources (the pieces) belongs to the board
	// This relationship will change when the game is initialized,
	// assigning the resources to the players.

	// The board has only one rule to verify
	// any time a player plays!
	QGAMES::BoardGameRules rules;
	rules.push_back (new VerifyThreeInARow ());

	// The game has to players
	QGAMES::BoardGamePlayers players;
	players.insert (QGAMES::BoardGamePlayers::value_type 
		(__PLAYER1__, new Player3InARow (__PLAYER1__)));
	players.insert (QGAMES::BoardGamePlayers::value_type 
		(__PLAYER2__, new Player3InARow (__PLAYER2__)));

	// ...and no specific resources
	// Let's say that the resources defined in the definition file will have been 
	// assigned assigned to the board initially.
	// During the initialization of the board game, they will be reassigned
	// to the players, and during the game they will be located at squares!
	QGAMES::BoardResources resources;

	// Finally the game is created!-
	return (new TheGame (boards, rules, players, resources));
}

// ---
void GameApplication::initialize ()
{
	// Caclling this parent method, the game is created and the
	// resources redistributed to the players...
	QGAMES::BoardGameApplication::initialize ();

	// Sets the icon to the window...
	mainScreen () -> setIcon (formBuilder () -> form (__APPLICATIONICONFORM__));

	// add the game states...
	addState (new GameApplicationIntroState (this), __GAMESTATEINTRONAME__);
	addState (new GameApplicationSelectSquareState (this), __GAMESTATESELECTSQUARENAME__);
	addState (new GameApplicationPlayingState (this), __GAMESTATEPLAYINGNAME__);
	addState (new GameApplicationWinsState (this), __GAMESTATEWINNERNAME__);

	// ...adds the score objects
	addScoreObjects ();

	// The initial state is..just to play...
	setState (std::string (__GAMESTATEINTRONAME__));
}

//---
void GameApplication::finalize ()
{
	QGAMES::BoardGameApplication::finalize ();
	removeScoreObjects ();
}

// ---
void GameApplication::processEvent (const QGAMES::Event& e)
{
	QGAMES::Game::processEvent (e);
	// Let's notice the application does nothing when the notification about
	// WeHavaAWinner arrives. The action of changing the status of the game
	// is executed from the Bouy, after all pending instructions of a loop 
	// have been processed!
	if (e.code () == __CHANGESTATUSTOWIN__)
		setState (__GAMESTATEWINNERNAME__);
}
