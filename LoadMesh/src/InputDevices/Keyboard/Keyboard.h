#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "KeyEvent.h"

namespace dx9
{
	class Keyboard
	{
		friend class Window;

	public:

	// Constructors and Destructor:

		Keyboard() = default;
		Keyboard( const Keyboard& ) = delete;

		~Keyboard() {}

	// Operators:

		Keyboard& operator=( const Keyboard& ) = delete;

	// Functions for Key Event:

		bool8    KeyIsPressed( uint8 key_code ) const noexcept;

		KeyEvent ReadKey()          noexcept;

		bool8    KeyIsEmpty() const noexcept;

		void     FlushKey()         noexcept;

	// Functions for Char Event:

		char8 ReadChar()          noexcept;

		bool8 CharIsEmpty() const noexcept;

		void  FlushChar()         noexcept;

		void  Flush()             noexcept;

	// Functions for autorepeat control:

		void  EnableAutorepeat()  noexcept;

		void  DisableAutorepeat() noexcept;

		const bool8& AutorepeatIsEnabled() const noexcept;

	private:

	// Private Functions:

		void OnKeyPress(   uint8 key_code ) noexcept;

		void OnKeyRelease( uint8 key_code ) noexcept;

		void OnChar( char8 character )      noexcept;

		void ClearState() noexcept;

		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept
		{
			while (buffer.size() > m_BufferSize)
			{
				buffer.pop();
			}
		}

	// Variables:

		static constexpr uint32 m_KeysNumber = 256u;

		static constexpr uint32 m_BufferSize = 16u;

		bool8 m_AutorepeatEnabled = false;

		std::bitset<m_KeysNumber> m_KeyStates;

		std::queue<KeyEvent> m_KeyBuffer;
		std::queue<char8>    m_CharBuffer;
	};
}

#endif // KEYBOARD_H