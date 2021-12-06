#include "../PrecompiledHeaders/stdafx.h"
#include "FBXVector3F.h"

namespace fbx
{
// Constructor:

	FBXVector3F::FBXVector3F()
		: x(0.0f),
		  y(0.0f),
		  z(0.0f)
	{
	}

	FBXVector3F::FBXVector3F(float32 x, float32 y, float32 z)
		: x(x),
		  y(y),
		  z(z)
	{
	}

}