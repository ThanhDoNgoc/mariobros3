#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED		0.03f
#define KOOPAS_SHELL_MOVING_SPEED	0.35f
#define KOOPAS_INSTANCE_DEAD_VY		0.5f
#define KOOPAS_GRAVITY				0.003f


#define KOOPAS_BBOX_WIDTH	48
#define KOOPAS_BBOX_HEIGHT	48 
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING		100
#define KOOPAS_STATE_SHELL			200	
#define KOOPAS_STATE_SHELL_MOVING	300
#define KOOPAS_STATE_DIE			400
#define KOOPAS_STATE_BEING_HOLD		500

#define KOOPAS_ANI_WALKING		0
#define KOOPAS_ANI_SHELL		1
#define KOOPAS_ANI_SHELLMOVING	2

enum class KoopaState
{
	walk,
	shell,
	slide,
	die
};

class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float velocity;

public:
	CKoopas();
	KoopaState koopaState;
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	//bool isBeingHold = false;
	void SetState(KoopaState state);
	int GetState() { return 1; };
	virtual void TakeDamage();
	void InstanceDead();
	void BeingHold();
};