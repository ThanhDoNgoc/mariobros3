#include "PlayerStateWarp.h"
#include "PlayerStateIdle.h"
#include "Mario.h"
PlayerStateWarp::PlayerStateWarp(bool down, float posX, float posY)
{
	this->isDown = down;
	DebugOut(L"[INFO] warp \n");
	__Mario->isWarping = true;
	__Mario->state = MARIO_STATE_WARP;
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
