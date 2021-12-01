#ifndef VERTEX_H
#define VERTEX_H

#include "Color.h"

namespace dx9
{
	class Vertex
	{
	public:

	// Constructor:

		Vertex() = default;
		Vertex( D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 textureCoord, D3DCOLOR color );
		Vertex( float32 x , float32 y , float32 z,
			    float32 nx, float32 ny, float32 nz, 
			    float32 u , float32 v, 
			    D3DCOLOR color);

	// Variables:

		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 textureCoord;

		D3DCOLOR color = Color::White;

		static const DWORD FVF;
	};
}

#endif // VERTEX_H