#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Window/Window.h"
#include "../Timer/Timer.h"
#include "../MeshLoader/MeshLoader.h"
#include "../OBJLoader/OBJLoader.h"

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

	dx9::MeshLoader m_MeshLoader;

// TEST:
	ID3DXMesh* mesh = nullptr;
};

#endif // APPLICATION_H