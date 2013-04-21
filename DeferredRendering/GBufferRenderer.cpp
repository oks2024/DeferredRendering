#pragma once

#include "stdafx.h"
#include "GBufferRenderer.h"
#include "Engine.h"
#include "QuadRenderer.h"

#ifdef _DEBUG
#include "InputManager.h"
#endif

GBufferRenderer::GBufferRenderer(void)
{
	ID3DBlob* renderVSBlob = NULL;
	m_pRenderVertexLayout = NULL;

	m_pClearPixelShader = Engine::Instance()->CreatePixelShader(L"ClearPixelShader.hlsl", "main");
	m_pRenderGBufferVertexShader = Engine::Instance()->CreateVertexShader(L"RenderGBufferVertexShader.hlsl", "main", &renderVSBlob);
	m_pRenderGBufferPixelShader = Engine::Instance()->CreatePixelShader(L"RenderGBufferPixelShader.hlsl", "main");

	

	HRESULT hr;
	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(GBufferConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = Engine::Instance()->GetDevice()->CreateBuffer(&bd, NULL, &m_pConstantBuffer);
	if(FAILED(hr))
		MessageBox(NULL, L"The constant buffer cannot be created.", L"Error", MB_OK);


	// Define the quad input layout.
	D3D11_INPUT_ELEMENT_DESC modelLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//{"BINORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//{"TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT modelNumElements = ARRAYSIZE(modelLayout);

	// Create the quad input layout
	
	hr = Engine::Instance()->GetDevice()->CreateInputLayout(modelLayout,
		modelNumElements,
		renderVSBlob->GetBufferPointer(),
		renderVSBlob->GetBufferSize(),
		&m_pRenderVertexLayout);
	renderVSBlob->Release();

	if (FAILED(hr))
		MessageBox(NULL, L"The Quad input layout cannot be created.", L"Error", MB_OK);


}


GBufferRenderer::~GBufferRenderer(void)
{

}

void GBufferRenderer::Render(ID3D11RenderTargetView* ppAlbedo, 
							 ID3D11RenderTargetView* ppNormal, 
							 ID3D11RenderTargetView* ppDepth,
							 Camera* p_pCamera,
							 Scene* p_pScene)
{

#ifdef _DEBUG
	m_nbDrawCalls = 0;
#endif

	// Update our time
	static float t = 0.0f;

	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if(dwTimeCur == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;


	QuadRenderer *quadRenderer = QuadRenderer::Instance();
	Engine* engine = Engine::Instance();

	// Set render targets.
	ID3D11RenderTargetView* RTViews[3] = { ppAlbedo, ppNormal, ppDepth };
	engine->GetImmediateContext()->OMSetRenderTargets(3, RTViews, 0);

	// Clear render targets
	quadRenderer->SetPixelShader(m_pClearPixelShader);
	quadRenderer->Render();

	// Set render targets.
	engine->GetImmediateContext()->OMSetRenderTargets(3, RTViews, engine->GetDepthStencil());
	engine->ClearDepthStencilView();
	
	// Set primitive topology
	engine->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	engine->GetImmediateContext()->VSSetShader(m_pRenderGBufferVertexShader, NULL, 0);
	engine->GetImmediateContext()->PSSetShader(m_pRenderGBufferPixelShader, NULL, 0);
	engine->GetImmediateContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	engine->GetImmediateContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//Engine::Instance()->GetImmediateContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	
	// Set vertex buffer
	UINT quadStride = sizeof(VertexPositionNormalTexture);
	UINT quadOffset = 0;

	ID3D11Buffer* vertexBuffer = p_pScene->GetModels()[0]->GetVertexBuffer();
	ID3D11Buffer* indexBuffer = p_pScene->GetModels()[0]->GetIndexBuffer();


	engine->GetImmediateContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &quadStride, &quadOffset);
	engine->GetImmediateContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	
	engine->GetImmediateContext()->IASetInputLayout(m_pRenderVertexLayout);


	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 64; z++)
			{
				if ( p_pScene->voxels[x][y][z].State != Active)
				{

					#ifdef _DEBUG
						m_nbDrawCalls++;
					#endif
					GBufferConstantBuffer m_ConstantBufferStructure;
					m_ConstantBufferStructure.mWorld = XMMatrixTranspose(XMMatrixTranslation(32 - x * 2.0f, -y * 2.0f, 32 - z*2.0f));
					//m_ConstantBufferStructure.mView = XMMatrixTranspose(p_pCamera->GetViewMatrix());
					m_ConstantBufferStructure.mView = p_pCamera->GetViewMatrix();
					m_ConstantBufferStructure.mProjection = p_pCamera->GetProjectionMatrix();

					engine->GetImmediateContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantBufferStructure, 0, 0);

					engine->GetImmediateContext()->DrawIndexed(12 * 3, 0, 0);
				}
			}
		}
	}


	#ifdef _DEBUG
		if (InputManager::Instance()->IsKeyDown(DIK_Z))
		{
			char buf[2048];
			sprintf_s(buf,"Number of draw calls:  %i \n",m_nbDrawCalls);
			OutputDebugStringA(buf);
		}
	#endif

}
