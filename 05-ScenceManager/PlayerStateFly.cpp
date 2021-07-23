#include "PlayerStateFly.h"
#include "Mario.h"

#include "PlayerStateFall.h"
#include "PlayerStateAttack.h"
PlayerStateFly::PlayerStateFly()
{
	__Mario->vy = -MARIO_FLY_SPEED;
	StartFly();
	__Mario->state = MARIO_STATE_FLY;
}

void PlayerStateFly::Update()
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
	if (GetTickCount64() - flyTimeStart > MARIO_FLY_TIME)
		__Mario->SetState(new PlayerStateFall());
}

void PlayerStateFly::SetAnimation()
{
	__Mario->ani = MARIO_ANI_SPECIAL_2;
}

void PlayerStateFly::OnKeyDown(int KeyCode)
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
