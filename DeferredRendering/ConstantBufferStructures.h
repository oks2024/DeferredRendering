#pragma once
#include <DirectXMath.h>

struct GBufferConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4 mProjection;
};

__declspec(align(16))
struct LightningConstantBuffer
{
	DirectX::XMFLOAT4 mLightDirection;
	DirectX::XMFLOAT4 mColor;
	DirectX::XMFLOAT3 mCameraPosition;
	DirectX::XMFLOAT4X4 mInvertViewMatrix;
};