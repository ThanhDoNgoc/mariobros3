#include "PlayerStateRun.h"

#include "PlayerStateWalk.h"
#include "PlayerStateIdle.h"
#include "PlayerStateJump.h"
#include "PlayerStateAttack.h"
#include "Mario.h"

PlayerStateRun::PlayerStateRun()
{
	DebugOut(L"[INFO] RUN \n");
	//this->velocity = MARIO_MAX_RUNNING_SPEED * __Mario->direction.x;
}

void PlayerStateRun::Update()
{
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_RIGHT))
		__Mario->direction.x = 1.0f;
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_LEFT))
		__Mario->direction.x = -1.0f;


	if (!KeyHanler::GetInstance()->IsKeyDown(DIK_A) || __Mario->vx * __Mario->direction.x < 0)
		__Mario->SetState(new PlayerStateWalk());

}

void PlayerStateRun::SetAnimation()
{
		__Mario->ani = MARIO_ANI_RUN;
}

void PlayerStateRun::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		__Mario->StartOnMaxCharge();
		__Mario->SetState(new PlayerStateJump());
		break;
	case DIK_A:
		if (__Mario->level > MARIO_LEVEL_BIG)
			__Mario->SetState(new PlayerStateAttack());
		break;
	}
}
