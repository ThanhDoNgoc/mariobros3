#pragma once
#include "GameObject.h"
#define CURTAIN_SPEED	0.15f;
#define ANI_ID_CURTAIN	0
class Curtain : public CGameObject
{
public:
	Curtain();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

