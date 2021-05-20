#include "MarioLevelRaccoon.h"
#include "Mario.h"
MarioLevelRaccoon::MarioLevelRaccoon()
{
	__Mario->animation_set.clear();
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_IDLE);			//0
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_WALK);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_SKID);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_JUMP);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_FALL);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_RUN);			//5
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_FALL_MAX);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_CROUCH);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_WARP);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_IDLE_HOLD);		//10
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_RUN_HOLD);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_KICK);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_ATTACK);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_SLOW_FALL);
	__Mario->AddAnimation(ID_ANI_RACCOON_MARIO_FLY);
	
	this->width = MARIO_BIG_BBOX_WIDTH;
	this->height = MARIO_BIG_BBOX_HEIGHT;

	__Mario->level = MARIO_LEVEL_RACCOON;
}

void MarioLevelRaccoon::LevelDown()
{
	__Mario->_marioLevel = new MarioLevelBig();
	__Mario->StartUntouchable();
}

void MarioLevelRaccoon::Attack()
{

}
