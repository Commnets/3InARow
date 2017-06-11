#include "GameAppImpl.hpp"
#include "InputHandler.hpp"

// ---
QGAMES::InputHandler* GameApplicationImpl::createInputHandler ()
{
	return (new InputHandler (_game));
}
