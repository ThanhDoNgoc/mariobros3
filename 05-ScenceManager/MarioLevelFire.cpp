#include "MarioLevelFire.h"
#include "Mario.h"

MarioLevelFire::MarioLevelFire()
{
	__Mario->animation_set.clear();
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_IDLE);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_WALK);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_SKID);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_JUMP);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_FALL);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_RUN);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_CROUCH);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_WARP);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_IDLE_HOLD);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_RUN_HOLD);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_KICK);
	__Mario->AddAnimation(ID_ANI_FIRE_MARIO_ATTACK);

	this->width = MARIO_BIG_BBOX_WIDTH;
	this->height = MARIO_BIG_BBOX_HEIGHT;

	__Mario->level = MARIO_LEVEL_FIRE;
}

void MarioLevelFire::LevelDown()
{
	__Mario->_marioLevel = new MarioLevelBig();
	__Mario->StartUntouchable();
}

void MarioLevelFire::Attack()
{
}
