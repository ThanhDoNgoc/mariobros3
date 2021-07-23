#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_INSTANCE_DEAD_VY	0.8f
#define GOOMBA_GRAVITY	0.003f
#define GOOMBA_JUMP_SPEED	0.8f
#define GOOMBA_BOUND_SPEED	0.3f

#define GOOMBA_BBOX_WIDTH	48
#define GOOMBA_BBOX_HEIGHT	45

#define GOOMBA_ANI_FLYING		0
#define GOOMBA_ANI_BOUNDING		1
#define GOOMBA_ANI_WALKING		2
#define GOOMBA_ANI_DIE			3

#define GOOMBA_DIE_TIME		300
#define GOOMBA_INSTANCE_DIE_TIME	2000
#define FOLLOW_RANGE	192
enum class ParaGoombaState
{
	jump,
	bound,
	walk,
	die,
	instancedead
};
class ParaGoomba : public CGameObject
{
	ULONGLONG die_time;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	int width, height;
	ParaGoombaState goombaState;
	float velocity;
	float velocityY;
	int boundCount;
public:
	ParaGoomba();
	virtual void SetState(ParaGoombaState state);
	virtual void TakeDamage();
	void InstanceDead();
	virtual void OnOverLap(CGameObject* obj);
};

