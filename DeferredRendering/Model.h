#pragma once
#include "VertexStructures.h"
#include <DirectXMath.h>
#include <d3d11.h>



class Model
{
public:
	Model(VertexPositionNormalTexture p_VertexBuffer[], int p_IndexBuffer[]);
	~Model(void);

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

private:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
};

