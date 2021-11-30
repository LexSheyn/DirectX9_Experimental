#include "../PrecompiledHeaders/stdafx.h"
#include "Vertex.h"

namespace dx9
{
// Constructor:

	Vertex::Vertex(float32 x, float32 y, float32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	const DWORD Vertex::FVF = D3DFVF_XYZ;
}