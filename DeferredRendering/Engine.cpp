#pragma once
#include "stdafx.h"
#include "DeferredRendering.h"
#include "Engine.h"
#include <d3d11shader.h>
#include <d3dcompiler.h>



Engine::Engine()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(DeferredRendering::s_hWnd, &rc);
	m_Width = rc.right - rc.left;
	m_Height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_Width;
	sd.BufferDesc.Height = m_Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = DeferredRendering::s_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, 
			m_driverType, 
			NULL, 
			createDeviceFlags, 
			featureLevels, 
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&m_pd3dDevice,
			&m_featureLevel,
			&m_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if( FAILED(hr))
	{
		MessageBox(NULL, L"Error.", L"Error", MB_OK);
	}

	// Create the back buffer.
	// Create a render target view.
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error.", L"Error", MB_OK);
	}

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Error.", L"Error", MB_OK);
	}

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_Width;
	descDepth.Height = m_Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_pd3dDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Error.", L"Error", MB_OK);
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Error.", L"Error", MB_OK);
	}

	//g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

	// Create the linear sample state.
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = m_pd3dDevice->CreateSamplerState(&sampDesc, &m_pSamplerLinear);
	if(FAILED(hr))
		MessageBox(NULL, L"Error creating linear sampler.", L"Error", MB_OK);

		// Create the linear sample state.
	D3D11_SAMPLER_DESC sampPointDesc;
	ZeroMemory(&sampPointDesc, sizeof(sampPointDesc));
	sampPointDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampPointDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampPointDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampPointDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampPointDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampPointDesc.MinLOD = 0;
	sampPointDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = m_pd3dDevice->CreateSamplerState(&sampPointDesc, &m_pSamplerPoint);
	if(FAILED(hr))
		MessageBox(NULL, L"Error creating point sampler.", L"Error", MB_OK);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_Width;
	vp.Height = (FLOAT)m_Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &vp);

		// Setup the raster description which will determine how and what polygons will be drawn.
	D3D11_RASTERIZER_DESC rasterDesc;

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	hr = m_pd3dDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizerState);
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Error creating rasterizer state.", L"Error", MB_OK);
	}

	// Now set the rasterizer state.
	m_pImmediateContext->RSSetState(m_pRasterizerState);

	//D3D11_BLEND_DESC opaqueBlendDesc;
	//opaqueBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	//opaqueBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//opaqueBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//hr = g_pd3dDevice->CreateBlendState(&opaqueBlendDesc, &m_pOpaqueBlendState);

	//if(FAILED(hr))
	//{
	//	MessageBox(NULL, L"Error creating opaque blend state.", L"Error", MB_OK);
	//}

	//D3D11_BLEND_DESC alphaBlendBlendDesc;
	//alphaBlendBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	//alphaBlendBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//alphaBlendBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//hr = g_pd3dDevice->CreateBlendState(&alphaBlendBlendDesc, &m_pAlphaBlendState);

	//if(FAILED(hr))
	//{
	//	MessageBox(NULL, L"Error creating alpha blend state.", L"Error", MB_OK);
	//}

	OutputDebugString(L"Engine initialized\n");
}

Engine* Engine::Instance()
{
	if ( Engine::m_Instance == NULL)
	{
		Engine::m_Instance = new Engine();
	}
	return Engine::m_Instance;
}


Engine::~Engine()
{
	//if (g_pd3dDevice) g_pd3dDevice->Release();
	//g_pImmediateContext = NULL;
	//g_pSwapChain = NULL;
	//g_pRenderTargetView = NULL;
	//g_pDepthStencil = NULL;
	//g_pDepthStencilView = NULL;
	//g_pRasterizerState = NULL;
	//m_pSamplerLinear = NULL;
	//m_pSamplerPoint = NULL;
}

// Tools
//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT Engine::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG)|| defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improove the shader debugging experience, but still allows
	// ths shaders to be optimizes and to run exactly the way they will run in
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif


	ID3DBlob* pErrorBlob;

	const D3D_SHADER_MACRO defines[] = 
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	hr = D3DCompileFromFile( szFileName, 
		defines, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		szEntryPoint, 
		szShaderModel, 
		dwShaderFlags, 
		0, 
		ppBlobOut, 
		&pErrorBlob);

	if (FAILED(hr))
	{
		if(pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if ( pErrorBlob)
			pErrorBlob->Release();
		return hr;
	}

	if (pErrorBlob)
		pErrorBlob->Release();
	
	OutputDebugString(szFileName);
	OutputDebugString(L" Shader compiled.\n");

	return S_OK;
}

