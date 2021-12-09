#include "../../PrecompiledHeaders/stdafx.h"
#include "Position.h"

namespace obj
{
// Constructors:

	Position::Position()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Position::Position(float32 x, float32 y, float32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

}