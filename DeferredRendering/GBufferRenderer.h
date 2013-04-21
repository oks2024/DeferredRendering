#pragma once
#include <d3d11.h>
#include "ConstantBufferStructures.h"
#include "Camera.h"
#include "Scene.h"

class GBufferRenderer
{
public:
	GBufferRenderer(void);
	~GBufferRenderer(void);
	void Render(ID3D11RenderTargetView* ppAlbedo, ID3D11RenderTargetView* ppNormal, ID3D11RenderTargetView* ppDepth, Camera* p_pCamera, Scene* p_pScene);

private:
	ID3D11PixelShader* m_pClearPixelShader;

	ID3D11VertexShader* m_pRenderGBufferVertexShader;
	ID3D11PixelShader* m_pRenderGBufferPixelShader;

	//GBufferConstantBuffer m_ConstantBufferStructure;
	ID3D11Buffer* m_pConstantBuffer;

	ID3D11InputLayout* m_pRenderVertexLayout;

#ifdef _DEBUG
	// Statistics.
	int m_nbDrawCalls;
#endif


};

