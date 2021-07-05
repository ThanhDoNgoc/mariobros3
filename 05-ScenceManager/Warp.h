#pragma once
#include "GameObject.h"
#define WARP_WIDTH	48;
#define WARP_HEIGHT	24;

enum class WarpDirection
{
	up,
	down
};

class Warp : public CGameObject
{
	WarpDirection direc;
public:
	Warp();
	float toX, toY;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnOverLap(CGameObject* obj);
	virtual void setWarpDirection(WarpDirection dir);
	WarpDirection getWarpDirection();
	virtual void Render();
	int getKeyDirection();
	virtual void TakeDamage() {};
	bool isDown();
};

