#include "PlayerStateWalk.h"

#include "KeyHanler.h"

#include "PlayerStateIdle.h"
#include "PlayerStateRun.h"
#include "PlayerStateJump.h"
#include "PlayerStateAttack.h"
#include "Mario.h"

PlayerStateWalk::PlayerStateWalk()
{
	DebugOut(L"[INFO] walk \n");
}

void PlayerStateWalk::Update()
{
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		__Mario->direction.x = 1.0f;
		__Mario->vx += MARIO_ACCELERATION * __Mario->direction.x;
	}
	else if (KeyHanler::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		__Mario->direction.x = -1.0f;
		__Mario->vx += MARIO_ACCELERATION * __Mario->direction.x;
	}
	else	
		__Mario->SetState(new PlayerStateIdle());


	if (KeyHanler::GetInstance()->IsKeyDown(DIK_A))
	{
		if (abs(__Mario->vx) > MARIO_MAX_RUNNING_SPEED)
				__Mario->SetState(new PlayerStateRun());
	}
	else
	{
		if (abs(__Mario->vx) > MARIO_MAX_WALKING_SPEED)
		{
			__Mario->vx = MARIO_MAX_WALKING_SPEED * __Mario->direction.x;
		}

	}
}

void PlayerStateWalk::SetAnimation()
{
	if (__Mario->direction.x * CMario::GetInstance()->vx < 0)
		__Mario->ani = MARIO_ANI_SKID;
	else
	{
		if (__Mario->isHolding)
			__Mario->ani = MARIO_ANI_RUN_HOLD;
		else
			__Mario->ani = MARIO_ANI_WALK;
	}
}

void PlayerStateWalk::OnKeyDown(int KeyCode)
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
