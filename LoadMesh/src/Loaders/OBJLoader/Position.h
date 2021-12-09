#ifndef POSITION_H
#define POSITION_H

namespace obj
{
	class Position
	{
	public:

	// Constructors:

		Position();
		Position( float32 x, float32 y, float32 z );

	// Public Variables:

		float32 x;
		float32 y;
		float32 z;
	};
}

#endif // POSITION_H