#include "Camera.h"

#include "Game.h"
#include "GameObject.h"

void Camera::SetCamPos(int CamPosX, int CamPosY)
{
	this->CamPosX = CamPosX;
	this->CamPosY = CamPosY;
}

void Camera::SetCamSize(float CamWidth, float CamHeight)
{
	this->CamWidth = CamWidth;
	this->CamHeight = CamHeight;
}

void Camera::SetCamTarget(CGameObject* target)
{
	this->target = target;
}

int Camera::GetCamPosX()
{
	return CamPosX;
}

int Camera::GetCamPosY()
{
	return CamPosY;
}

float Camera::GetCamWidth()
{
	return CamWidth;
}

float Camera::GetCamHeight()
{
	return CamHeight;
}

void Camera::Update()
{
	// Update camera to follow mario
	float cx, cy;
	target->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= CamWidth / 2;
	cy -= CamHeight / 2;

	CamPosX = cx;
	CamPosY = cy;

}
