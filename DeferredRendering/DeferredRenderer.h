#pragma once
#include "GBufferRenderer.h"
#include "LightningRenderer.h"
#include "CombineFinalRenderer.h"
#include "Camera.h"
#include "Scene.h"
#include <d3d11.h>

class DeferredRenderer
{
public:
	DeferredRenderer(void);
	~DeferredRenderer(void);

	void Update();
	void Render();


private:
	GBufferRenderer *m_pGBufferRenderer;
	LightningRenderer* m_pLightningRenderer;
	CombineFinalRenderer* m_pCombineFinalRenderer;
	

	// Albedo
	ID3D11Texture2D*			m_pAlbedoTexture;
	ID3D11RenderTargetView *	m_pAlbedoRenderTargetView;
	ID3D11ShaderResourceView*	m_pAlbedoShaderRV;
	
	// Normal
	ID3D11Texture2D*			m_pNormalTexture;
	ID3D11RenderTargetView *	m_pNormalRenderTargetView;
	ID3D11ShaderResourceView*	m_pNormalShaderRV;
	
	// Depth
	ID3D11Texture2D*			m_pDepthTexture;
	ID3D11RenderTargetView *	m_pDepthRenderTargetView;
	ID3D11ShaderResourceView*	m_pDepthShaderRV;

	// Lightmap
	ID3D11Texture2D*			m_pLightTexture;
	ID3D11RenderTargetView *	m_pLightRenderTargetView;
	ID3D11ShaderResourceView*	m_pLightShaderRV;

	// Final Render Target
	ID3D11Texture2D*			m_pFinalTexture;
	ID3D11RenderTargetView *	m_pFinalRenderTargetView;
	ID3D11ShaderResourceView*	m_pFinalShaderRV;


	// tests
	ID3D11PixelShader* m_pDrawTexturePixelShader;
//	ID3D11SamplerState* m_pLinearSampler;

	Camera* m_pCamera;
	Scene* m_pScene;


};

