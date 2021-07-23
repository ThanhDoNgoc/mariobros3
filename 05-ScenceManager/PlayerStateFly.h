#pragma once
#include "PlayerState.h"
class PlayerStateFly : public PlayerState
{
	ULONGLONG flyTimeStart;
public:
	PlayerStateFly();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartFly() { flyTimeStart = GetTickCount64(); }
};

