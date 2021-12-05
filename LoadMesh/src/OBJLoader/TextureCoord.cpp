#include "../PrecompiledHeaders/stdafx.h"
#include "TextureCoord.h"

namespace obj
{
// Constructors:

	TextureCoord::TextureCoord()
	{
		u = 0.0f;
		v = 0.0f;
	}

	TextureCoord::TextureCoord(float32 u, float32 v)
	{
		this->u = u;
		this->v = v;
	}

}