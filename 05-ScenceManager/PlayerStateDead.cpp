#include "PlayerStateDead.h"
#include "Mario.h"
PlayerStateDead::PlayerStateDead()
{
	__Mario->state = MARIO_STATE_DIE;
	__Mario->isEndScene = true;
	__Mario->vy = -MARIO_JUMP_SPEED;
	GlobalVariables::GetInstance()->MinusLife();
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
