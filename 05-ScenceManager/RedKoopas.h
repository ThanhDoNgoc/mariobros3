#pragma once
#include "GameObject.h"
#define KOOPAS_WALKING_SPEED		0.03f
#define KOOPAS_SHELL_MOVING_SPEED	0.35f
#define KOOPAS_INSTANCE_DEAD_VY		0.8f
#define KOOPAS_GRAVITY				0.003f
#define KOOPAS_FLY 0.7f
#define KOOPAS_FLY_SPEED 0.1f

#define KOOPAS_BBOX_WIDTH	45
#define KOOPAS_BBOX_HEIGHT	51 
#define KOOPAS_BBOX_HEIGHT_DIE 16


#define KOOPAS_ANI_WALKING		0
#define KOOPAS_ANI_SHELL		1
#define KOOPAS_ANI_SHELLMOVING	2

#define TIME_RESTORE_MOVE 4000

enum class RedKoopaState
{
	walk,
	shell,
	slide,
	die,
	troppa
};

class RedKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD startShellTime;
	float velocity;
public:
	RedKoopas();
	RedKoopaState koopaState;
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	void SetState(RedKoopaState state);
	virtual void TakeDamage();
	void InstanceDead();
	virtual void OnOverLap(CGameObject* obj);
};

