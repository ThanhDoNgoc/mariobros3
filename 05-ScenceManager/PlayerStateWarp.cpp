#include "PlayerStateWarp.h"
#include "PlayerStateIdle.h"
#include "Mario.h"
PlayerStateWarp::PlayerStateWarp(bool down, float posX, float posY)
{
	this->toX = posX;
	this->toY = posY;
	this->isDown = down;
	DebugOut(L"[INFO] warp \n");
	this->distance = __Mario->y;
	__Mario->isWarping = true;
	__Mario->collision = Collision2D::None;
}

void PlayerStateWarp::Update()
{
	DebugOut(L"[INFO] warpspeed %f \n", __Mario->vy);
	if (isDown)
		__Mario->vy = +MARIO_WARP_SPEED;
	else
		__Mario->vy = -MARIO_WARP_SPEED;
}

void PlayerStateWarp::SetAnimation()
{
	__Mario->ani = MARIO_ANI_WARP;
}

void PlayerStateWarp::OnKeyDown(int KeyCode)
{
}
