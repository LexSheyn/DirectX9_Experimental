#ifndef FBXVERTEX_H
#define FBXVERTEX_H

#include "FBXVector2F.h"
#include "FBXVector3F.h"

namespace fbx
{
	class FBXVertex
	{
	public:

	// Constructor:

		FBXVertex();
		FBXVertex( FBXVector3F position, FBXVector3F normal, FBXVector2F textureCoord );
		FBXVertex( float32 x, float32 y, float32 z, float32 nx, float32 ny, float32 nz, float32 u, float32 v );

	// Public Variables:

		FBXVector3F Position;
		FBXVector3F Normal;
		FBXVector2F TextureCoord;
	};
}

#endif // FBXVERTEX_H