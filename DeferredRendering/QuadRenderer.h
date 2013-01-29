#pragma once
#include <d3d11.h>
class QuadRenderer
{
public:
	static QuadRenderer* Instance();
	void Render();

	void PSSetSampler(UINT pStartSlot, UINT pNumSampler, ID3D11SamplerState* ppSamplerState);
	void PSSetShaderResource(UINT pStartSlot, ID3D11ShaderResourceView* ppSamplerState);

	void SetPixelShader(ID3D11PixelShader* ppPixelShader);

	void SetConstantBuffer(int p_Slot, ID3D11Buffer* p_pConstantBuffer);

	void UpdateSubresource(ID3D11Resource* p_pResource, const void* p_pSrcData );
private:
	QuadRenderer(void);
	~QuadRenderer(void);

	static QuadRenderer* m_pInstance;

	// Full screen quad data
	// General datas, common toall fullscreen quads.
	ID3D11InputLayout*			m_pQuadVertexLayout;
	ID3D11VertexShader*			m_pQuadVertexShader;
	ID3D11Buffer*				m_pQuadVertexBuffer;
	ID3D11Buffer*				m_pQuadIndexBuffer;

	ID3D11PixelShader*			m_pQuadPixelShader;
	
};

