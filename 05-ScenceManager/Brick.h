#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

#define ANI_BRICK	0
#define ANI_COIN	1

#define STATE_BRICK	0
#define STATE_COIN	1

#define COIN_TIME	5000
class CBrick : public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	DWORD coinTime;
public:
	CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void TakeDamage();
	virtual void InstanceDead() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void BrickToCoin();
	virtual void OnOverLap(CGameObject* obj);
	void Bound();
};