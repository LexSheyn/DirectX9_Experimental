#ifndef FBXVECTOR3F_H
#define FBXVECTOR3F_H

namespace fbx
{
	class FBXVector3F
	{
	public:

	// Constructor:

		FBXVector3F();
		FBXVector3F( float32 x, float32 y, float32 z );

	// Public Varoables:

		float32 x;
		float32 y;
		float32 z;
	};
}

#endif // FBXVECTOR3F_H