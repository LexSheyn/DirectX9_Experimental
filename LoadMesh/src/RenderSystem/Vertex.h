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
		Vertex( float32 x, float32 y, float32 z );
		Vertex( float32 x, float32 y, float32 z, D3DCOLOR color );

	// Variables:

		float32 x = 0.0f;
		float32 y = 0.0f;
		float32 z = 0.0f;

		D3DCOLOR color = Color::White;

		static const DWORD FVF;
	};
}

#endif // VERTEX_H