#include "MarioLevelSmall.h"
#include "Mario.h"

MarioLevelSmall::MarioLevelSmall()
{
	__Mario->animation_set.clear();
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_IDLE);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_WALK);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_SKID);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_JUMP);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_JUMP);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_RUN);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_JUMP_MAX);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_IDLE);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_WARP);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_IDLE_HOLD);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_RUN_HOLD);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_KICK);
	__Mario->AddAnimation(ID_ANI_SMALL_MARIO_DIE);

	this->width = MARIO_SMALL_BBOX_WIDTH;
	this->height = MARIO_SMALL_BBOX_HEIGHT;

	__Mario->level = MARIO_LEVEL_SMALL;

}

void MarioLevelSmall::LevelDown()
{
}
