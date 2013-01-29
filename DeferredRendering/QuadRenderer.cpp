#pragma once

#include "stdafx.h"
#include "QuadRenderer.h"
#include "Engine.h"
#include "VertexStructures.h"

using namespace DirectX;

QuadRenderer::QuadRenderer(void)
{

	// Compile the quad shader.
	ID3DBlob* pQuadVSBlob = NULL;
	HRESULT hr = Engine::Instance()->CompileShaderFromFile(L"QuadVertexShader.hlsl", "main", "vs_5_0", &pQuadVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"The Quad FX file cannot be compiled.", L"Error", MB_OK);
	}

	// Create the quad vertex shader
	hr = Engine::Instance()->GetDevice()->CreateVertexShader(pQuadVSBlob->GetBufferPointer(),
		pQuadVSBlob->GetBufferSize(),
		NULL,
		&m_pQuadVertexShader);

	if(FAILED(hr))
	{
		pQuadVSBlob->Release();
		MessageBox(NULL, L"The Quad shader cannot be created.", L"Error", MB_OK);
	}

	// Define the quad input layout.
	D3D11_INPUT_ELEMENT_DESC quadLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT quadNumElements = ARRAYSIZE(quadLayout);

	// Create the quad input layout

	hr = Engine::Instance()->GetDevice()->CreateInputLayout(quadLayout,
		quadNumElements,
		pQuadVSBlob->GetBufferPointer(),
		pQuadVSBlob->GetBufferSize(),
		&m_pQuadVertexLayout);
	pQuadVSBlob->Release();

	if (FAILED(hr))
		MessageBox(NULL, L"The Quad input layout cannot be created.", L"Error", MB_OK);
	
	// Create quad vertex buffer.
	VertexPositionTexture quadVertices[]=
	{
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT2(1.0f ,1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(0.0f ,1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f ,0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f ,0.0f) },
	};

	D3D11_BUFFER_DESC bdQuad;
	ZeroMemory(&bdQuad, sizeof(bdQuad));
	bdQuad.Usage = D3D11_USAGE_DEFAULT;
	bdQuad.ByteWidth = sizeof(VertexPositionTexture) * 4;
	bdQuad.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bdQuad.CPUAccessFlags = 0;
	bdQuad.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA InitQuadData;
	ZeroMemory(&InitQuadData, sizeof(InitQuadData));
	InitQuadData.pSysMem = quadVertices;
	InitQuadData.SysMemPitch = 0;
	InitQuadData.SysMemSlicePitch = 0;
	hr = Engine::Instance()->GetDevice()->CreateBuffer(&bdQuad, &InitQuadData, &m_pQuadVertexBuffer);
	if (FAILED(hr))
		MessageBox(NULL, L"The Quad buffer cannot be created.", L"Error", MB_OK);

	// Create quad index buffer.
	WORD quadIndices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	bdQuad.Usage = D3D11_USAGE_DEFAULT;
	bdQuad.ByteWidth = sizeof(WORD)*6;
	bdQuad.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bdQuad.CPUAccessFlags = 0;
	InitQuadData.pSysMem = quadIndices;
	hr = Engine::Instance()->GetDevice()->CreateBuffer(&bdQuad, &InitQuadData, &m_pQuadIndexBuffer);
	if(FAILED(hr))
		MessageBox(NULL, L"The Quad buffer cannot be created.", L"Error", MB_OK);

	OutputDebugString(L"QuadRenderer Initialized\n");
}


QuadRenderer::~QuadRenderer(void)
{
}

// Render a full screen quad. The pixel shader, ressources and buffers needs to be set.
void QuadRenderer::Render()
{
	Engine::Instance()->GetImmediateContext()->IASetInputLayout(m_pQuadVertexLayout);

	// Set primitive topology
	Engine::Instance()->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set vertex buffer
	UINT quadStride = sizeof(VertexPositionTexture);
	UINT quadOffset = 0;
	Engine::Instance()->GetImmediateContext()->IASetVertexBuffers(0, 1, &m_pQuadVertexBuffer, &quadStride, &quadOffset);
	Engine::Instance()->GetImmediateContext()->IASetIndexBuffer(m_pQuadIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	Engine::Instance()->GetImmediateContext()->VSSetShader(m_pQuadVertexShader, NULL, 0);
	Engine::Instance()->GetImmediateContext()->PSSetShader(m_pQuadPixelShader, NULL, 0);

	Engine::Instance()->GetImmediateContext()->DrawIndexed(6, 0, 0);
}

// Set rendering settings.
void QuadRenderer::PSSetSampler(UINT p_StartSlot, UINT p_NumSampler, ID3D11SamplerState* p_pSamplerState)
{
	Engine::Instance()->GetImmediateContext()->PSSetSamplers(p_StartSlot, p_NumSampler, &p_pSamplerState);
}

// Set constant buffer.
void QuadRenderer::SetConstantBuffer(int p_Slot, ID3D11Buffer* p_pConstantBuffer)
{
	Engine::Instance()->GetImmediateContext()->PSSetConstantBuffers(p_Slot, 1, &p_pConstantBuffer);
}

void QuadRenderer::UpdateSubresource(ID3D11Resource* p_pResource, const void* p_pSrcData )
{
	Engine::Instance()->GetImmediateContext()->UpdateSubresource(p_pResource, 0, NULL, p_pSrcData, 0, 0);
}

// Set rendering settings.
void QuadRenderer::PSSetShaderResource(UINT pStartSlot, ID3D11ShaderResourceView* ppSamplerState)
{
	Engine::Instance()->GetImmediateContext()->PSSetShaderResources(pStartSlot, 1, &ppSamplerState);
}

void QuadRenderer::SetPixelShader(ID3D11PixelShader* ppPixelShader)
{
	m_pQuadPixelShader = ppPixelShader;
}

QuadRenderer* QuadRenderer::Instance()
{
	if ( m_pInstance == NULL)
	{
		m_pInstance = new QuadRenderer();
	}
	return m_pInstance;
}

// Initialization.
QuadRenderer *QuadRenderer::m_pInstance = NULL;
