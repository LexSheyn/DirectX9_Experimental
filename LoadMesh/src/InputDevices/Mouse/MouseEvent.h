#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Interface/IMouse.h"

namespace dx9
{
	class MouseEvent
	{
	public:

	// Event Types:

		enum class Type : int32
		{
			LPress = 0,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};

	// Constructors and Destructor:

		MouseEvent() noexcept;
		MouseEvent( Type type, const IMouse& parent ) noexcept;

		~MouseEvent();

	// Accessors:

		inline                   bool8 IsValid()        const noexcept { return type != Type::Invalid; }

		inline            const  Type& GetType()        const noexcept { return type; }

		inline std::pair<int32, int32> GetPosition()    const noexcept { return { x, y }; }

		inline            const int32& GetX()           const noexcept { return x; }

		inline            const int32& GetY()           const noexcept { return y; }

		inline            const bool8& LeftIsPressed()  const noexcept { return b_LeftIsPressed; }

		inline            const bool8& RightIsPressed() const noexcept { return b_RightIsPressed; }

	private:

	// Variables:

		Type  type;

		bool8 b_LeftIsPressed;
		bool8 b_RightIsPressed;

		int32 x;
		int32 y;
	};
}

#endif // MOUSEEVENT_H