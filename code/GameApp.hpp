#ifndef __GAMEAPP_HPP__
#define __GAMEAPP_HPP__

#include <Board/boardgameapp.hpp>
#include "GameAppImpl.hpp"

/** The implementation of the application. */
class GameApplication : public QGAMES::BoardGameApplication
{
	public:
	GameApplication ();

	virtual void addScoreObjects ();
	virtual void removeScoreObjects ();

	void reset ();

	private:
	virtual QGAMES::FormBuilder* createFormBuilder ();
	virtual QGAMES::ObjectBuilder* createObjectBuilder ();
	virtual QGAMES::EntityBuilder* createEntityBuilder ();
	virtual QGAMES::MovementBuilder* createMovementBuilder ();
	virtual QGAMES::SoundBuilder* createSoundBuilder ();
	virtual QGAMES::Timer* createTimer ();
	virtual QGAMES::Screens createScreens ();
	virtual QGAMES::BoardBuilder* createBoardBuilder ();
	virtual QGAMES::BoardGame* createBoardGame ();

	virtual void initialize ();
	virtual void finalize ();
	
	virtual void processEvent (const QGAMES::Event& e);
};

#endif