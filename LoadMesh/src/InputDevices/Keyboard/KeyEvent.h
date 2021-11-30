#ifndef KEYEVENT_H
#define KEYEVENT_H

namespace dx9
{
	class KeyEvent
	{
	public:

	// KeyEvent types:

		enum class Type : int32
		{
			Press = 0,
			Release,
			Invalid
		};

	// Constructors and Destructor:

		KeyEvent() noexcept;
		KeyEvent( Type type, uint8 code ) noexcept;

		~KeyEvent();

	// Accessors:

		inline       bool8  IsPressed()  const noexcept { return type == Type::Press;   }

		inline       bool8  IsReleased() const noexcept { return type == Type::Release; }

		inline       bool8  IsValid()    const noexcept { return type != Type::Invalid; }

		inline const uint8& GetCode()    const noexcept { return code; }

	private:

	// Variables:

		Type  type;
		uint8 code;
	};
}

#endif // KEYEVENT_H