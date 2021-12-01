#ifndef MESHLOADER_H
#define MESHLOADER_H

namespace dx9
{
	class MeshLoader
	{
	public:

	// Constructors and Destructor:

		MeshLoader();
		MeshLoader( HWND hWnd );

		~MeshLoader();

	// Functions:

		bool8 Load( const char* filePath );

		void GetMeshes( std::vector<ID3DXMesh*>& meshes );

	private:

	// Variables:

		HWND m_hWnd = nullptr;

		std::vector<ID3DXMesh*> m_Meshes;
	};
}

#endif // MESHLOADER