#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "Engine.h"


Camera::Camera(void)
{

}


Camera::~Camera(void)
{
}

// Getters and Setters
XMMATRIX Camera::GetProjectionMatrix()
{
	XMVECTOR m_Position = XMVectorSet(-15.0f, 7.0f, 1.0f, 1.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	return XMMatrixPerspectiveFovLH(XM_PIDIV2, Engine::Instance()->GetWidth()/(FLOAT)Engine::Instance()->GetHeight(), 0.01f, 10000.0f);;
}

XMMATRIX Camera::GetViewMatrix()
{
	XMVECTOR m_Position = XMVectorSet(-15.0f, 7.0f, 1.0f, 1.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	return XMMatrixLookAtLH(m_Position, At, Up);;
}

XMVECTOR Camera::GetPosition()
{
	return XMVectorSet(-15.0f, 7.0f, 1.0f, 1.0f);
	//return m_Position;
}
