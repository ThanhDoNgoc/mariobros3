#include "MarioLevelBig.h"
#include "Mario.h"

MarioLevelBig::MarioLevelBig()
{
	__Mario->animation_set.clear();
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_IDLE);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_WALK);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_SKID);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_JUMP);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_FALL);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_RUN);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_CROUCH);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_WARP);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_IDLE_HOLD);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_RUN_HOLD);
	__Mario->AddAnimation(ID_ANI_BIG_MARIO_KICK);

	//__Mario->y -= 100;

	__Mario->width = MARIO_BIG_BBOX_WIDTH;
	__Mario->height = MARIO_BIG_BBOX_HEIGHT;

	__Mario->level = MARIO_LEVEL_BIG;
}

void MarioLevelBig::LevelDown()
{
	__Mario->_marioLevel = new MarioLevelSmall();
	__Mario->StartUntouchable();
}

void MarioLevelBig::Attack()
{
}
