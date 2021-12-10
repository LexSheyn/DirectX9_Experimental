#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Window/Window.h"
#include "../Timer/Timer.h"
#include "../Loaders/OBJLoader/OBJLoader.h"
#include "../Loaders/STLLoader/STLLoader.h"

#include "../GUI/Menu.h"

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

	dx9::Window m_Window;
	dx9::Timer  m_Timer;

// TEST:

	dx9::Mesh Meshes[3];

	obj::OBJLoader m_OBJLoader;

	stl::STLLoader m_STLLoader;
};

#endif // APPLICATION_H