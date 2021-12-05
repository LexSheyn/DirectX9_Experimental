#include "../PrecompiledHeaders/stdafx.h"
#include "Normal.h"

namespace obj
{
// Constructors:

	Normal::Normal()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Normal::Normal(float32 x, float32 y, float32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

}