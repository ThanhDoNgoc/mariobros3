#pragma once
#include "MarioLevel.h"
class MarioLevelFire : public MarioLevel
{
	DWORD attack_time_start;
public:
	MarioLevelFire();
	void LevelDown();
	void Attack();
	void StartAttack() { attack_time_start= GetTickCount(); }
};

