#include "../PrecompiledHeaders/stdafx.h"
#include "FBXLoader.h"

namespace fbx
{
// Constructors and Destructor:

	FBXLoader::FBXLoader()
		: m_phWnd( nullptr ),
		  m_ErrorCode( 0u )
	{
	// TEST CODE:

	// Change the following filename to a suitable filename value.

		const char* lFilename = "D:/Models/xinyan-fbx/source/Xinyan/Model/Xinyan.fbx";

	// Initialize the SDK manager. This object handles memort managment.

		FbxManager* lSdkManager = FbxManager::Create();

	// Create the IO settings object.

		FbxIOSettings* ioSettings = FbxIOSettings::Create( lSdkManager, IOSROOT );

		lSdkManager->SetIOSettings( ioSettings );

	// Create an importer using the SDK manager.

		FbxImporter* lImporter = FbxImporter::Create( lSdkManager, "" );

	// Use the first argument as the filename for the importer.

		if ( !lImporter->Initialize( lFilename, -1, lSdkManager->GetIOSettings() ) )
		{
			std::ostringstream errorMessage;

			errorMessage << "ERROR::Constructor::Call to FbxImporter::Initialize() failed."
				         << "\n" << "Error returned: " << lImporter->GetStatus().GetErrorString();

			MessageBoxA( m_phWnd, errorMessage.str().c_str(), "FBXLoader", 0u );

			return;
		}

	// Create a new scene so that it can be populated by the imported file.

		FbxScene* lScene = FbxScene::Create( lSdkManager, "NewScene1" );

	// Import the contents of the file into the scene.

		lImporter->Import( lScene );

	// The file is imported, so get rid of the importer.

		lImporter->Destroy();
	}

	FBXLoader::FBXLoader(HWND phWnd)
		: m_phWnd( phWnd ),
		  m_ErrorCode( 0u )
	{
	}

	FBXLoader::~FBXLoader()
	{
		m_phWnd = nullptr;
	}


// Functions:

	const uint32& FBXLoader::LoadFBX(const char* filePath) const
	{
		// To do... FBX SDK required...

		return m_ErrorCode;
	}


// Modifiers:

	void FBXLoader::SetWindowHandle( HWND phWnd )
	{
		m_phWnd = phWnd;
	}


// Private Functions:

	void FBXLoader::ClearBuffers()
	{
	// Vertices:

		m_Vertices.clear();

	// Indices:

		m_Indices.clear();

	// Materials:

		// To do...
	}

}