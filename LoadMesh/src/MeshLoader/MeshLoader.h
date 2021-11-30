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

	private:

	// Variables:

		HWND m_hWnd = nullptr;
	};
}

#endif // MESHLOADER