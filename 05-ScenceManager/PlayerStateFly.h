#pragma once
#include "PlayerState.h"
class PlayerStateFly : public PlayerState
{
	DWORD flyTimeStart;
public:
	PlayerStateFly();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartFly() { flyTimeStart = GetTickCount(); }
};

