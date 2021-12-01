#include "../PrecompiledHeaders/stdafx.h"
#include "Vertex.h"

namespace dx9
{
// Constructor:	
	
	Vertex::Vertex(D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DCOLOR color)
	{
		this->position = position;

		this->normal   = normal;

		this->color    = color;
	}

	Vertex::Vertex(float32 x , float32 y , float32 z, 
		           float32 nx, float32 ny, float32 nz, 
		           D3DCOLOR color)
	{
		position.x = x;
		position.y = y;
		position.z = z;

		normal.x = x;
		normal.y = y;
		normal.z = z;

		this->color = color;
	}


// Static Variables:

	const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
}