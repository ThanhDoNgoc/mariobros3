#include "PlayerStateEndGame.h"
#include "Mario.h"
PlayerStateEndGame::PlayerStateEndGame()
{
}

void PlayerStateEndGame::Update()
{
	__Mario->x = MARIO_WALKING_SPEED * __Mario->dt;
}

void PlayerStateEndGame::SetAnimation()
{
	__Mario->ani = MARIO_ANI_WALK;
}

void PlayerStateEndGame::OnKeyDown(int KeyCode)
{
}
