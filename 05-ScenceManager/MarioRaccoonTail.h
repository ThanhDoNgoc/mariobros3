#pragma once
#include "GameObject.h"
#define TAIL_BBOX_WIDTH	50
#define	TAIL_BBOX_HEIGHT	20
#define ATTACK_TIME	200
class MarioRaccoonTail : public CGameObject
{
	ULONGLONG deleteTime;
public:
	MarioRaccoonTail(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage();
	virtual void OnOverLap(CGameObject* obj);
};

