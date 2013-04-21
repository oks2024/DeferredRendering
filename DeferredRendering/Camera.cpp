#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "Engine.h"
#include "InputManager.h"


Camera::Camera(void):m_Position(0.0f, 0.0f, -20.0f),
					 m_CameraReference(0.0f, 0.0f, 10.0f),
					 m_Offset(0.0f, 10.0f, 0.0f)
{
	m_Yaw = 0;
	m_Pitch = 0;
	m_RotationSpeed = 1.0f;
	m_MovementSpeed = 1.0f;
}


Camera::~Camera(void)
{
}

void Camera::Update()
{


	int dMouseX = 0;
	int dMouseY = 0;

	if( InputManager::Instance()->IsMouseButtonDown(0))
	{
		InputManager::Instance()->GetMouseMove(dMouseX, dMouseY);
		m_Yaw += dMouseX * m_RotationSpeed * XM_PI/180;
		m_Pitch += dMouseY * m_RotationSpeed * XM_PI/180;
	}

	CXMVECTOR Forward = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	CXMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	CXMVECTOR Right = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);

	//XMMATRIX rotation = XMMatrixRotationAxis(Up, m_Yaw);

	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(m_Pitch, m_Yaw, 0.0f);
	XMVECTOR position = XMLoadFloat3(&m_Position);
	
	//XMVECTOR quaternion = XMVectorSet(0.0f, m_Yaw, 0.0f, 1.0f);

	
	XMVECTOR transformedForward = XMVector3Transform(Forward, rotation);
	XMVector3Normalize(transformedForward);

	XMVECTOR transformedRight = XMVector3Transform(Right, rotation);
	XMVector3Normalize(transformedRight);

	// Compute view matrix.
	
	//XMFLOAT3 lookAt(m_Position);
	//lookAt.z+=1.0f;
	//XMVECTOR At = XMLoadFloat3(&lookAt);
	//XMVectorSet(0.0f, -1.0f, 0.0f, 1.0f);
	/*XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);*/



	if ( InputManager::Instance()->IsKeyDown(DIK_W))
	{
		//m_Position.z += 1.0f;
		position += transformedForward * m_MovementSpeed;
	}

	if ( InputManager::Instance()->IsKeyDown(DIK_S))
	{
		position -= transformedForward * m_MovementSpeed;
	}

	if ( InputManager::Instance()->IsKeyDown(DIK_A))
	{
		position -= transformedRight * m_MovementSpeed;
	}

	if ( InputManager::Instance()->IsKeyDown(DIK_D))
	{
		position += transformedRight * m_MovementSpeed;
	}

	if ( InputManager::Instance()->IsKeyDown(DIK_Q))
	{
		position += Up * m_MovementSpeed;
	}

	if ( InputManager::Instance()->IsKeyDown(DIK_E))
	{
		position -= Up * m_MovementSpeed;
	}

	
	CXMMATRIX view = XMMatrixTranspose(XMMatrixLookAtLH(position, transformedForward + position, Up));

	XMStoreFloat4x4(&m_ViewMatrix, view);

	// Compute projection matrix.
	CXMMATRIX proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, Engine::Instance()->GetWidth()/(FLOAT)Engine::Instance()->GetHeight(), 0.01f, 10000.0f));
	XMStoreFloat4x4(&m_ProjectionMatrix, proj);

	// Compute invert view projection matrix.

	CXMMATRIX invertViewProj = XMMatrixInverse(nullptr, XMMatrixMultiply(view, proj));
	XMStoreFloat4x4(&m_InvertViewProjectionMatrix, invertViewProj);

	XMStoreFloat3(&m_Position, position);
}

// Getters and Setters
XMFLOAT4X4 Camera::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

XMFLOAT4X4 Camera::GetInvertViewProjection()
{
	return m_InvertViewProjectionMatrix;
}

XMFLOAT4X4 Camera::GetViewMatrix()
{

	return m_ViewMatrix;
}

XMFLOAT3 Camera::GetPosition()
{
	//return XMVectorSet(-15.0f, 7.0f, 1.0f, 1.0f);
	return m_Position;
}
