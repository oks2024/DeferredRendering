#pragma once

#include "stdafx.h"
#include "DeferredRenderer.h"
#include "Engine.h"
#include "QuadRenderer.h"
#include "InputManager.h"


DeferredRenderer::DeferredRenderer(void)
{
	HRESULT hr = S_OK;


	UINT width = Engine::Instance()->GetWidth();
	UINT height = Engine::Instance()->GetHeight();

	// Albedo.

	// Create the albedo texture.
	D3D11_TEXTURE2D_DESC descAlbedoTexture;
	ZeroMemory(&descAlbedoTexture, sizeof(descAlbedoTexture));
	descAlbedoTexture.Width = width;
	descAlbedoTexture.Height = height;
	descAlbedoTexture.MipLevels = 1;
	descAlbedoTexture.ArraySize = 1;
	descAlbedoTexture.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descAlbedoTexture.SampleDesc.Count = 1;
	descAlbedoTexture.SampleDesc.Quality = 0;
	descAlbedoTexture.Usage = D3D11_USAGE_DEFAULT;
	descAlbedoTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descAlbedoTexture.CPUAccessFlags = 0;
	descAlbedoTexture.MiscFlags = 0;

	hr = Engine::Instance()->GetDevice()->CreateTexture2D(&descAlbedoTexture, NULL, &m_pAlbedoTexture);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating albedo texture.", L"Error", MB_OK);


	// Create the albedo render target.
	D3D11_RENDER_TARGET_VIEW_DESC albedoRTVDesc;
	ZeroMemory(&albedoRTVDesc, sizeof(albedoRTVDesc));
	albedoRTVDesc.Format = descAlbedoTexture.Format;
	albedoRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	albedoRTVDesc.Texture2D.MipSlice = 0;

	hr = Engine::Instance()->GetDevice()->CreateRenderTargetView(m_pAlbedoTexture, &albedoRTVDesc, &m_pAlbedoRenderTargetView);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating albedo RT.", L"Error", MB_OK);


	// Create the albedo shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC albedoSRVDesc;
	albedoSRVDesc.Format = descAlbedoTexture.Format;
	albedoSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	albedoSRVDesc.Texture2D.MostDetailedMip = 0;
	albedoSRVDesc.Texture2D.MipLevels = 1;

	hr = Engine::Instance()->GetDevice()->CreateShaderResourceView(m_pAlbedoTexture, &albedoSRVDesc, &m_pAlbedoShaderRV);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating albedo SRV.", L"Error", MB_OK);


	// Normal.

	// Create the normal texture.
	D3D11_TEXTURE2D_DESC descNormalTexture;
	ZeroMemory(&descNormalTexture, sizeof(descNormalTexture));
	descNormalTexture.Width = width;
	descNormalTexture.Height = height;
	descNormalTexture.MipLevels = 1;
	descNormalTexture.ArraySize = 1;
	descNormalTexture.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descNormalTexture.SampleDesc.Count = 1;
	descNormalTexture.SampleDesc.Quality = 0;
	descNormalTexture.Usage = D3D11_USAGE_DEFAULT;
	descNormalTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descNormalTexture.CPUAccessFlags = 0;
	descNormalTexture.MiscFlags = 0;

	hr = Engine::Instance()->GetDevice()->CreateTexture2D(&descNormalTexture, NULL, &m_pNormalTexture);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating normal texture.", L"Error", MB_OK);


	// Create the Normal render target.
	D3D11_RENDER_TARGET_VIEW_DESC normalRTVDesc;
	ZeroMemory(&normalRTVDesc, sizeof(normalRTVDesc));
	normalRTVDesc.Format = descNormalTexture.Format;
	normalRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	normalRTVDesc.Texture2D.MipSlice = 0;

	hr = Engine::Instance()->GetDevice()->CreateRenderTargetView(m_pNormalTexture, &normalRTVDesc, &m_pNormalRenderTargetView);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating normal RT.", L"Error", MB_OK);


	// Create the Normal shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC normalSRVDesc;
	normalSRVDesc.Format = descNormalTexture.Format;
	normalSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	normalSRVDesc.Texture2D.MostDetailedMip = 0;
	normalSRVDesc.Texture2D.MipLevels = 1;

	hr = Engine::Instance()->GetDevice()->CreateShaderResourceView(m_pNormalTexture, &normalSRVDesc, &m_pNormalShaderRV);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating normal SRV.", L"Error", MB_OK);


	// Depth.

	// Create the depth texture.
	D3D11_TEXTURE2D_DESC descDepthTexture;
	ZeroMemory(&descDepthTexture, sizeof(descDepthTexture));
	descDepthTexture.Width = width;
	descDepthTexture.Height = height;
	descDepthTexture.MipLevels = 1;
	descDepthTexture.ArraySize = 1;
	descDepthTexture.Format = DXGI_FORMAT_R32_FLOAT;
	descDepthTexture.SampleDesc.Count = 1;
	descDepthTexture.SampleDesc.Quality = 0;
	descDepthTexture.Usage = D3D11_USAGE_DEFAULT;
	descDepthTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descDepthTexture.CPUAccessFlags = 0;
	descDepthTexture.MiscFlags = 0;

	hr = Engine::Instance()->GetDevice()->CreateTexture2D(&descDepthTexture, NULL, &m_pDepthTexture);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating depth texture.", L"Error", MB_OK);


	// Create the depth render target.
	D3D11_RENDER_TARGET_VIEW_DESC depthRTVDesc;
	ZeroMemory(&depthRTVDesc, sizeof(depthRTVDesc));
	depthRTVDesc.Format = descDepthTexture.Format;
	depthRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	depthRTVDesc.Texture2D.MipSlice = 0;

	hr = Engine::Instance()->GetDevice()->CreateRenderTargetView(m_pDepthTexture, &depthRTVDesc, &m_pDepthRenderTargetView);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating depth RT.", L"Error", MB_OK);


	// Create the depth shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC depthSRVDesc;
	depthSRVDesc.Format = descDepthTexture.Format;
	depthSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	depthSRVDesc.Texture2D.MostDetailedMip = 0;
	depthSRVDesc.Texture2D.MipLevels = 1;

	hr = Engine::Instance()->GetDevice()->CreateShaderResourceView(m_pDepthTexture, &depthSRVDesc, &m_pDepthShaderRV);

	// Lightmap.

	// Create the light texture.
	D3D11_TEXTURE2D_DESC descLightTexture;
	ZeroMemory(&descLightTexture, sizeof(descLightTexture));
	descLightTexture.Width = width;
	descLightTexture.Height = height;
	descLightTexture.MipLevels = 1;
	descLightTexture.ArraySize = 1;
	descLightTexture.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descLightTexture.SampleDesc.Count = 1;
	descLightTexture.SampleDesc.Quality = 0;
	descLightTexture.Usage = D3D11_USAGE_DEFAULT;
	descLightTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descLightTexture.CPUAccessFlags = 0;
	descLightTexture.MiscFlags = 0;

	hr = Engine::Instance()->GetDevice()->CreateTexture2D(&descLightTexture, NULL, &m_pLightTexture);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating light texture.", L"Error", MB_OK);

	// Create the light render target.
	D3D11_RENDER_TARGET_VIEW_DESC lightRTVDesc;
	ZeroMemory(&lightRTVDesc, sizeof(lightRTVDesc));
	lightRTVDesc.Format = descLightTexture.Format;
	lightRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	lightRTVDesc.Texture2D.MipSlice = 0;

	hr = Engine::Instance()->GetDevice()->CreateRenderTargetView(m_pLightTexture, &lightRTVDesc, &m_pLightRenderTargetView);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating light RT.", L"Error", MB_OK);

	// Create the light shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC lightSRVDesc;
	lightSRVDesc.Format = descLightTexture.Format;
	lightSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	lightSRVDesc.Texture2D.MostDetailedMip = 0;
	lightSRVDesc.Texture2D.MipLevels = 1;

	hr = Engine::Instance()->GetDevice()->CreateShaderResourceView(m_pLightTexture, &lightSRVDesc, &m_pLightShaderRV);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating light SRV.", L"Error", MB_OK);

	// Final.

	// Create the final texture.
	D3D11_TEXTURE2D_DESC descFinalTexture;
	ZeroMemory(&descFinalTexture, sizeof(descFinalTexture));
	descFinalTexture.Width = width;
	descFinalTexture.Height = height;
	descFinalTexture.MipLevels = 1;
	descFinalTexture.ArraySize = 1;
	descFinalTexture.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descFinalTexture.SampleDesc.Count = 1;
	descFinalTexture.SampleDesc.Quality = 0;
	descFinalTexture.Usage = D3D11_USAGE_DEFAULT;
	descFinalTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descFinalTexture.CPUAccessFlags = 0;
	descFinalTexture.MiscFlags = 0;

	hr = Engine::Instance()->GetDevice()->CreateTexture2D(&descFinalTexture, NULL, &m_pFinalTexture);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating final texture.", L"Error", MB_OK);

	// Create the final render target.
	D3D11_RENDER_TARGET_VIEW_DESC finalRTVDesc;
	ZeroMemory(&finalRTVDesc, sizeof(finalRTVDesc));
	finalRTVDesc.Format = descFinalTexture.Format;
	finalRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	finalRTVDesc.Texture2D.MipSlice = 0;

	hr = Engine::Instance()->GetDevice()->CreateRenderTargetView(m_pFinalTexture, &finalRTVDesc, &m_pFinalRenderTargetView);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating final RT.", L"Error", MB_OK);

	// Create the final shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC finalSRVDesc;
	finalSRVDesc.Format = descFinalTexture.Format;
	finalSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	finalSRVDesc.Texture2D.MostDetailedMip = 0;
	finalSRVDesc.Texture2D.MipLevels = 1;

	hr = Engine::Instance()->GetDevice()->CreateShaderResourceView(m_pFinalTexture, &finalSRVDesc, &m_pFinalShaderRV);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating final SRV.", L"Error", MB_OK);


	
	m_pGBufferRenderer = new GBufferRenderer();
	m_pLightningRenderer = new LightningRenderer();
	m_pCombineFinalRenderer = new CombineFinalRenderer();
	// TESTS//////////////


	m_pDrawTexturePixelShader = Engine::Instance()->CreatePixelShader(L"DrawTexturePixelShader.hlsl", "main");

	m_pCamera = new Camera();
	m_pScene = new Scene();

	OutputDebugString(L"Deferred renderer initialized\n");
}

