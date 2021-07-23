#pragma once
#include "GameObject.h"
#define BBRRO_BBOX_WIDTH	48
#define BBRRO_BBOX_HEIGHT	72

#define BBRO_WALKING_SPEED	0.1f
#define BBRO_IDLE_TIME	300
#define BBRO_WALKING_DISTANCE	96
#define BBRO_GRAVITY	0.003f

#define ANI_ID_BBRO_NONE	0
#define ANI_ID_BBRO_ATTACK	1

#define BBRO_ATTACK_TIME		8000
#define BBRO_SECOND_ATTACK_TIME	2000
#define BBRO_ATTACK_WAIT_TIME	500

enum class BBroState
{
	walkleft ,
	walkright,
	idleleft,
	idleright
};
enum class BBroAttackSate
{
	NoneAttack1,
	WaitAttack1,
	NoneAttack2,
	WaitAttack2,
	NoneAttack3
};
class BoomerangBro : public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	BBroState bbroState;
	ULONGLONG idleTime;
	bool isDead = false;
	ULONGLONG startAttackTime;
	ULONGLONG waitAttackTime;
	bool waitAttack;
	BBroAttackSate bbroAtkState;
	
public:
	BoomerangBro();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage();
	virtual void OnOverLap(CGameObject* obj);
};

