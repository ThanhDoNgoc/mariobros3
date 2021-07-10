#pragma once
#include "PlayerState.h"
class PlayerStateAttack : public PlayerState
{
	DWORD attackTimeStart;
	int attack_time;
	DWORD raccoonAttackDelay;
	bool cantailattack;
public:
	PlayerStateAttack();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartAttack() { attackTimeStart = GetTickCount(); }
};

