#include "PlayerStateEndGame.h"
#include "Mario.h"
PlayerStateEndGame::PlayerStateEndGame()
{
	this->startEndScene = GetTickCount();
	__Mario->direction.x = 1.0f;
}

void PlayerStateEndGame::Update()
{
	__Mario->vx = MARIO_MAX_WALKING_SPEED ;
	if (GetTickCount() - startEndScene > WAIT_END_TIME)
		__Mario->isEndScene = true;
}

void PlayerStateEndGame::SetAnimation()
{
	__Mario->ani = MARIO_ANI_WALK;
}

void PlayerStateEndGame::OnKeyDown(int KeyCode)
{
}
