#ifndef TIMER_H
#define TIMER_H

namespace dx9
{
	class Timer
	{
	public:

	// Constructor:

		Timer();

	// Functions:

		float32 Mark();
		
		float32 Peek() const;

	private:

	// Variables:

		std::chrono::steady_clock::time_point last;
	};
}

#endif // TIMER_H