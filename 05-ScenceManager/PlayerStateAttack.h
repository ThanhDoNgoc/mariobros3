#pragma once
#include "PlayerState.h"
class PlayerStateAttack : public PlayerState
{
	ULONGLONG attackTimeStart;
	ULONGLONG attack_time;
	ULONGLONG raccoonAttackDelay;
	bool cantailattack;
public:
	PlayerStateAttack();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartAttack() { attackTimeStart = GetTickCount64(); }
};

