#include "../../PrecompiledHeaders/stdafx.h"
#include "FBXVector2F.h"

namespace fbx
{
// Constructor:

	FBXVector2F::FBXVector2F()
		: x(0.0f),
		  y(0.0f)
	{
	}

	FBXVector2F::FBXVector2F(float32 x, float32 y)
		: x(x),
		  y(y)
	{
	}

}