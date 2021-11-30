#include "../../PrecompiledHeaders/stdafx.h"
#include "Mouse.h"

namespace dx9
{
// Functions:

	MouseEvent Mouse::Read() noexcept
	{
		if ( m_Buffer.size() > 0u )
		{
			MouseEvent mouse_event = m_Buffer.front();

			m_Buffer.pop();

			return mouse_event;
		}

		return MouseEvent();
	}

	void Mouse::Flush() noexcept
	{
		m_Buffer = std::queue<MouseEvent>();
	}


// Private Functions:

	void Mouse::OnMouseMove(int32 _x, int32 _y) noexcept
	{
		x = _x;
		y = _y;

		m_Buffer.push( MouseEvent( MouseEvent::Type::Move, *this ) );

		this->TrimBuffer();
	}

	void Mouse::OnMouseLeave() noexcept
	{
		b_IsInWindow = false;

		m_Buffer.push( MouseEvent( MouseEvent::Type::Leave, *this ) );

		this->TrimBuffer();
	}

	void Mouse::OnMouseEnter() noexcept
	{
		b_IsInWindow = true;

		m_Buffer.push( MouseEvent( MouseEvent::Type::Enter, *this ) );

		this->TrimBuffer();
	}

	void Mouse::OnLeftPress(int32 _x, int32 _y) noexcept
	{
		b_LeftIsPressed = true;

		m_Buffer.push( MouseEvent( MouseEvent::Type::LPress, *this ) );

		this->TrimBuffer();
	}

	void Mouse::OnLeftRelease(int32 _x, int32 _y) noexcept
	{
		b_LeftIsPressed = false;

		m_Buffer.push(MouseEvent(MouseEvent::Type::LRelease, *this));

		this->TrimBuffer();
	}

	void Mouse::OnRightPress(int32 _x, int32 _y) noexcept
	{
		b_RightIsPressed = true;

		m_Buffer.push(MouseEvent(MouseEvent::Type::RPress, *this));

		this->TrimBuffer();
	}

	void Mouse::OnRightRelease(int32 _x, int32 _y) noexcept
	{
		b_RightIsPressed = false;

		m_Buffer.push(MouseEvent(MouseEvent::Type::RRelease, *this));

		this->TrimBuffer();
	}

	void Mouse::OnWheelUp(int32 _x, int32 _y) noexcept
	{
		m_Buffer.push( MouseEvent( MouseEvent::Type::WheelUp, *this ) );

		this->TrimBuffer();
	}

	void Mouse::OnWheelDown(int32 _x, int32 _y) noexcept
	{
		m_Buffer.push(MouseEvent(MouseEvent::Type::WheelDown, *this));

		this->TrimBuffer();
	}

	void Mouse::OnWheelDelta(int32 _x, int32 _y, int32 _delta) noexcept
	{
		m_WheelDeltaCarry += _delta;

	// Generate events every 120 ( WHEEL_DELTA ):

		while ( m_WheelDeltaCarry >= WHEEL_DELTA )
		{
			m_WheelDeltaCarry -= WHEEL_DELTA;

			this->OnWheelUp( _x, _y );
		}

		while ( m_WheelDeltaCarry <= -WHEEL_DELTA )
		{
			m_WheelDeltaCarry += WHEEL_DELTA;

			this->OnWheelDown( _x, _y );
		}
	}

	void Mouse::TrimBuffer() noexcept
	{
		while ( m_Buffer.size() > m_BufferSize )
		{
			m_Buffer.pop();
		}
	}
}