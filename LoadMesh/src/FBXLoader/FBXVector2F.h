#ifndef FBXVECTOR2F_H
#define FBXVECTOR2F_H

namespace fbx
{
	class FBXVector2F
	{
	public:

	// Constructor:

		FBXVector2F();
		FBXVector2F( float32 x, float32 y );

	// Public Varoables:

		float32 x;
		float32 y;
	};
}

#endif // FBXVECTOR2F_H