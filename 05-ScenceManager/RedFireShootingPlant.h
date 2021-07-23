#pragma once

#include "GameObject.h"

#define RED_FIRE_SHOOTING_PLANT_WIDTH	48
#define RED_FIRE_SHOOTING_PLANT_HEIGHT	96

#define ANI_ID_RED_FIRE_SHOOTING_PLANT_DOWN	0
#define ANI_ID_RED_FIRE_SHOOTING_PLANT_UP	1

#define RED_FIRE_SHOOTING_PLANT_SPEED 0.15f

#define RED_FIRE_SHOOTING_PLANT_WAIT_TIME 3000
#define RED_FIRE_SHOOTING_PLANT_HIDE_TIME 800
#define RED_FIRE_SHOOTING_PLANT_GROWTIME 100
#define FIREBALL_POS 24

enum class ShootPlantState {
	slideup,
	slidedown,
	idleup,
	idledown
};
enum class Aim
{
	up,
	down
};

class RedFireShootingPlant:public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void ShootFire();
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	float velocity=0;
	ShootPlantState state = ShootPlantState::slideup;
	Aim aim = Aim::down;
	float distance=0;
	ULONGLONG waitTime_start =0, hideTime_start=0;
public:
	RedFireShootingPlant();
	float fsheight=0;
	virtual void TakeDamage();
	void startWait() { this->waitTime_start = GetTickCount64(); }
	void startHide() { this->hideTime_start = GetTickCount64(); }
	virtual void OnOverLap(CGameObject* obj);
};
