#pragma once
#include "DirectXMath.h"

struct VertexPositionTexture
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 TexCoord;
};

struct VertexPositionNormalTexture
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT2 Tex;
};

struct VertexPositionNormalTextureBinormalTangent
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT2 Tex;
	DirectX::XMFLOAT3 Binormal;
	DirectX::XMFLOAT3 Tangent;
};