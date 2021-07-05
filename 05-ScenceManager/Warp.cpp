#include "Warp.h"
#include <dinput.h>
#include"Camera.h"

Warp::Warp()
{
	this->collision = Collision2D::None;
	this->ObjectGroup = Group::warp;
}

void Warp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->x;
	t = this->y;
	r = this->x + WARP_WIDTH;
	b = this->y + WARP_HEIGHT;
}

void Warp::OnOverLap(CGameObject* obj)
{
}

void Warp::setWarpDirection(WarpDirection dir)
{
	this->direc = dir;
}

WarpDirection Warp::getWarpDirection()
{
	return this->direc;
}

void Warp::Render()
{
	RenderBoundingBox();
}

int Warp::getKeyDirection()
{
	int warpKey;
	switch (this->getWarpDirection())
	{
	case WarpDirection::up: warpKey = DIK_UP; break;
	case WarpDirection::down: warpKey = DIK_DOWN; break;
	}
	return warpKey;
}

bool Warp::isDown()
{
	if (this->direc == WarpDirection::down)
		return true;

	return false;
}
