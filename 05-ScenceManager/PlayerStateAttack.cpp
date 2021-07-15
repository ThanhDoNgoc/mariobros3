#include "PlayerStateAttack.h"
#include "Mario.h"
#include "MarioFireBall.h"
#include "MarioRaccoonTail.h"
#include "GameObject.h"
#include "Scence.h"
#include "Game.h"

PlayerStateAttack::PlayerStateAttack()
{
	this->cantailattack = false;
	switch (__Mario->level)
	{
	case MARIO_LEVEL_FIRE:
	{
		this->attack_time = MARIO_FIRE_ATTACK_TIME;
		if (__Mario->fireball > 0)
		{
			__Mario->fireball -= 1;
			MarioFireBall* fireball1 = new MarioFireBall(__Mario->x + MARIO_BIG_BBOX_WIDTH / 2, __Mario->y, __Mario->direction.x, __Mario->direction.y);
			CGame::GetInstance()->GetCurrentScene()->AddObject(fireball1);
		}
		break;
	}
	case MARIO_LEVEL_RACCOON:
		this->attack_time = MARIO_RACCOON_ATTACK_TIME;
		this->raccoonAttackDelay = GetTickCount();
		this->cantailattack = true;
		if (__Mario->direction.x >= 1)
		{
			MarioRaccoonTail* tail = new MarioRaccoonTail(__Mario->x + MARIO_BIG_BBOX_WIDTH / 2 - 50, __Mario->y + 50);
			CGame::GetInstance()->GetCurrentScene()->AddObject(tail);
		}
		else if (__Mario->direction.x <= -1)
		{
			MarioRaccoonTail* tail = new MarioRaccoonTail(__Mario->x + MARIO_BIG_BBOX_WIDTH / 2, __Mario->y + 50);
			CGame::GetInstance()->GetCurrentScene()->AddObject(tail);
		}
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
	if (__Mario->level == MARIO_LEVEL_RACCOON)
	{
		if (GetTickCount() - raccoonAttackDelay > RACCOON_ATTACK_DELAY && cantailattack)
		{
			cantailattack = false;
			if (__Mario->direction.x >= 1)
			{
				MarioRaccoonTail* tail = new MarioRaccoonTail(__Mario->x + MARIO_BIG_BBOX_WIDTH / 2, __Mario->y + 50);
				CGame::GetInstance()->GetCurrentScene()->AddObject(tail);
			}
			else if (__Mario->direction.x <= -1)
			{
				MarioRaccoonTail* tail = new MarioRaccoonTail(__Mario->x + MARIO_BIG_BBOX_WIDTH / 2 - 50, __Mario->y + 50);
				CGame::GetInstance()->GetCurrentScene()->AddObject(tail);
			}
		}
	}
}

void PlayerStateAttack::SetAnimation()
{
	__Mario->ani = MARIO_ANI_SPECIAL;
}

void PlayerStateAttack::OnKeyDown(int KeyCode)
{
}
