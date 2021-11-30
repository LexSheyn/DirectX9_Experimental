#include "../../PrecompiledHeaders/stdafx.h"
#include "MouseEvent.h"

namespace dx9
{
// Constructors and Destructor:

	MouseEvent::MouseEvent() noexcept
		: type( Type::Invalid ),
		  b_LeftIsPressed(  false ),
		  b_RightIsPressed( false ),
		  x( 0 ),
		  y( 0 )
	{
	}

	MouseEvent::MouseEvent(Type type, const IMouse& parent) noexcept
		: type( type ),
		  b_LeftIsPressed(  parent.LeftIsPressed()  ),
		  b_RightIsPressed( parent.RightIsPressed() ),
		  x( parent.GetX() ),
		  y( parent.GetY() )
	{
	}

	MouseEvent::~MouseEvent()
	{
	}

}