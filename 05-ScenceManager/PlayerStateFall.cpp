#include "PlayerStateFall.h"
#include "Mario.h"

#include "PlayerStateFly.h"
#include "PlayerStateSlowFall.h"
#include "PlayerStateAttack.h"

PlayerStateFall::PlayerStateFall()
{
	DebugOut(L"[INFO] Fall \n");
}

void PlayerStateFall::Update()
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
	if (__Mario->isOnGround)
		__Mario->SetState(new PlayerStateIdle());
}

void PlayerStateFall::SetAnimation()
{
	if (!__Mario->isMaxCharge)
		__Mario->ani = MARIO_ANI_FALL;
	else
		__Mario->ani = MARIO_ANI_FALL_MAX;
}

void PlayerStateFall::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		if (__Mario->level == MARIO_LEVEL_RACCOON)
		{
			if (__Mario->isMaxCharge)
				__Mario->SetState(new PlayerStateFly());
			else
				__Mario->SetState(new PlayerStateSlowFall());
		}
		break;
	case DIK_A:
		if (__Mario->level > MARIO_LEVEL_BIG)
			__Mario->SetState(new PlayerStateAttack());
		break;
	}
}
