#pragma once
#include "GameObject.h"
#define LEAF_REVEAL_TIME 300
#define LEAF_REVEAL_VY 0.4f

#define LEAF_GRAVITY  0.0012f
#define LEAF_FALLING_VEL 0.055f
#define LEAF_FALLING_VX 0.15f
#define LEAF_CYCLE_TIME 900

#define LEAF_WIDTH 48
#define LEAF_HEIGHT 42

#define ANI_ID_LEAF	0

#define DELAY 1

class Leaf:public CGameObject
{
	bool isClaimed;
	DWORD timeClaimed;
	DWORD leafRevealTime, cycleTime;
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	int state;
public:
	Leaf();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
};

