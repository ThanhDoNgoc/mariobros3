#pragma once
#include "GameObject.h"

#define PBUTTON_BBOX_WIDTH 48
#define PBUTTON_BBOX_HEIGHT 48

#define ANI_ID_P_BUTTON		0
#define ANI_ID_P_CLAIMED	1
class PButton : public CGameObject
{
	bool isClaimed;
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
public:
	PButton();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage();
	virtual void OnOverLap(CGameObject* obj);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

