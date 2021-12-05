#include "../PrecompiledHeaders/stdafx.h"
#include "OBJLoader.h"

namespace obj
{
// Constructors and Destructor:


	OBJLoader::OBJLoader()
	{
	}

	OBJLoader::~OBJLoader()
	{
		this->ClearBuffers();
	}


// Functions:

	bool8 OBJLoader::LoadOBJ(const char* filePath, const uint32 capacity)
	{
	// Clear buffers before allocationg new memory:

		this->ClearBuffers();

	// Create dynamic arrays for temporary store .obj data:

		Position* positions = new Position[capacity];
		uint32    positions_counter = 0u;

		TextureCoord* texCoords = new TextureCoord[capacity];
		uint32        texCoords_counter = 0u;

		Normal* normals = new Normal[capacity];
		uint32  normals_counter = 0u;


		uint32* indices_position = new uint32[capacity];
		uint32  indices_position_counter = 0u;

		uint32* indices_texCoord = new uint32[capacity];
		uint32  indices_texCoord_counter = 0u;

		uint32* indices_normal   = new uint32[capacity];
		uint32  indices_normal_counter = 0u;

		uint32 temp_index = 0u;

	// Create strings and input file stream for file parsing:

		std::istringstream inStrStream;

		std::string line;
		std::string prefix;

		std::ifstream inFileStream;

		inFileStream.open( filePath );

		if ( inFileStream.is_open() )
		{
		// Read one line at a time:

			while ( std::getline( inFileStream, line ) )
			{
			// Get prefix of the line:

				inStrStream.clear();
				inStrStream.str( line );
				inStrStream >> prefix;

			// Disable notification about possible buffer overflow, this will never happen with x32 bit application:

				#pragma warning( push ) // C6835
				#pragma warning( disable : 6385)

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
					inStrStream >> positions[positions_counter].x >> positions[positions_counter].y >> positions[positions_counter].z;

					positions_counter++;
				}
				else if ( prefix == "vt" ) // Texture Vertex
				{
					inStrStream >> texCoords[texCoords_counter].u >> texCoords[texCoords_counter].v;

					texCoords_counter++;
				}
				else if ( prefix == "vn" ) // Vertex Normal
				{
					inStrStream >> normals[normals_counter].x >> normals[normals_counter].y >> normals[normals_counter].z;

					normals_counter++;
				}
				else if ( prefix == "f" ) // Face
				{
					uint32 counter = 0u;

				// Disable notification about possible buffer overflow.

					#pragma warning( push ) // C6836
					#pragma warning( disable : 6386)

					while ( inStrStream >> temp_index )
					{
					// Push indices into correct vectore:

						if ( counter == 0u )
						{
							indices_position[indices_position_counter] = temp_index;

							indices_position_counter++;
						}
						else if ( counter == 1u )
						{
							indices_texCoord[indices_texCoord_counter] = temp_index;

							indices_texCoord_counter++;
						}
						else if ( counter == 2u )
						{
							indices_normal[indices_normal_counter] = temp_index;

							indices_normal_counter++;
						}

					// Handle characters:

						if ( inStrStream.peek() == '/' )
						{
							counter++;

							inStrStream.ignore( 1, '/' );
						}
						else if (inStrStream.peek() == ' ' )
						{
							counter++;

							inStrStream.ignore( 1, ' ' );
						}

					// Reset counter:

						if ( counter > 2u )
						{
							counter = 0u;
						}
					}

					#pragma warning( pop ) // C6386
				}

				#pragma warning( pop ) // C6385
			}

		// Build final Vertex array:

			m_Vertices = new dx9::Vertex[indices_position_counter];

			m_VerticesAmount = indices_position_counter;

			m_Indices  = new uint32[indices_position_counter];

			m_IndicesAmount = indices_position_counter;

			for ( uint32 i = 0u; i < indices_position_counter; i++ )
			{
			// Position:

				m_Vertices[i].position.x = positions[indices_position[i] - 1u].x;
				m_Vertices[i].position.y = positions[indices_position[i] - 1u].y;
				m_Vertices[i].position.z = positions[indices_position[i] - 1u].z;

			// Texture coordinates:

				m_Vertices[i].textureCoord.x = texCoords[indices_texCoord[i] - 1u].u;
				m_Vertices[i].textureCoord.y = texCoords[indices_texCoord[i] - 1u].v;

			// Normals:

				m_Vertices[i].normal.x = normals[indices_normal[i] - 1u].x;
				m_Vertices[i].normal.y = normals[indices_normal[i] - 1u].y;
				m_Vertices[i].normal.z = normals[indices_normal[i] - 1u].z;

			// Indices:

				m_Indices[i] = indices_position[i];
			}
		}
		else
		{
			return false;
		}

	// Delete all temporary data:

		delete[] positions;
		delete[] texCoords;
		delete[] normals;

		delete[] indices_position;
		delete[] indices_texCoord;
		delete[] indices_normal;

		return true;
	}

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

		std::vector<dx9::Vertex> vertices;

	// Strings for file parsing:

		std::stringstream strStream;

		std::string line;
		std::string prefix;

		D3DXVECTOR3 temp_vec3;
		D3DXVECTOR2 temp_vec2;
		uint32 temp_uint32 = 0u;

		std::ifstream inFile;

		// TEST
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

			// DEBUG:

				NumVertexPos       = vertex_positions.size();
				NumVertexTexCoords = vertex_texCoords.size();
				NumVertexNormals   = vertex_normals.size();
			}

		// Build final Vertex vector:

			vertices.resize( vertex_position_indices.size(), dx9::Vertex() );

			for ( size_t i = 0u; i < vertices.size(); i++ )
			{
				vertices[i].position     = vertex_positions[vertex_position_indices[i] - 1u];
				vertices[i].textureCoord = vertex_texCoords[vertex_texCoord_indices[i] - 1u];
				vertices[i].normal       = vertex_normals[vertex_normal_indices[i] - 1u];
			}
		}
		else
		{
			return false;
		}

		return true;
	}


// Private Functions:

	void OBJLoader::ClearBuffers()
	{
	// Vertices:

		if ( m_Vertices )
		{
			delete[] m_Vertices;

			m_Vertices = nullptr;
		}

		if ( m_VerticesAmount != 0u )
		{
			m_VerticesAmount = 0u;
		}

	// Indices:

		if ( m_Indices )
		{
			delete[] m_Indices;

			m_Indices = nullptr;
		}

		if ( m_Indices != 0u )
		{
			m_Indices = 0u;
		}
	}

}