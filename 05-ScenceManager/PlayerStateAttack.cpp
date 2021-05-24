#include "PlayerStateAttack.h"
#include "Mario.h"
#include "MarioFireBall.h"
#include "GameObject.h"
#include "Scence.h"
#include "Game.h"

PlayerStateAttack::PlayerStateAttack()
{
	switch (__Mario->level)
	{
	case MARIO_LEVEL_FIRE:
	{
		this->attack_time = MARIO_FIRE_ATTACK_TIME;
		MarioFireBall* fireball = new MarioFireBall(__Mario->x + MARIO_BIG_BBOX_WIDTH / 2, __Mario->y, __Mario->direction.x, __Mario->direction.y);
		//CScene::AddObject(fireball);
		CGame::GetInstance()->GetCurrentScene()->AddObject(fireball);
		break;
	}
	case MARIO_LEVEL_RACCOON:
		this->attack_time = MARIO_RACCOON_ATTACK_TIME;
		break;
	}
	StartAttack();
}

void PlayerStateAttack::Update()
{
	
	if (GetTickCount() - attackTimeStart > attack_time)
	{
		__Mario->SetState(new PlayerStateIdle);
	}
}

void PlayerStateAttack::SetAnimation()
{
	__Mario->ani = MARIO_ANI_SPECIAL;
}

void PlayerStateAttack::OnKeyDown(int KeyCode)
{
}
