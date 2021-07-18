#include "PlayerStateDead.h"
#include "Mario.h"
PlayerStateDead::PlayerStateDead()
{
	__Mario->state = MARIO_STATE_DIE;
	__Mario->isEndScene = true;
	__Mario->vy = -1.0f;
	GlobalVariables::GetInstance()->MinusLife();
	__Mario->vx = 0;
}

void PlayerStateDead::Update()
{
}

void PlayerStateDead::SetAnimation()
{
	__Mario->ani = MARIO_ANI_SPECIAL;
}

void PlayerStateDead::OnKeyDown(int KeyCode)
{
}
