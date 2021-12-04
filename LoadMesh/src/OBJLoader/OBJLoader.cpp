#include "../PrecompiledHeaders/stdafx.h"
#include "OBJLoader.h"

namespace dx9
{
// Constructors and Destructor:


	OBJLoader::OBJLoader()
	{
	}

	OBJLoader::~OBJLoader()
	{
	}


// Functions:

	bool8 OBJLoader::LoadOBJ(const char* filePath)
	{
	// Vertex positions:

		std::vector<D3DXVECTOR3> vertex_positions;
		std::vector<D3DXVECTOR2> vertex_texCoords;
		std::vector<D3DXVECTOR3> vertex_normals;

	// Face vectors:

		std::vector<uint32> vertex_position_indices;
		std::vector<uint32> vertex_texCoord_indices;
		std::vector<uint32> vertex_normal_indices;

	// Vertices:

		std::vector<Vertex> vertices;

	// Strings for file parsing:

		std::stringstream strStream;

		std::string line;
		std::string prefix;

		D3DXVECTOR3 temp_vec3;
		D3DXVECTOR2 temp_vec2;
		uint32 temp_uint32 = 0u;

		std::ifstream inFile;

		size_t NumVertexPos = 0u;
		size_t NumVertexTexCoords = 0u;
		size_t NumVertexNormals = 0u;

		inFile.open( filePath );

	// Parse OBJ file:

		if ( inFile.is_open() )
		{
		// Read one line at a time:

			while ( std::getline( inFile, line ) )
			{
			// Get prefix of the line:

				strStream.clear();

				strStream.str( line );

				strStream >> prefix;

				if ( prefix == "#" ) // Comment
				{

				}
				else if ( prefix == "o" ) // Object name
				{

				}
				else if ( prefix == "s" ) // Smoothing group
				{

				}
				else if ( prefix == "usemtl" ) // Material name
				{

				}
				else if ( prefix == "v" ) // Geometric Vertex
				{
					strStream >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;

					vertex_positions.push_back( temp_vec3 );
				}
				else if ( prefix == "vt" ) // Texture Vertex
				{
					strStream >> temp_vec2.x >> temp_vec2.y;

					vertex_texCoords.push_back( temp_vec2 );
				}
				else if ( prefix == "vn" ) // Vertex Normal
				{
					strStream >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;

					vertex_normals.push_back( temp_vec3 );
				}
				else if ( prefix == "f" ) // Face
				{
					uint32 counter = 0u;

					while ( strStream >> temp_uint32 )
					{
					// Push indices into correct vectore:

						if ( counter == 0u )
						{
							vertex_position_indices.push_back( temp_uint32 );
						}
						else if ( counter == 1u )
						{
							vertex_texCoord_indices.push_back( temp_uint32 );
						}
						else if ( counter == 2u )
						{
							vertex_normal_indices.push_back( temp_uint32 );
						}

					// Handle characters:

						if ( strStream.peek() == '/' )
						{
							counter++;

							strStream.ignore( 1, '/' );
						}
						else if ( strStream.peek() == ' ' )
						{
							counter++;

							strStream.ignore( 1, ' ' );
						}

					// Reset counter:

						if ( counter > 2u )
						{
							counter = 0u;
						}
					}
				}

			// Build final Vertex vector:

				vertices.resize( vertex_position_indices.size(), Vertex() );

				for ( size_t i = 0u; i < vertices.size(); i++ )
				{
					vertices[i].position     = vertex_positions[vertex_position_indices[i] - 1u];
					vertices[i].textureCoord = vertex_texCoords[vertex_texCoord_indices[i] - 1u];
					vertices[i].normal       = vertex_normals[vertex_normal_indices[i] - 1u];
				}

			// DEBUG:

				NumVertexPos       = vertex_positions.size();
				NumVertexTexCoords = vertex_texCoords.size();
				NumVertexNormals   = vertex_normals.size();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

}