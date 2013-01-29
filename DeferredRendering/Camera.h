#pragma once
#include "DirectXMath.h"

using namespace DirectX;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();
	XMVECTOR GetPosition();

private:
	////XMMATRIX m_View;
	//XMMATRIX m_Projection;
	//XMVECTOR m_Position;
};

