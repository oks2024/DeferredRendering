#pragma once
#include "DirectXMath.h"

using namespace DirectX;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void Update();

	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjectionMatrix();
	XMFLOAT3 GetPosition();
	XMFLOAT4X4 GetInvertViewProjection();

	

private:
	XMFLOAT3 m_Position;
	XMFLOAT4X4 m_ViewMatrix;
	XMFLOAT4X4 m_ProjectionMatrix;
	XMFLOAT4X4 m_InvertViewProjectionMatrix;

	XMFLOAT3 m_Offset;
	float m_Yaw;
	float m_Pitch;
	XMFLOAT3 m_CameraReference;
	float m_RotationSpeed;
	float m_MovementSpeed;
};

