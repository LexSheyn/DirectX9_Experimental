#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Window/Window.h"
#include "../Timer/Timer.h"

namespace dx9
{
	class Application
	{
	public:

	// Constructors and Destructor:

		Application();

		~Application();

	// Functions:

		int32 Run();

	private:

	// Private Functions:

		void DoFrame();

	// Components:

		Window m_Window;
		Timer  m_Timer;

	// TEST:
		ID3DXMesh* mesh = nullptr;
	};
}

#endif // APPLICATION_H