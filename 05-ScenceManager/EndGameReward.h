#pragma once
#include "GameObject.h"
#define ANI_REWARD_MUSHROOM	0
#define ANI_REWARD_FLOWER	1
#define ANI_REWARD_STAR		2

#define SWITCH_TIME	100

#define REWARD_STATE_MUSHROOM	0
#define REWARD_STATE_FLOWER		1
#define REWARD_STATE_STAR		2

#define REWARD_BBOX_WIDTH	78
#define REWARD_BBOX_HEIGHT	78

#define FLY_SPEED	0.25f
class EndGameReward : public CGameObject
{
	bool isCollected;
	ULONGLONG switchTime;
	int state;
	bool isAddCard;
public:
	EndGameReward();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
	virtual void OnOverLap(CGameObject* obj);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

