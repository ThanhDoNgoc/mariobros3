#pragma once
#include "GameObject.h"
#define ANI_ID_GOOMBA_POOP	0

#define POOP_BBOX_WIDTH		24
#define POOP_BBOX_HEIGHT	27

#define POOP_FALL_SPEED	0.05f
#define POOP_FALL_SPEEDX	0.05f
#define POOP_ON_MARIO_SPEED	0.015f
#define POOP_CYCLE_TIME	800
#define POOP_DIE_FALL_SPEED	0.2f;
class GoombaPoop : public CGameObject
{
	ULONGLONG cycleTime;
	bool isDead;
	bool isOnMario;
	float movingX, movingY;
public:
	GoombaPoop();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage();
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	virtual void OnOverLap(CGameObject* obj);
};

