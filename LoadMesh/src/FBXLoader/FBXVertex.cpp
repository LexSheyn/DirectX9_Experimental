#include "../PrecompiledHeaders/stdafx.h"
#include "FBXVertex.h"

namespace fbx
{
// Constructor:

	FBXVertex::FBXVertex()
		: Position( FBXVector3F() ),
		  Normal( FBXVector3F() ),
		  TextureCoord( FBXVector2F() )
	{
	}

	FBXVertex::FBXVertex( FBXVector3F position, FBXVector3F normal, FBXVector2F textureCoord )
		: Position( position ),
		  Normal( normal ),
		  TextureCoord( textureCoord )
	{
	}

	FBXVertex::FBXVertex( float32 x, float32 y, float32 z, float32 nx, float32 ny, float32 nz, float32 u, float32 v )
		: Position( x, y, z ),
		  Normal( nx, ny, nz ),
		  TextureCoord( u, v )
	{
	}

}