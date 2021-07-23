#pragma once
#include "GameObject.h"

#define GREENEATING_WIDTH 48
#define GREENEATING_HEIGHT 72

#define GREENEATING_WAIT 3000
#define GREENEATING_HIDE 800

#define GREENEATING_GROWTIME 100

#define GREENEATING_SPEED 0.15f


enum class GreeneatingState
{
	slideup,
	slidedown,
	idleup,
	idledown
};


class GreenEatingPlant : public CGameObject
{
	DWORD waitTime_start, hideTime_start;
	float distance;
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	GreeneatingState state;
public:
	GreenEatingPlant();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage();
	virtual void OnOverLap(CGameObject* obj);
};

