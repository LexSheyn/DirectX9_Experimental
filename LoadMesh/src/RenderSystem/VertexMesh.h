#ifndef VERTEXMESH_H
#define VERTEXMESH_H

namespace dx9
{
	class VertexMesh
	{
	public:

	// Constructor:

		VertexMesh() = default;
		VertexMesh( D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 textureCoord);
		VertexMesh( float32 x , float32 y , float32 z,
			        float32 nx, float32 ny, float32 nz, 
			        float32 u , float32 v);

	// Variables:

		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 textureCoord;

		static const DWORD FVF;
	};
}

#endif // VERTEXMESH_H