#include "PlayerStateIdle.h"

#include "PlayerStateWalk.h"
#include "PlayerStateJump.h"
#include "PlayerStateFall.h"
#include "KeyHanler.h"
#include "Mario.h"

PlayerStateIdle::PlayerStateIdle()
{
	DebugOut(L"[INFO] idle \n");
}

void PlayerStateIdle::Update()
{
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_RIGHT) || KeyHanler::GetInstance()->IsKeyDown(DIK_LEFT))
		__Mario->SetState(new PlayerStateWalk());
	
	if (KeyHanler::GetInstance()->IsKeyDown(DIK_X))
		__Mario->SetState(new PlayerStateJump());

	if (__Mario->vx != 0)
		__Mario->vx -= MARIO_DRAG * __Mario->direction.x;
	if (__Mario->vx * __Mario->direction.x < 0)
		__Mario->vx = 0;

	if (!__Mario->isOnGround && __Mario->vy > 0)
		__Mario->SetState(new PlayerStateFall());

}


void PlayerStateIdle::SetAnimation()
{
	if (__Mario->vx != 0)
		__Mario->ani = MARIO_ANI_WALK;
	else
		__Mario->ani = MARIO_ANI_IDLE;
}

void PlayerStateIdle::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		__Mario->SetState(new PlayerStateJump());
		break;

	}
}
