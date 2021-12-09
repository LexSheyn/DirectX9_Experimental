#include "../../PrecompiledHeaders/stdafx.h"
#include "Vector3F64.h"

namespace stl
{
// Constructors:

	Vector3F64::Vector3F64()
		: x ( 0.0 ),
		  y ( 0.0 ),
		  z ( 0.0 )
	{
	}

	Vector3F64::Vector3F64(float64 x, float64 y, float64 z)
		: x ( x ),
		  y ( y ),
		  z ( z )
	{
	}

}