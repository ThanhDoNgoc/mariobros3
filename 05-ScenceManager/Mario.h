#pragma once
#pragma warning (disable : 4005)
#include "GameObject.h"
#include "KeyHanler.h"
#include "defineAni.h"
#include "defineMario.h"

#include "PlayerState.h"
#include "PlayerStateIdle.h"
#include "PlayerStateWalk.h"
#include "PlayerStateRun.h"
#include "PlayerStateEndGame.h"

#include "MarioLevel.h"
#include "MarioLevelSmall.h"
#include "MarioLevelBig.h"
#include "MarioLevelFire.h"
#include "MarioLevelRaccoon.h"

#define __Mario CMario::GetInstance()

class CMario : public CGameObject
{
	int untouchable;
	ULONGLONG untouchable_start, on_max_charge_start, kickStart;
	static CMario* __instance;

	float start_x;			// initial position of Mario at scene
	float start_y;
	LPGAMEOBJECT obj;
	//D3DXVECTOR2 direction = D3DXVECTOR2(1.0f,1.0f);
	bool canRemovePoop;

public:
	int ani = -1;
	int level;
	int fireball;
	int state;
	float width, height;
	bool isOnGround, isMaxCharge;
	bool isAttacking, isKicking, isHolding, isWarping;
	bool isEndScene;
	bool isDebuff;
	int jumpCount = 0;
	ULONGLONG removePoop_start;
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	float abilytiBar;
	PlayerState* _playerState;

	MarioLevel* _marioLevel;

	CMario(float x = 0.0f, float y = 0.0f);
	static CMario* GetInstance();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	//void SetState(int state);
	void SetState(PlayerState* newState);
	void SetLevel(int lvl);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartOnMaxCharge() { this->isMaxCharge = true; on_max_charge_start = GetTickCount64(); }
	void StartKick() { this->isKicking = true; kickStart = GetTickCount64(); }
	void TakeDamage();
	void Reset();
	void GetAnimation(int new_ani);

	void OnKeyUp(int KeyCode);
	void OnKeyDown(int KeyCode);

	virtual void OnOverLap(CGameObject* obj);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};