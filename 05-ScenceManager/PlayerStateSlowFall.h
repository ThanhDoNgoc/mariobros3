#pragma once
#include "PlayerState.h"
class PlayerStateSlowFall : public PlayerState
{
	ULONGLONG slowFallTimeStart;
public:
	PlayerStateSlowFall();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartSlowFall() { slowFallTimeStart = GetTickCount64(); }
};

