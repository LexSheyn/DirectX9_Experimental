#ifndef TEXTURECOORD_H
#define TEXTURECOORD_H

namespace obj
{
	class TextureCoord
	{
	public:

	// Constructors:

		TextureCoord();
		TextureCoord( float32 u, float32 v );

	// Public Variables:

		float32 u;
		float32 v;
	};
}

#endif // TEXTURECOORD_H