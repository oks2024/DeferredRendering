#pragma once

#include "stdafx.h"
#include "Model.h"
#include "Engine.h"

using namespace DirectX;
Model::Model()
{
	
	//// Create vertex buffer
	//VertexPositionNormalTextureBinormalTangent tempVertices[] = 
	//{
	//	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f ) },
	//	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f ) },
	//	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f) },
	//	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

	//	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f)  },
	//	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

	//	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
	//	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
	//	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f)  },
	//	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

	//	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f)  },
	//	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

	//	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(0.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(1.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(1.0f, 1.0f)  },
	//	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(0.0f, 1.0f) },

	//	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(0.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(1.0f, 0.0f) },
	//	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(1.0f, 1.0f)  },
	//	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(0.0f, 1.0f) },
	//};

	//	// Create vertex buffer
	//VertexPositionNormalTextureBinormalTangent tempVertices[] = 
	//{
	//	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -0.9999999f )},
	//	
	//	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//	
	//	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT3( 0.0f, -0.9999999f, 0.0f )},
	//};
	
	// Create vertex buffer
	VertexPositionNormalTexture tempVertices[] = 
	{
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f)  },
		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f)  },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(1.0f, 1.0f)  },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(1.0f, 1.0f)  },
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(1.0f, 1.0f)  },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT2(0.0f, 1.0f) },
	};
	
	

	//m_Vertices = new VertexPositionNormalTexture[24];
	//// Ugly copy
	//for (int i = 0; i < 24; i++)
	//{
	//	m_Vertices[i] = tempVertices[i];
	//}

	// Create Index Buffer
		// Create index buffer
	WORD indicesTemp[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	//m_Indices = new WORD[12 * 3];
	//// Ugly copy
	//for (int i = 0; i < 12 * 3; i++)
	//{
	//	m_Indices[i] = indicesTemp[i];
	//}

	HRESULT hr;

	// Create vertex buffer.
	D3D11_BUFFER_DESC bdModel;
	ZeroMemory(&bdModel, sizeof(bdModel));
	bdModel.Usage = D3D11_USAGE_DEFAULT;
	bdModel.ByteWidth = sizeof(VertexPositionNormalTexture) * 24;
	bdModel.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bdModel.CPUAccessFlags = 0;
	bdModel.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA InitQuadData;
	ZeroMemory(&InitQuadData, sizeof(InitQuadData));
	InitQuadData.pSysMem = tempVertices;
	InitQuadData.SysMemPitch = 0;
	InitQuadData.SysMemSlicePitch = 0;
	hr = Engine::Instance()->GetDevice()->CreateBuffer(&bdModel, &InitQuadData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error creating vertex buffer.", L"Error", MB_OK);
	}

	// Create index buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 12 * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indicesTemp;
	hr = Engine::Instance()->GetDevice()->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Error creating index buffer.", L"Error", MB_OK);
	}

}


Model::~Model(void)
{

}

ID3D11Buffer* Model::GetVertexBuffer()
{
	return m_pVertexBuffer;
}

ID3D11Buffer* Model::GetIndexBuffer()
{
	return m_pIndexBuffer;
}