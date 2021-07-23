#include "PlayerStateSlowFall.h"
#include "Mario.h"
#include "PlayerStateFall.h"
#include "PlayerStateAttack.h"
PlayerStateSlowFall::PlayerStateSlowFall()
{
	__Mario->vy = MARIO_SLOW_FALL_SPEED;
	StartSlowFall();
	__Mario->state = MARIO_STATE_SLOW_FALL;
}

void PlayerStateSlowFall::Update()
{
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		__Mario->direction.x = 1.0f;
		__Mario->vx = MARIO_MAX_WALKING_SPEED * __Mario->direction.x;
	}
	else if (KeyHanler::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		__Mario->direction.x = -1.0f;
		__Mario->vx = MARIO_MAX_WALKING_SPEED * __Mario->direction.x;
	}

	if (GetTickCount64() - slowFallTimeStart > MARIO_FLY_TIME)
		__Mario->SetState(new PlayerStateFall());

	if (__Mario->isOnGround)
		__Mario->SetState(new PlayerStateIdle());
}

void PlayerStateSlowFall::SetAnimation()
{
	__Mario->ani = MARIO_ANI_SPECIAL_1;
}

void PlayerStateSlowFall::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		if (__Mario->level == MARIO_LEVEL_RACCOON)
		{
			__Mario->SetState(new PlayerStateSlowFall());
		}
		break;
	case DIK_A:
		if (__Mario->level > MARIO_LEVEL_BIG)
			__Mario->SetState(new PlayerStateAttack());
		break;
	}
}
