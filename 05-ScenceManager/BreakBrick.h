#pragma once
#include"GameObject.h"

#define ANI_ID_BREAK	0
#define BREAK_SPEED_X	0.1f
#define BREAK_SPEED_Y_H	0.25f
#define BREAK_SPEED_Y_L	0.05f

#define BREAK_WIDTH		24
#define BREAK_HEIGHT	24

#define BREAK_GRAVITY 0.003f
class BreakBrick : public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
public:
	BreakBrick(float x, float y, bool ishigh, bool isDirecRight);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void TakeDamage() {};
	virtual void InstanceDead() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

