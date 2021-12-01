#include "../PrecompiledHeaders/stdafx.h"
#include "VertexMesh.h"

namespace dx9
{
// Constructor:	
	
	VertexMesh::VertexMesh(D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 textureCoord)
	{
		this->position     = position;

		this->normal       = normal;

		this->textureCoord = textureCoord;
	}

	VertexMesh::VertexMesh(float32 x , float32 y , float32 z,
		                   float32 nx, float32 ny, float32 nz,
		                   float32 u , float32 v)
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

	const DWORD VertexMesh::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
}