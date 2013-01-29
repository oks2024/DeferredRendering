#include "stdafx.h"
#include "CombineFinalRenderer.h"
#include "Engine.h"
#include "QuadRenderer.h"


CombineFinalRenderer::CombineFinalRenderer(void)
{
	m_pCombinePixelShader = Engine::Instance()->CreatePixelShader(L"CombineFinalPixelShader.hlsl", "main");
}


CombineFinalRenderer::~CombineFinalRenderer(void)
{
	delete m_pCombinePixelShader;
}

void CombineFinalRenderer::Render(ID3D11RenderTargetView* p_pFinalRT,
								  ID3D11ShaderResourceView* p_pAlbedo,
								  ID3D11ShaderResourceView* p_pLight)
{
	QuadRenderer* quadRenderer = QuadRenderer::Instance();
	Engine* engine = Engine::Instance();


	engine->GetImmediateContext()->OMSetRenderTargets(1, &p_pFinalRT, 0);

	quadRenderer->SetPixelShader(m_pCombinePixelShader);
	quadRenderer->PSSetShaderResource(0, p_pAlbedo);
	quadRenderer->PSSetShaderResource(1, p_pLight);

	// Set renderstates.
	quadRenderer->PSSetSampler(0, 1, engine->GetSamplerLinear());

	quadRenderer->Render();
}
