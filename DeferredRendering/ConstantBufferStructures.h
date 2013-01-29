#pragma once
#include <DirectXMath.h>

struct GBufferConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};

struct LightningConstantBuffer
{
	DirectX::XMFLOAT4 mLightDirection;
	DirectX::XMFLOAT4 mColor;
	DirectX::XMFLOAT4 mCameraPosition;
	DirectX::XMMATRIX mInvertViewMatrix;
};