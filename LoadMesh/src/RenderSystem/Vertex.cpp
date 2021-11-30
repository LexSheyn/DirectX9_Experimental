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

	Vertex::Vertex(float32 x, float32 y, float32 z, D3DCOLOR color)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		this->color = color;
	}

	const DWORD Vertex::FVF = D3DFVF_XYZ;
}