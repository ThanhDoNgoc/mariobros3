#pragma once
#include "GameObject.h"

#define MUSIC_BBOX_WIDTH  48
#define MUSIC_BBOX_HEIGHT 48

#define ANI_MUSIC_BLOCK	0
#define MUSIC_BOUND_POSITION	12
#define MUSIC_VELOCITY	0.05f

class MusicNode : public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	bool boundUp, boundDown;

public:
	MusicNode();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnOverLap(CGameObject* obj);

};

