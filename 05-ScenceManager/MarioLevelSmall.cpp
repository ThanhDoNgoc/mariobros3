#include "MarioLevelSmall.h"
#include "Mario.h"
#include "PlayerStateDead.h"
#include "GlobalVariables.h"
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

	__Mario->width = MARIO_SMALL_BBOX_WIDTH;
	__Mario->height = MARIO_SMALL_BBOX_HEIGHT;

	__Mario->level = MARIO_LEVEL_SMALL;
	CGame::GetInstance()->mariolvl = MARIO_LEVEL_SMALL;

}

void MarioLevelSmall::LevelDown()
{
	__Mario->SetState(new PlayerStateDead());
	__Mario->StartUntouchable();
}