void DeferredRenderer::Update()
{
	InputManager::Instance()->Update();
	m_pCamera->Update();
}

void DeferredRenderer::Render()
{
	ID3D11ShaderResourceView* nosrvs[3] = {0, 0, 0};
	
	m_pGBufferRenderer->Render(m_pAlbedoRenderTargetView, m_pNormalRenderTargetView, m_pDepthRenderTargetView, m_pCamera, m_pScene);

	m_pLightningRenderer->Render(m_pLightRenderTargetView, m_pAlbedoShaderRV, m_pNormalShaderRV, m_pDepthShaderRV, m_pCamera);

	m_pCombineFinalRenderer->Render(m_pFinalRenderTargetView, m_pAlbedoShaderRV, m_pLightShaderRV);

	// Draw render targets.
	ID3D11RenderTargetView* backBufferRenderTarget = Engine::Instance()->GetBackBufferRenderTarget();
	Engine::Instance()->GetImmediateContext()->OMSetRenderTargets(1, &backBufferRenderTarget, 0);
	float ClearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	Engine::Instance()->GetImmediateContext()->ClearRenderTargetView(backBufferRenderTarget, ClearColor);

	QuadRenderer::Instance()->PSSetSampler(0, 1, Engine::Instance()->GetSamplerLinear());
	QuadRenderer::Instance()->PSSetShaderResource(0, m_pFinalShaderRV);
	QuadRenderer::Instance()->SetPixelShader(m_pDrawTexturePixelShader);
	QuadRenderer::Instance()->Render();
	
	// Unbind resources.
	Engine::Instance()->GetImmediateContext()->PSSetShaderResources(0, 3, nosrvs);

	Engine::Instance()->Present();
}


DeferredRenderer::~DeferredRenderer(void)
{
	delete m_pGBufferRenderer;

	delete m_pCamera;
	delete m_pScene;

	// Albedo
	if ( m_pAlbedoRenderTargetView)
		m_pAlbedoRenderTargetView->Release();

	if ( m_pAlbedoShaderRV)
		m_pAlbedoShaderRV->Release();

	if ( m_pAlbedoTexture)
		m_pAlbedoTexture->Release();

	// Normal
	if ( m_pNormalRenderTargetView)
		m_pNormalRenderTargetView->Release();

	if ( m_pNormalShaderRV)
		m_pNormalShaderRV->Release();

	if ( m_pNormalTexture)
		m_pNormalTexture->Release();

	// Depth
	if ( m_pDepthRenderTargetView)
		m_pDepthRenderTargetView->Release();

	if ( m_pDepthShaderRV)
		m_pDepthShaderRV->Release();

	if ( m_pDepthTexture)
		m_pDepthTexture->Release();
}
