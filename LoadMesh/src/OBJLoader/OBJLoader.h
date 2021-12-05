#ifndef OBJLOADER_H
#define OBJLOADER_H

// Components:
#include "Position.h"
#include "TextureCoord.h"
#include "Normal.h"

// External dependancies:
#include "../RenderSystem/D3DUtility.h"
#include "../RenderSystem/Vertex.h"

namespace obj
{
	class OBJLoader
	{
	public:

	// Constructors and Destructor:

		OBJLoader();
		
		~OBJLoader();

	// Functions:

		/// <summary>
		/// Load Vertex positions, texture coordinates and normals from .obj file to the buffers.
		/// </summary>
		/// <param name="filePath"> - Full path to the .obj file.</param>
		/// <param name="capacity"> - Size of vertex array to store the vertices.</param>
		/// <returns>true if file has been opened successfully, otherwise returns false.</returns>
		bool8 LoadOBJ( const char* filePath, uint32 capacity );

		bool8 LoadOBJ( const char* filePath );

	private:

	

	};
}

#endif // OBJLOADER_H