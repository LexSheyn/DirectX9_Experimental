#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "../RenderSystem/D3DUtility.h"
#include "../RenderSystem/Vertex.h"

namespace 
{
	class MeshLoader
	{
	public:

	// Constructors and Destructor:

		MeshLoader();
		MeshLoader( HWND hWnd );

		~MeshLoader();

	// Functions:

		bool8 LoadMesh( const char* filePath );

	// Accessors:

		std::vector<ID3DXMesh*>& GetMeshes();

	// Modifiers:

		void SetOutputWindow( HWND hWnd );

		void SetD3DDevice( IDirect3DDevice9* pDevice );

	private:

	// Private Functions:

		ID3DXMesh* CopyMesh( aiMesh* iMesh );

	// Variables:

		HWND phWnd = nullptr;

		IDirect3DDevice9* pDevice = nullptr;

		std::vector<ID3DXMesh*> m_Meshes;
	};
}

#endif // MESHLOADER