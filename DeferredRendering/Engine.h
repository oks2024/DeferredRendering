#pragma once
#include "Engine.h"
#include "Camera.h"
#include "Scene.h"
#include <d3d11.h>

class Engine
{
private:
	Engine();
	~Engine();
	static Engine *m_Instance;

	// DirectX 11 datas.
	ID3D11Device*				g_pd3dDevice;
	ID3D11DeviceContext*		g_pImmediateContext;
	IDXGISwapChain*				g_pSwapChain;
	D3D_DRIVER_TYPE				g_driverType;
	D3D_FEATURE_LEVEL			g_featureLevel;
	ID3D11RenderTargetView*		g_pRenderTargetView;
	ID3D11Texture2D*			g_pDepthStencil;
	ID3D11DepthStencilView*		g_pDepthStencilView;
	ID3D11RasterizerState*		g_pRasterizerState;
	ID3D11SamplerState*			m_pSamplerLinear;
	ID3D11SamplerState*			m_pSamplerPoint;

	ID3D11BlendState*			m_pOpaqueBlendState;
	ID3D11BlendState*			m_pAlphaBlendState;

	int m_Width;
	int m_Height;



public:
	// Getters/Setters.
	static Engine *Instance();
	int GetWidth();
	int GetHeight();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetImmediateContext();
	ID3D11RenderTargetView* GetBackBufferRenderTarget();
	ID3D11DepthStencilView* GetDepthStencil();
	ID3D11SamplerState* GetSamplerLinear();
	ID3D11SamplerState* GetSamplerPoint();

	// Tools.
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	ID3D11PixelShader* CreatePixelShader(WCHAR* pFileName, LPCSTR pEntryPoint, ID3DBlob* p_pPSBlobOut);
	ID3D11PixelShader* CreatePixelShader(WCHAR* pFileName, LPCSTR pEntryPoint);
	ID3D11VertexShader* CreateVertexShader(WCHAR* pFileName, LPCSTR pEntryPoint, ID3DBlob** p_pVSBlobOut);
	void ClearDepthStencilView();
	void Present();
	void SetOpaque();


};

