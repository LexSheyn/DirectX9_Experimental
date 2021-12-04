#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../RenderSystem/D3DUtility.h"
#include "../RenderSystem/Vertex.h"

namespace dx9
{
	class OBJLoader
	{
	public:

	// Constructors and Destructor:

		OBJLoader();
		
		~OBJLoader();

	// Functions:

		bool8 LoadOBJ( const char* filePath );

	private:

	

	};
}

#endif // OBJLOADER_H