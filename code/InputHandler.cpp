#include "InputHandler.hpp"
#include "Defs.hpp"
#include "GameAppStates.hpp"

// ---
void InputHandler::onJoystickAxisMoveEvent (QGAMES::JoystickMovementEventData* dt)
{
}

// ---
void InputHandler::onJoystickButtonEvent (QGAMES::JoystickButtonEventData* dt)
{

}

// ---
void InputHandler::onKeyboardEvent (QGAMES::KeyboardEventData* dt)
{
	int kPressed = -1;
	bool pKey = false;
	if (_lastKey != -1)
	{
		if (!dt -> _on)
		{
			kPressed = _lastKey;
			_lastKey = -1;
			pKey = true;
		}
	}
	else
		_lastKey = dt -> _key;

	if (pKey)
	{
		int gS = _game -> activeState () -> type ();
		switch (gS)
		{
			case __GAMESTATEINTRO__:
				manageKeyOnIntroState (kPressed);
				break;

			case __GAMESTATESELECTSQUARE__:
				manageKeyOnSelectSquareState (kPressed);
				break;

			case __GAMESTATEPLAYING__:
				manageKeyOnPlayingState (kPressed);
				break;

			case __GAMESTATEWINNER__:
				manageKeyOnWinState (kPressed);
				break;

			default:
				break;
		};
	}
}

// ---
void InputHandler::onMouseMovementEvent (QGAMES::MouseMovementEventData* dt)
{
}

// ---
void InputHandler::onMouseButtonEvent (QGAMES::MouseButtonEventData* dt)
{
	int gS = _game -> activeState () -> type ();
	switch (gS)
	{
		case __GAMESTATESELECTSQUARE__:
			{
				QGAMES::MouseMovementEventData mPos = whereIsMouse ();
				if (dt -> _on == false)
					((GameApplicationSelectSquareState*) _game -> activeState ()) 
						-> squareSelectedOn (mPos._x, mPos._y);
				else
					((GameApplicationSelectSquareState*) _game -> activeState ()) 
						-> squareClickedOn (mPos._x, mPos._y);
			}

			break;

		default:
			break;
	}
}

// ---
void InputHandler::manageKeyOnIntroState (int k)
{
	// What ever the ky is...I want to exit the state...
	((GameApplicationIntroState*) _game -> activeState ()) -> setWantToExit (true);
}

// ---
void InputHandler::manageKeyOnSelectSquareState (int k)
{
	if (k == SDL_SCANCODE_RETURN)
		((GameApplicationSelectSquareState*) _game -> activeState ()) -> squareSelected ();
	else
	if (k == SDL_SCANCODE_LEFT)
		((GameApplicationSelectSquareState*) _game -> activeState ()) -> squareLeft ();
	else
	if (k == SDL_SCANCODE_RIGHT)
		((GameApplicationSelectSquareState*) _game -> activeState ()) -> squareRight ();
	else
	if (k == SDL_SCANCODE_UP)
		((GameApplicationSelectSquareState*) _game -> activeState ()) -> squareUp ();
	else
	if (k == SDL_SCANCODE_DOWN)
		((GameApplicationSelectSquareState*) _game -> activeState ()) -> squareDown ();
}

// ---
void InputHandler::manageKeyOnPlayingState (int k)
{
}

// ---
void InputHandler::manageKeyOnWinState (int k)
{
	// What ever the ky is...I want to exit the state...
	((GameApplicationWinsState*) _game -> activeState ()) -> setWantToExit (true);
}

