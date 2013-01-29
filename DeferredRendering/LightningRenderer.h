#pragma once
#include <d3d11.h>

#include "ConstantBufferStructures.h"
#include "Camera.h"

class LightningRenderer
{
public:
	LightningRenderer(void);
	~LightningRenderer(void);

	void Render(ID3D11RenderTargetView* p_pLightMap, 
				ID3D11ShaderResourceView* p_pAlbedo, 
				ID3D11ShaderResourceView* p_pNormal, 
				ID3D11ShaderResourceView* p_pDepth,
				Camera* p_pCamera);

private:
	ID3D11PixelShader* m_pLightningPixelShader;
	LightningConstantBuffer m_ConstantBufferStructure;
	ID3D11Buffer* m_pConstantBuffer;

};

