#include "../../PrecompiledHeaders/stdafx.h"
#include "KeyEvent.h"

namespace dx9
{
// Constructors and Destructor:

	KeyEvent::KeyEvent() noexcept
		: type( Type::Invalid ),
		  code( 0u )
	{
	}

	KeyEvent::KeyEvent( Type type, uint8 code ) noexcept
		: type( type ),
		  code( code )
	{
	}

	KeyEvent::~KeyEvent()
	{
	}

}