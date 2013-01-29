#pragma once
#include "VertexStructures.h"
#include <DirectXMath.h>
#include <d3d11.h>



class Model
{
public:
	Model(void);
	~Model(void);

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

private:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
};

