#ifndef __INPUTHANDLER_HPP__
#define __INPUTHANDLER_HPP__

#include <SDL/sdlinputhandler.hpp>

/** JUst the input hadler. */
class InputHandler : public SDLInputHandler
{
	public:
	InputHandler (QGAMES::Game* g)
		: SDLInputHandler (g),
		  _lastKey (-1)
							{ }

	virtual void onJoystickAxisMoveEvent (QGAMES::JoystickMovementEventData* dt);
	virtual void onJoystickButtonEvent (QGAMES::JoystickButtonEventData* dt);
	virtual void onKeyboardEvent (QGAMES::KeyboardEventData* dt);
	virtual void onMouseMovementEvent (QGAMES::MouseMovementEventData* dt);
	virtual void onMouseButtonEvent (QGAMES::MouseButtonEventData* dt);

	private:
	void manageKeyOnIntroState (int k);
	void manageKeyOnSelectSquareState (int k);
	void manageKeyOnPlayingState (int k);
	void manageKeyOnWinState (int k);

	private:
	int _lastKey;
};

#endif