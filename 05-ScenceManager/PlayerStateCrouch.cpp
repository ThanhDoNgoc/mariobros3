#include "PlayerStateCrouch.h"

#include "PlayerStateWalk.h"
#include "PlayerStateJump.h"
#include "PlayerStateFall.h"
#include "PlayerStateAttack.h"
#include "PlayerStateIdle.h"
#include "KeyHanler.h"
#include "Mario.h"

PlayerStateCrouch::PlayerStateCrouch()
{
	DebugOut(L"[INFO] CROUCH \n");
	if (__Mario->level != MARIO_LEVEL_SMALL)
	{
		__Mario->y += MARIO_BIG_BBOX_HEIGHT - MARIO_CROUCH_BBOX_HEIGHT;
		__Mario->height = MARIO_CROUCH_BBOX_HEIGHT;
	}
}

PlayerStateCrouch::~PlayerStateCrouch()
{
}

void PlayerStateCrouch::Update()
{
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_RIGHT) || KeyHanler::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		__Mario->SetState(new PlayerStateWalk());
		ExitCrouch();
	}

	if (KeyHanler::GetInstance()->IsKeyDown(DIK_X))
	{
		__Mario->SetState(new PlayerStateJump());
		ExitCrouch();
	}

	if (!KeyHanler::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		__Mario->SetState(new PlayerStateIdle());
		ExitCrouch();
	}

	if (__Mario->vx != 0)
		__Mario->vx -= MARIO_DRAG * __Mario->direction.x;
	if (__Mario->vx * __Mario->direction.x < 0)
		__Mario->vx = 0;

	if (!__Mario->isOnGround && __Mario->vy > 0)
		__Mario->SetState(new PlayerStateFall());
}

void PlayerStateCrouch::SetAnimation()
{
	__Mario->ani = MARIO_ANI_CROUCH;
}

void PlayerStateCrouch::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		__Mario->SetState(new PlayerStateJump());
		break;
	case DIK_A:
		if (__Mario->level > MARIO_LEVEL_BIG)
			__Mario->SetState(new PlayerStateAttack());
		break;
	}
}

void PlayerStateCrouch::ExitCrouch()
{
	if (__Mario->level != MARIO_LEVEL_SMALL)
	{
		__Mario->y -= MARIO_BIG_BBOX_HEIGHT - MARIO_CROUCH_BBOX_HEIGHT;
		__Mario->height = MARIO_BIG_BBOX_HEIGHT;
	}
}
