#include "../PrecompiledHeaders/stdafx.h"
#include "Vertex.h"

namespace dx9
{
// Constructor:	
	
	Vertex::Vertex()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		position.z = 0.0f;

		normal.x = 0.0f;
		normal.y = 0.0f;
		normal.z = 0.0f;

		textureCoord.x = 0.0f;
		textureCoord.y = 0.0f;
	}

	Vertex::Vertex(D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 textureCoord)
	{
		this->position     = position;

		this->normal       = normal;

		this->textureCoord = textureCoord;
	}

	Vertex::Vertex( float32 x , float32 y , float32 z,
		            float32 nx, float32 ny, float32 nz,
		            float32 u , float32 v )
	{
		position.x = x;
		position.y = y;
		position.z = z;
		
		normal.x = x;
		normal.y = y;
		normal.z = z;

		textureCoord.x = u;
		textureCoord.y = v;
	}


// Static Variables:

	const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
}