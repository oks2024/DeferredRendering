#include "stdafx.h"
#include "LightningRenderer.h"
#include "Engine.h"
#include "QuadRenderer.h"


LightningRenderer::LightningRenderer(void)
{
	HRESULT hr;
	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(LightningConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = Engine::Instance()->GetDevice()->CreateBuffer(&bd, NULL, &m_pConstantBuffer);
	if(FAILED(hr))
		MessageBox(NULL, L"The constant buffer cannot be created.", L"Error", MB_OK);

	m_pLightningPixelShader = Engine::Instance()->CreatePixelShader(L"DirectionalLightPixelShader.hlsl", "main");
	OutputDebugString(L"Lightning renderer initialized\n");
}


LightningRenderer::~LightningRenderer(void)
{
}

void LightningRenderer::Render(ID3D11RenderTargetView* p_pLightMap, 
							   ID3D11ShaderResourceView* p_pAlbedo, 
							   ID3D11ShaderResourceView* p_pNormal, 
							   ID3D11ShaderResourceView* p_pDepth,
							   Camera* p_pCamera)
{
	QuadRenderer *quadRenderer = QuadRenderer::Instance();
	Engine* engine = Engine::Instance();


	engine->GetImmediateContext()->OMSetRenderTargets(1, &p_pLightMap, 0);
	float ClearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	engine->GetImmediateContext()->ClearRenderTargetView(p_pLightMap, ClearColor);

	quadRenderer->SetPixelShader(m_pLightningPixelShader);
	quadRenderer->PSSetShaderResource(0, p_pAlbedo);
	quadRenderer->PSSetShaderResource(1, p_pNormal);
	quadRenderer->PSSetShaderResource(2, p_pDepth);

	// Set renderstates.
	quadRenderer->PSSetSampler(0, 1, engine->GetSamplerLinear());
	quadRenderer->PSSetSampler(1, 1, engine->GetSamplerPoint());

	// Set constant buffer.
	LightningConstantBuffer lightningConstantBuffer;
	lightningConstantBuffer.mLightDirection = XMFLOAT4(0.5f, -0.3f, 0.0f, 1.0f);
	lightningConstantBuffer.mColor = XMFLOAT4(0.99f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4 position;
	XMStoreFloat4(&position, p_pCamera->GetPosition());
	lightningConstantBuffer.mCameraPosition = position;

	lightningConstantBuffer.mInvertViewMatrix = XMMatrixTranspose(XMMatrixInverse(nullptr, XMMatrixMultiply(p_pCamera->GetViewMatrix(), p_pCamera->GetProjectionMatrix())));
	quadRenderer->SetConstantBuffer(0, m_pConstantBuffer);
	quadRenderer->UpdateSubresource(m_pConstantBuffer, &lightningConstantBuffer);

	quadRenderer->Render();
}
