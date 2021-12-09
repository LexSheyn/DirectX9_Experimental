#include "../../PrecompiledHeaders/stdafx.h"
#include "OBJLoader.h"

namespace obj
{
// Constructors and Destructor:


	OBJLoader::OBJLoader()
	{
	}

	OBJLoader::~OBJLoader()
	{
		this->ClearGeometryBuffer();

		this->ClearMaterialsBuffer();
	}


// Functions:

	bool8 OBJLoader::LoadOBJ( const char* pathToOBJ, const bool findMaterials )
	{
	// Clear buffers first:

		this->ClearGeometryBuffer();

	// Vertex positions:

		std::vector<Position>     vertex_positions;
		std::vector<TextureCoord> vertex_texCoords;
		std::vector<Normal>       vertex_normals;

	// Face vectors:

		std::vector<uint32> vertex_position_indices;
		std::vector<uint32> vertex_texCoord_indices;
		std::vector<uint32> vertex_normal_indices;

	// Strings for file parsing:

		std::istringstream inStrStream;

		std::string line;
		std::string prefix;

		Position     temp_position;		
		TextureCoord temp_texCoord;
		Normal       temp_normal;;
		uint32       temp_index = 0u;

		std::ifstream inFile;

		inFile.open( pathToOBJ );

	// Parse OBJ file:

		if ( inFile.is_open() )
		{
		// Read one line at a time:

			while ( std::getline( inFile, line ) )
			{
			// Get prefix of the line:

				inStrStream.clear();

				inStrStream.str( line );

				inStrStream >> prefix;

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
					inStrStream >> temp_position.x >> temp_position.y >> temp_position.z;

					vertex_positions.push_back( temp_position );
				}
				else if ( prefix == "vt" ) // Texture Vertex
				{
					inStrStream >> temp_texCoord.u >> temp_texCoord.v;

					vertex_texCoords.push_back( temp_texCoord );
				}
				else if ( prefix == "vn" ) // Vertex Normal
				{
					inStrStream >> temp_normal.x >> temp_normal.y >> temp_normal.z;

					vertex_normals.push_back( temp_normal );
				}
				else if ( prefix == "f" ) // Face
				{
					uint32 counter = 0u;

					while ( inStrStream >> temp_index )
					{
					// Push indices into correct vectore:

						if ( counter == 0u )
						{
							vertex_position_indices.push_back( temp_index );
						}
						else if ( counter == 1u )
						{
							vertex_texCoord_indices.push_back( temp_index );
						}
						else if ( counter == 2u )
						{
							vertex_normal_indices.push_back( temp_index );
						}

					// Handle characters:

						if ( inStrStream.peek() == '/' )
						{
							counter++;

							inStrStream.ignore( 1, '/' );
						}
						else if ( inStrStream.peek() == ' ' )
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
				}
			}

		// Build final Vertex vector:

			m_Vertices.resize(vertex_position_indices.size(), dx9::Vertex() );

			for ( size_t i = 0u; i < m_Vertices.size(); i++ )
			{
				m_Vertices[i].position.x     = vertex_positions[vertex_position_indices[i] - 1u].x;
				m_Vertices[i].position.y     = vertex_positions[vertex_position_indices[i] - 1u].y;
				m_Vertices[i].position.z     = vertex_positions[vertex_position_indices[i] - 1u].z;

				m_Vertices[i].textureCoord.x = vertex_texCoords[vertex_texCoord_indices[i] - 1u].u;
				m_Vertices[i].textureCoord.y = vertex_texCoords[vertex_texCoord_indices[i] - 1u].v;

				m_Vertices[i].normal.x       = vertex_normals[vertex_normal_indices[i] - 1u].x;
				m_Vertices[i].normal.y       = vertex_normals[vertex_normal_indices[i] - 1u].y;
				m_Vertices[i].normal.z       = vertex_normals[vertex_normal_indices[i] - 1u].z;
			}

			m_VerticesAmount = static_cast<uint32>( m_Vertices.size() );

			m_FacesAmount = static_cast<uint32>( vertex_position_indices.size() ) / 3u;			
		}
		else
		{
			return false;
		}

	// TEST FOR 1 MATERIAL:

		if ( findMaterials )
		{
			this->ClearMaterialsBuffer();
			
			std::string pathToMTL = pathToOBJ;

			pathToMTL.resize( pathToMTL.size() - 3u );
			
			pathToMTL += "mtl";

			this->LoadMaterial( pathToMTL.c_str() );
		}

		inFile.close();

		return true;
	}

	bool8 OBJLoader::LoadMaterial(const char* pathToMTL)
	{
	// Temporary material:

		D3DMATERIAL9 material = {};

	// Strings for file parsing:

		std::istringstream inStrStream;

		std::string line;
		std::string prefix;

	// Parse MTL file:

		std::ifstream inFile;

		inFile.open( pathToMTL );

		if ( inFile.is_open() )
		{
		// Read one line at a time:

			while ( std::getline( inFile, line ) )
			{
			// Get prefix of the line:

				inStrStream.clear();

				inStrStream.str(line);

				inStrStream >> prefix;

				if ( prefix == "#" ) // Comment
				{

				}
				else if ( prefix == "Ns" ) // Specular Highlights
				{
				// Sharpness if specular highlight:

					inStrStream >> material.Power;
				}
				else if ( prefix == "Ka" ) // Ambient color
				{
				// Ambient color RGB:

					inStrStream >> material.Ambient.r;

					inStrStream >> material.Ambient.g;

					inStrStream >> material.Ambient.b;

					material.Ambient.a = 1.0f;
				}
				else if ( prefix == "Kd" ) // Diffuse color
				{
				// Diffuse color RGBA:

					inStrStream >> material.Diffuse.r;

					inStrStream >> material.Diffuse.g;

					inStrStream >> material.Diffuse.b;

					material.Diffuse.a = 1.0f;
				}
				else if ( prefix == "Ks" ) // Specular color
				{
				// Specular 'shininess':

					inStrStream >> material.Specular.r;

					inStrStream >> material.Specular.g;

					inStrStream >> material.Specular.b;

					material.Specular.a = 1.0f;
				}
				else if ( prefix == "Ke" ) // Emissive color
				{
				// Emissive color RGB:

					inStrStream >> material.Emissive.r;

					inStrStream >> material.Emissive.g;

					inStrStream >> material.Emissive.b;

					material.Emissive.a = 1.0f;
				}
			}

		// Add material to the buffer:

			m_Materials.push_back( material );

			m_MaterialsAmount = static_cast<uint32>( m_Materials.size() );
		}
		else
		{
			return false;
		}

		inFile.close();

		return true;
	}

	void OBJLoader::ClearGeometryBuffer()
	{
	// Vertices:

		if ( !m_Vertices.empty() )
		{
			m_Vertices.clear();

			m_VerticesAmount = static_cast<uint32>( m_Vertices.size() );
		}		

		if ( m_FacesAmount != 0u )
		{
			m_FacesAmount = 0u;
		}
	}

	void OBJLoader::ClearMaterialsBuffer()
	{
	// Materials:

		if ( !m_Materials.empty() )
		{
			m_Materials.clear();

			m_MaterialsAmount = static_cast<uint32>( m_Materials.size() );
		}
	}

}