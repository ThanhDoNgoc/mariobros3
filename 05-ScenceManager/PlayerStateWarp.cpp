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
	if (isDown)
		__Mario->vy += MARIO_WARP_SPEED * __Mario->dt;
	else
		__Mario->vy -= MARIO_WARP_SPEED * __Mario->dt;
	if (abs(__Mario->y - this->distance) > __Mario->height)
	{
		__Mario->isWarping = false;
		__Mario->SetPosition(this->toX, this->toY);
		__Mario->SetState(new PlayerStateIdle());
		__Mario->collision = Collision2D::Full;
	}
}

void PlayerStateWarp::SetAnimation()
{
	__Mario->ani = MARIO_ANI_WARP;
}

void PlayerStateWarp::OnKeyDown(int KeyCode)
{
}
