#include "../PrecompiledHeaders/stdafx.h"
#include "Timer.h"

namespace dx9
{
// Constructor:

	Timer::Timer()
	{
		last = std::chrono::steady_clock::now();
	}

	float32 Timer::Mark()
	{
		const auto old = last;

		last = std::chrono::steady_clock::now();

		const std::chrono::duration<float> frame_time = last - old;

		return frame_time.count();
	}

	float32 Timer::Peek() const
	{
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
	}

}