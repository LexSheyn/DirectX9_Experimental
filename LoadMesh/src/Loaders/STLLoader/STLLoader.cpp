#include "../../PrecompiledHeaders/stdafx.h"
#include "STLLoader.h"

namespace stl
{
// Constructors and Destructor:

	STLLoader::STLLoader()
		: m_VerticesAmount( static_cast<uint32>( m_Vertices.size() ) ),
		  m_FacesAmount( 0u )
	{
	}

	STLLoader::~STLLoader()
	{
		this->ClearBuffer();
	}


// Functions:

	uint32 STLLoader::LoadSTL(const char* pathToSTL)
	{
	// Clear buffer first:

		this->ClearBuffer();

	// Temporary vectors to store positions and normals, textures are not supported by STL:

		std::vector<Vector3F64> positions;
		std::vector<Vector3F64> normals;

	// Strings for file parsing:

		std::istringstream inStrStream;

		std::string line;
		std::string prefix;

		Vector3F64 temp_position;
		Vector3F64 temp_normal;

		std::ifstream inFile;

		inFile.open( pathToSTL );

		if ( inFile.is_open() )
		{
		// Read one line at a time:

			while ( std::getline( inFile, line ) )
			{
			// Get prefix of the line:

				inStrStream.clear();

				inStrStream.str( line );

				inStrStream >> prefix;

				if ( prefix == "facet" ) // Face and Normal
				{
					m_FacesAmount++;

					inStrStream.ignore( 8 );

					inStrStream >> temp_normal.x >> temp_normal.y >> temp_normal.z;

				// Always has same normal coordinates for every vertex of the face:

					normals.push_back( temp_normal );
					normals.push_back( temp_normal );
					normals.push_back( temp_normal );
				}
				else if ( prefix == "vertex" ) // Vertex position
				{
					inStrStream >> temp_position.x >> temp_position.y >> temp_position.z;

					positions.push_back( temp_position );
				}
			}

		// Construct the Vertices:

			m_Vertices.resize( positions.size() );

			for ( size_t i = 0u; i < m_Vertices.size(); i++ )
			{
			// Position:

				m_Vertices[i].position.x = static_cast<float32>( positions[i].x );
				m_Vertices[i].position.y = static_cast<float32>( positions[i].y );
				m_Vertices[i].position.z = static_cast<float32>( positions[i].z );

			// Normal:
				
				m_Vertices[i].normal.x = static_cast<float32>( normals[i].x );
				m_Vertices[i].normal.y = static_cast<float32>( normals[i].y );
				m_Vertices[i].normal.z = static_cast<float32>( normals[i].z );

			// Texture coordinates always 0, not supported by STL:

				m_Vertices[i].textureCoord.x = 0.0f;
				m_Vertices[i].textureCoord.y = 0.0f;
			}
		}
		else
		{
			return 1; // Error code enum here..
		}

		inFile.close();

		return 0u; // Error code enum here..
	}

	void STLLoader::ClearBuffer()
	{
		if ( !m_Vertices.empty() )
		{
			m_Vertices.clear();

			m_VerticesAmount = static_cast<uint32>( m_Vertices.size() );

			m_FacesAmount = 0u;
		}
	}

}