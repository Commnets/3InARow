#ifndef __ENTITIES_HPP__
#define __ENTITIES_HPP__

#include <Common/entity.hpp>
#include "Defs.hpp"

/** Just the entity appearing in the game. */
class EntityAnimating3InARow : public QGAMES::Entity
{
	public:
	EntityAnimating3InARow (const QGAMES::Forms& f = QGAMES::Forms (), 
		const QGAMES::Entity::Data& d = QGAMES::Entity::Data ())
		: QGAMES::Entity (__ENTITYANIMATING3INAROW__, f, d)
							{ }

	virtual QGAMES::Entity* clone ();
};

#endif