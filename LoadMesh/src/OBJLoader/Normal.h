#ifndef NORMAL_H
#define NORMAL_H

namespace obj
{
	class Normal
	{
	public:

	// Constructors:

		Normal();
		Normal( float32 x, float32 y, float32 z );

	// Public Variables:

		float32 x;
		float32 y;
		float32 z;
	};
}

#endif // NORMAL_H