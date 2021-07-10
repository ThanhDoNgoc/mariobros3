#pragma once
#include "GameObject.h"

#define QBLOCK_BBOX_WIDTH  48
#define QBLOCK_BBOX_HEIGHT 48

#define ANI_QUESTION_BLOCK	0
#define ANI_QUESTION_BLOCK_CLAIMED	1
#define ANI_BRICK	2
#define DISTANCE	16
enum class Item
{
	GreenMushroom,
	Coin,
	RedMushroom,
	Leaf,
	Flower,
	PButton
};

class QuestionBlock : public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	bool isClaimed = false;
	Item qblockItem;
	float distance;
public:
	QuestionBlock();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetItem(string item);
	void SpawnItem();
	virtual void OnOverLap(CGameObject* obj);
};

