#ifndef __GAMEAPPIMPL_HPP__
#define __GAMEAPPIMPL_HPP__

#include <SDL/sdlgame.hpp>

/** Just the simple basic implementation, needed to create
	the input handler. It is based on SDL implementation. */
class GameApplicationImpl : public SDLGame
{
	public:
	GameApplicationImpl ()
		: SDLGame ()
							{ }

	virtual QGAMES::InputHandler* createInputHandler ();
};

#endif
