#pragma once
#include "GameObject.h"

#define MUSHROOM_SPEED  0.1f
#define MUSHROOM_GRAVITY  0.0015f

#define SPROUT_SPEED  0.1f

#define MUSHROOM_WIDTH 48
#define MUSHROOM_HEIGHT 48

#define ANI_ID_MUSHROOM	0;

class RedMushroom : public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	int state;
	bool isOut;
	float distance;
	bool setVx;
	float velocity;
public:
	RedMushroom();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage();
	virtual void OnOverLap(CGameObject* obj);
};

