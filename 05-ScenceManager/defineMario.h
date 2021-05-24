#pragma once

#define MARIO_WALKING_SPEED			0.0f
#define MARIO_MAX_WALKING_SPEED		0.25f
#define MARIO_MAX_RUNNING_SPEED		0.55f
#define MARIO_ACCELERATION			0.01f

#define MARIO_DRAG					0.01f
#define MARIO_DRAG_RUN				0.015f

#define MARIO_JUMP_SPEED			0.55f
#define MARIO_JUMP_SPEED_Y			0.35f
#define MARIO_JUMP_DEFLECT_SPEED	0.25f   //0.55f
#define MARIO_GRAVITY				0.002f
#define MARIO_DIE_DEFLECT_SPEED		0.5f
#define MARIO_SLOW_FALL_SPEED		0.1f


#define MARIO_ANI_IDLE			0
#define MARIO_ANI_WALK			1
#define MARIO_ANI_SKID			2
#define MARIO_ANI_JUMP			3
#define MARIO_ANI_FALL			4
#define MARIO_ANI_RUN			5
#define MARIO_ANI_JUMP_MAX		6
#define MARIO_ANI_FALL_MAX		7
#define MARIO_ANI_CROUCH		8
#define MARIO_ANI_WARP			9
#define MARIO_ANI_IDLE_HOLD		10
#define MARIO_ANI_RUN_HOLD		11
#define MARIO_ANI_KICK			12
#define MARIO_ANI_SPECIAL		13	// small - die || fire & raccoon - attack
#define MARIO_ANI_SPECIAL_1		14	// raccoon slow fall only
#define MARIO_ANI_SPECIAL_2		15	// raccoon fly only

#define	MARIO_LEVEL_SMALL	0
#define	MARIO_LEVEL_BIG		1
#define MARIO_LEVEL_FIRE	2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 81

#define MARIO_SMALL_BBOX_WIDTH  36
#define MARIO_SMALL_BBOX_HEIGHT 44

#define MARIO_UNTOUCHABLE_TIME		3000
#define MARIO_MAX_CHARGE_TIME		5000
#define MARIO_JUMP_TIME				300
#define MARIO_FLY_TIME				300
#define MARIO_SLOW_FALL_TIME		300
#define MARIO_FIRE_ATTACK_TIME		200
#define MARIO_RACCOON_ATTACK_TIME	400
#define MARIO_KICK_TIME				200