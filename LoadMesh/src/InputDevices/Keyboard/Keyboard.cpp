#include "../../PrecompiledHeaders/stdafx.h"
#include "Keyboard.h"

namespace dx9
{
// Functions for Key Event:

	bool8 Keyboard::KeyIsPressed(uint8 key_code) const noexcept
	{
		return m_KeyStates[key_code];
	}

	KeyEvent Keyboard::ReadKey() noexcept
	{
		if ( m_KeyBuffer.size() > 0u )
		{
			KeyEvent keyboard_event = m_KeyBuffer.front();
			
			m_KeyBuffer.pop();

			return keyboard_event;
		}

		return KeyEvent();
	}

	bool8 Keyboard::KeyIsEmpty() const noexcept
	{
		return m_KeyBuffer.empty();
	}

	void Keyboard::FlushKey() noexcept
	{
		m_KeyBuffer = std::queue<KeyEvent>();
	}


// Functions for Char Event:

	char8 Keyboard::ReadChar() noexcept
	{
		if ( m_CharBuffer.size() > 0u )
		{
			uint8 char_code = m_CharBuffer.front();

			m_CharBuffer.pop();

			return char_code;
		}

		return 0;
	}

	bool8 Keyboard::CharIsEmpty() const noexcept
	{
		return m_CharBuffer.empty();
	}

	void Keyboard::FlushChar() noexcept
	{
		m_CharBuffer = std::queue<char8>();
	}

	void Keyboard::Flush() noexcept
	{
		this->FlushKey();
		this->FlushChar();
	}


// Functions for autorepeat control:

	void Keyboard::EnableAutorepeat() noexcept
	{
		m_AutorepeatEnabled = true;
	}

	void Keyboard::DisableAutorepeat() noexcept
	{
		m_AutorepeatEnabled = false;
	}

	const bool8& Keyboard::AutorepeatIsEnabled() const noexcept
	{
		return m_AutorepeatEnabled;
	}


// Private Functions:

	void Keyboard::OnKeyPress(uint8 key_code) noexcept
	{
		m_KeyStates[key_code] = true;

		m_KeyBuffer.push( KeyEvent( KeyEvent::Type::Press, key_code ) );

		this->TrimBuffer( m_KeyBuffer );
	}

	void Keyboard::OnKeyRelease(uint8 key_code) noexcept
	{
		m_KeyStates[key_code] = false;

		m_KeyBuffer.push( KeyEvent( KeyEvent::Type::Release, key_code));

		this->TrimBuffer( m_KeyBuffer );
	}

	void Keyboard::OnChar(char8 character) noexcept
	{
		m_CharBuffer.push( character );

		this->TrimBuffer( m_CharBuffer );
	}

	void Keyboard::ClearState() noexcept
	{
		m_KeyStates.reset();
	}
}