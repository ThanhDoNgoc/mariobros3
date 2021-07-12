#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_INSTANCE_DEAD_VY	0.8f
#define GOOMBA_GRAVITY	0.003f

#define GOOMBA_BBOX_WIDTH	48
#define GOOMBA_BBOX_HEIGHT	45

#define GOOMBA_STATE_WALKING		100
#define GOOMBA_STATE_DIE			200
#define GOOMBA_STATE_INSTANCE_DEAD	300

#define GOOMBA_ANI_WALKING	0
#define GOOMBA_ANI_DIE		1

#define GOOMBA_DIE_TIME		300
#define GOOMBA_INSTANCE_DIE_TIME	2000
enum class GoombaState
{
	walk,
	die,
	instancedead
};

class CGoomba : public CGameObject
{
	DWORD die_time;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	int width, height;
	GoombaState goombaState;
	float velocity;
public: 	
	CGoomba();
	virtual void SetState(GoombaState state);
	virtual void TakeDamage();
	void InstanceDead();
	virtual void OnOverLap(CGameObject* obj);
};