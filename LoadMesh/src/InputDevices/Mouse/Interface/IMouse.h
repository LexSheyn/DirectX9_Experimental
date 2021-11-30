#ifndef IMOUSE_H
#define IMOUSE_H

namespace dx9
{
	class IMouse
	{
	public:

	// Accessors:

		virtual const int32& GetX() const noexcept = 0;

		virtual const int32& GetY() const noexcept = 0;

		virtual const bool8& IsInWindow() const noexcept = 0;

		virtual const bool8& LeftIsPressed()  const noexcept = 0;

		virtual const bool8& RightIsPressed() const noexcept = 0;
	};
}

#endif // IMOUSE_H