ID3D11PixelShader* Engine::CreatePixelShader(WCHAR* pFileName, LPCSTR pEntryPoint, ID3DBlob* p_pPSBlobOut)
{
	ID3D11PixelShader* pixelShader;
	// Compile the quad shader.
	//ID3DBlob* pPSBlob = NULL;
	p_pPSBlobOut = NULL;
	HRESULT hr = CompileShaderFromFile(pFileName, pEntryPoint, "ps_5_0", &p_pPSBlobOut);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"The pixel shader file cannot be compiled.", L"Error", MB_OK);
	}

	// Create the quad vertex shader
	hr = Engine::Instance()->GetDevice()->CreatePixelShader(p_pPSBlobOut->GetBufferPointer(),
		p_pPSBlobOut->GetBufferSize(),
		NULL,
		&pixelShader);

	if(FAILED(hr))
	{
		p_pPSBlobOut->Release();
		MessageBox(NULL, L"The pixel shader cannot be created.", L"Error", MB_OK);
		return NULL;
	}

	return pixelShader;
}

ID3D11PixelShader* Engine::CreatePixelShader(WCHAR* pFileName, LPCSTR pEntryPoint)
{
	ID3D11PixelShader* pixelShader;
	// Compile the quad shader.
	ID3DBlob* pPSBlob = NULL;

	HRESULT hr = CompileShaderFromFile(pFileName, pEntryPoint, "ps_5_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"The pixel shader file cannot be compiled.", L"Error", MB_OK);
	}

	// Create the quad vertex shader
	hr = Engine::Instance()->GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(),
		pPSBlob->GetBufferSize(),
		NULL,
		&pixelShader);

	if(FAILED(hr))
	{
		pPSBlob->Release();
		MessageBox(NULL, L"The pixel shader cannot be created.", L"Error", MB_OK);
		return NULL;
	}
	pPSBlob->Release();
	return pixelShader;
}


ID3D11VertexShader* Engine::CreateVertexShader(WCHAR* pFileName, LPCSTR pEntryPoint, ID3DBlob** p_pVSBlobOut)
{
	ID3D11VertexShader* vertexShader;
	// Compile the quad shader.
	//ID3DBlob* pVSBlob = NULL;
	(*p_pVSBlobOut) = NULL;
	HRESULT hr = CompileShaderFromFile(pFileName, pEntryPoint, "vs_5_0", p_pVSBlobOut);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"The vertex shader file cannot be compiled.", L"Error", MB_OK);
	}

	// Create the quad vertex shader
	hr = Engine::Instance()->GetDevice()->CreateVertexShader((*p_pVSBlobOut)->GetBufferPointer(),
		(*p_pVSBlobOut)->GetBufferSize(),
		NULL,
		&vertexShader);

	if(FAILED(hr))
	{
		(*p_pVSBlobOut)->Release();
		MessageBox(NULL, L"The vertex shader cannot be created.", L"Error", MB_OK);
		return NULL;
	}

	return vertexShader;
}

void Engine::SetOpaque()
{
	//g_pImmediateContext->OMSetBlendState(
}

void Engine::ClearDepthStencilView()
{
	// Clear the depth buffer to 1.0;
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Engine::Present()
{
	m_pSwapChain->Present(0, 0);
}

// Getters and Setters
int Engine::GetWidth()
{
	return m_Width;
}

int Engine::GetHeight()
{
	return m_Height;
}

ID3D11Device* Engine::GetDevice()
{
	return m_pd3dDevice;
}

ID3D11DeviceContext* Engine::GetImmediateContext()
{
	return m_pImmediateContext;
}

ID3D11RenderTargetView* Engine::GetBackBufferRenderTarget()
{
	return m_pRenderTargetView;
}

ID3D11DepthStencilView* Engine::GetDepthStencil()
{
	return m_pDepthStencilView;
}

ID3D11SamplerState* Engine::GetSamplerLinear()
{
	return m_pSamplerLinear;
}

ID3D11SamplerState* Engine::GetSamplerPoint()
{
	return m_pSamplerPoint;
}

// Initialization.
Engine *Engine::m_Instance = NULL;
