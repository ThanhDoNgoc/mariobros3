#include "Camera.h"

#include "Game.h"
#include "GameObject.h"

Camera::Camera()
{
	this->scrollX = true;
	this->scrollY = false;

	this->isFollow = false;
	this->isStatic = true;

	this->CamWidth = CAMERA_WIDTH;
	this->CamHeight = CAMERA_HEIGHT;
}

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

void Camera::SetCamLimit(float left, float top, float right, float bottom)
{
	this->limitLeft = left;
	this->limidRight = right;
	this->limitTop = top;
	this->limitBottom = bottom;
}

void Camera::setIsFollow(bool camfollow)
{
	this->isFollow = camfollow;
}

bool Camera::IsFollow()
{
	return this->isFollow;
}

void Camera::setIsStatic(bool camstatic)
{
	this->isStatic = camstatic;
}

bool Camera::IsStatic()
{
	return this->isStatic;
}

void Camera::SetScollX(bool sX)
{
}

void Camera::SetScoolY(bool sY)
{
}

void Camera::Update()
{
	// Update camera to follow mario
	float cx, cy;
	target->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= CamWidth/2;
	cy -= CamHeight/2;

	//update cam pos -> player (1:1)
	CamPosX = cx;
	CamPosY = cy;

	if (this->CamPosX < this->limitLeft)
		this->CamPosX = this->limitLeft;

	if (this->CamPosX + this->CamWidth > this->limidRight)
		this->CamPosX = this->limidRight - this->CamWidth;

	if (this->CamPosY < this->limitTop)
		this->CamPosY = this->limitTop;

	if (this->CamPosY + this->CamHeight > this->limitBottom)
		this->CamPosY = this->limitBottom - this->CamHeight;
}
