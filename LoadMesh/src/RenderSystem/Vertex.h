#ifndef VERTEX_H
#define VERTEX_H

namespace dx9
{
	class Vertex
	{
	public:

	// Constructor:

		Vertex() = default;
		Vertex( D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 textureCoord);
		Vertex( float32 x , float32 y , float32 z,
			    float32 nx, float32 ny, float32 nz, 
			    float32 u , float32 v);

	// Variables:

		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 textureCoord;

		static const DWORD FVF;
	};
}

#endif // VERTEX_H