#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH		24
#define FIREBALL_BBOX_HEIGHT	24

#define FIREBALL_SPEED			0.5f
#define FIREBALL_GRAVITY		0.003f

#define FIREBALL_ANI			0

class MarioFireBall : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage() {};
	virtual void InstanceDead() {};

public:
	MarioFireBall(float posX, float posY, float direcX, float direcY);
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);

};

