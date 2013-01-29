#pragma once
#include <d3d11.h>
class CombineFinalRenderer
{
public:
	CombineFinalRenderer(void);
	~CombineFinalRenderer(void);

	void Render(ID3D11RenderTargetView* p_pFinalRT,
				ID3D11ShaderResourceView* p_pAlbedo,
				ID3D11ShaderResourceView* p_pLight);

private:
	ID3D11PixelShader* m_pCombinePixelShader;
	
};

