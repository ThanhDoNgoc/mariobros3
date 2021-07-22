#include "PlayerStateJump.h"
#include "Mario.h"

#include "PlayerStateFall.h"
#include "PlayerStateFly.h"
#include "PlayerStateAttack.h"

PlayerStateJump::PlayerStateJump()
{
	DebugOut(L"[INFO] Jump \n");
	__Mario->vy = -MARIO_JUMP_SPEED;
	__Mario->isOnGround = false;
	StartJumpHigh();
	__Mario->state = MARIO_STATE_JUMP;

	if (__Mario->isDebuff == true)
	{
		if (__Mario->jumpCount < 2)
		{
			__Mario->jumpCount += 1;
		}
		else
		{
			__Mario->jumpCount = 0;
			__Mario->removePoop_start = GetTickCount();
		}
	}
	else __Mario->jumpCount = 0;
}

void PlayerStateJump::Update()
{

	if (KeyHanler::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		__Mario->direction.x = 1.0f;
		if (!__Mario->isMaxCharge)
			__Mario->vx = MARIO_MAX_WALKING_SPEED * __Mario->direction.x;
		else 
			__Mario->vx = MARIO_MAX_RUNNING_SPEED * __Mario->direction.x;
	}
	else if (KeyHanler::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		__Mario->direction.x = -1.0f;
		if (!__Mario->isMaxCharge)
			__Mario->vx = MARIO_MAX_WALKING_SPEED * __Mario->direction.x;
		else
			__Mario->vx = MARIO_MAX_RUNNING_SPEED * __Mario->direction.x;
	}

	if (!KeyHanler::GetInstance()->IsKeyDown(DIK_S) || GetTickCount() - jumpTimeStart > MARIO_JUMP_TIME || __Mario->isDebuff == true)
		isJumping = false;


	if (isJumping)
	{
		__Mario->vy = -MARIO_JUMP_SPEED;
		//DebugOut(L" velocity Y: %f \n ", __Mario->vy);
	}

	if (__Mario->isOnGround == true)
		__Mario->SetState(new PlayerStateIdle());

	if (__Mario->vy > 0)
		__Mario->SetState(new PlayerStateFall());
}

void PlayerStateJump::SetAnimation()
{
	if (!__Mario->isMaxCharge)
		__Mario->ani = MARIO_ANI_JUMP;
	else
		__Mario->ani = MARIO_ANI_JUMP_MAX;
}

void PlayerStateJump::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		if (__Mario->level == MARIO_LEVEL_RACCOON && __Mario->isMaxCharge)
		{
			__Mario->SetState(new PlayerStateFly());
		}
		break;
	case DIK_A:
		if (__Mario->level > MARIO_LEVEL_BIG)
			__Mario->SetState(new PlayerStateAttack());
		break;
	}
}
