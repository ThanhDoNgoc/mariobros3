#include "Camera.h"

#include "Game.h"
#include "GameObject.h"
#include "Mario.h"

Camera::Camera()
{

	this->isFollow = false;
	this->isStatic = true;

	this->CamWidth = CAMERA_WIDTH;
	this->CamHeight = CAMERA_HEIGHT;

	this->CamPosX = 0;
	this->CamPosY = 0;
	this->limidRight = 0;
	this->limitLeft = 0;
	this->limitTop = 0;
	this->limitBottom = 0;

	this->target = 0;
}

void Camera::SetCamPos(int CamPosX, int CamPosY)
{
	this->CamPosX = (float)CamPosX;
	this->CamPosY = (float)CamPosY;
}

void Camera::SetCamSize(float CamWidth, float CamHeight)
{
	this->CamWidth = CamWidth;
	this->CamHeight = CamHeight;
}

void Camera::SetCamTarget(CGameObject* target)
{
	this->target = target;
	this->isFollow = true;
}

int Camera::GetCamPosX()
{
	return (int)CamPosX;
}

int Camera::GetCamPosY()
{
	return (int)CamPosY;
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
	__Mario->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= CamWidth/2;
	cy -= CamHeight/2;

	if (isFollow)
	{
		//update cam pos -> player (1:1)
		CamPosX = (float)cx;
		CamPosY = (float)cy;
		/*if (__Mario->state == MARIO_STATE_FLY || __Mario->state == MARIO_STATE_SLOW_FALL)
		{
			if (__Mario->y < this->CamPosY - CamHeight/2)
				CamPosY = cy;
		}
		else this->CamPosY = this->limitBottom - this->CamHeight;;*/
	}
	if (!isFollow && !isStatic)
	{
		CamPosX += CAMERA_SPEED ;
		CamPosY = cy;
	}
	if (this->CamPosX < this->limitLeft)
		this->CamPosX = this->limitLeft;

	if (this->CamPosX + this->CamWidth > this->limidRight)
		this->CamPosX = this->limidRight - this->CamWidth;

	if (this->CamPosY < this->limitTop)
		this->CamPosY = this->limitTop;

	if (this->CamPosY + this->CamHeight > this->limitBottom)
		this->CamPosY = this->limitBottom - this->CamHeight;

	if (__Mario->x < this->CamPosX)
		__Mario->x = this->CamPosX;
	if (!__Mario->isEndScene)
	{
		if (__Mario->x > this->CamPosX + CAMERA_WIDTH - MARIO_BIG_BBOX_WIDTH)
			__Mario->x = this->CamPosX + CAMERA_WIDTH - MARIO_BIG_BBOX_WIDTH;
	}
		 
}
