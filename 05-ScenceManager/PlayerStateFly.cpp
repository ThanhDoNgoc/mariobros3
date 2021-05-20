#include "PlayerStateFly.h"
#include "Mario.h"

#include "PlayerStateFall.h"
PlayerStateFly::PlayerStateFly()
{
	__Mario->vy = -MARIO_JUMP_SPEED;
	StartFly();
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
	if (GetTickCount() - flyTimeStart > MARIO_FLY_TIME)
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
	}
}
