#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "NodeMap.h"
#define WORLD_MAP_MARIO_MOVE_SPEED		0.15f

#define WORLD_MAP_MARIO_ANI_SMALL		0
#define WORLD_MAP_MARIO_ANI_BIG			1
#define WORLD_MAP_MARIO_ANI_FIRE		2
#define WORLD_MAP_MARIO_ANI_RACOON		3

#define WORLD_MAP_MARIO_WIDTH	48
#define WORLD_MAP_MARIO_HEIGHT	48

class WorldMapMario :public CGameObject
{
	int level;
	int curentNode;
	bool ismovingx, ismovingy;
	NodeMap* map;
public:
	WorldMapMario();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update();
	virtual void Render();
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	int width, height;
	virtual void OnOverLap(CGameObject* obj) {};
	virtual void TakeDamage(){}
	void OnKeyUp(int KeyCode) {};
	void OnKeyDown(int KeyCode);
	void setMap(NodeMap* map);
	NodeMap* getMap();
};

