#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "D3DUtility.h"

#include "Drawable.h"

namespace dx9
{
	class Mesh : public Drawable
	{
	public:

	// Constructors and Destructor:

		Mesh();

		~Mesh();

	// Functions:

		HRESULT CreateVertexBuffer( IDirect3DDevice9* pD3DDevice, const std::vector<Vertex>& iVertices, const uint32& facesAmount );

		void Draw() override;

	// Accessord:

		inline IDirect3DVertexBuffer9* GetVertexBuffer()      { return m_pVertexBuffer; }

		inline const DWORD&            GetFVF()               { return m_FVF; }

		inline IDirect3DTexture9*      GetTexture()           { return m_pTexture; }

		inline D3DMATERIAL9&           GetMaterial()          { return m_Material; }

		inline const uint32&           GetFacesAmount() const { return m_FacesAmount; }

	// Modifiers:

		void SetTexture( IDirect3DTexture9* pTexture );

		void SetMaterial( D3DMATERIAL9& material );

	private:

	// Components:

		IDirect3DDevice9*       m_pD3DDevice;

		std::vector<Vertex>     m_Vertices;

		uint32                  m_FacesAmount;

		IDirect3DTexture9*      m_pTexture;

		D3DMATERIAL9            m_Material;

		const DWORD&            m_FVF;

		IDirect3DVertexBuffer9* m_pVertexBuffer;
	};
}

#endif // MESH_H