#include "PlayerStateWarpJump.h"
#include "Mario.h"
PlayerStateWarpJump::PlayerStateWarpJump()
{
	DebugOut(L"[INFO] warp \n");
	__Mario->isWarping = true;
	__Mario->state = MARIO_STATE_WARP;
	__Mario->direction.x = 1.0f;
}

void PlayerStateWarpJump::Update()
{
	DebugOut(L"[INFO] warpspeed %f \n", __Mario->vy);

	__Mario->vy = -MARIO_WARP_JUMP_SPEED;
}

void PlayerStateWarpJump::SetAnimation()
{
	__Mario->ani = MARIO_ANI_JUMP;
}

void PlayerStateWarpJump::OnKeyDown(int KeyCode)
{
}
