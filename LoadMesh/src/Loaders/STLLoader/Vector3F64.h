#ifndef VECTOR3F64_H
#define VECTOR3F64_H

namespace stl
{
	class Vector3F64
	{
	public:

	// Constuctors:

		Vector3F64();
		Vector3F64( float64 x, float64 y, float64 z );

	// Public Variables:

		float64 x;
		float64 y;
		float64 z;
	};
}

#endif // VECTOR3F64_H