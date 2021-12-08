#include "../PrecompiledHeaders/stdafx.h"
#include "Mesh.h"

namespace dx9
{
// Constructors and Destructor:

	Mesh::Mesh()
		: m_pD3DDevice( nullptr ),
		  m_FacesAmount( 0u ),
		  m_pTexture( nullptr ),
		  m_Material( {} ),
		  m_FVF( Vertex::FVF ),
		  m_pVertexBuffer( nullptr )
	{
	}

	Mesh::~Mesh()
	{
		m_pD3DDevice = nullptr;

		m_pTexture   = nullptr;

		dx9::Release( m_pVertexBuffer );
	}


// Functions:

	HRESULT Mesh::CreateVertexBuffer(IDirect3DDevice9* pD3DDevice, const std::vector<Vertex>& iVertices, const uint32& facesAmount)
	{
		HRESULT result;

	// Initialize components:

		m_pD3DDevice = pD3DDevice;

		m_Vertices    = iVertices;

		m_FacesAmount = facesAmount;

	// Create and fill Vertex Buffer:

		result = m_pD3DDevice->CreateVertexBuffer( static_cast<UINT>( m_Vertices.size() * sizeof(Vertex) ), 0, Vertex::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, nullptr );

		void* pVertices = nullptr;

		m_pVertexBuffer->Lock( 0u, static_cast<UINT>( m_Vertices.size() * sizeof(Vertex) ), (void**)&pVertices, 0u );

		memcpy_s( pVertices, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), m_Vertices.size() * sizeof(Vertex) );

		m_pVertexBuffer->Unlock();

		return result;
	}


// Modifiers:

	void Mesh::SetTexture(IDirect3DTexture9* pTexture)
	{
		m_pTexture = pTexture;
	}

	void Mesh::SetMaterial(D3DMATERIAL9& material)
	{
		m_Material = material;
	}

}