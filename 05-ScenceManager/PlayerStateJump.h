#pragma once
#include "PlayerState.h"
class PlayerStateJump : public PlayerState
{
	bool isJumping;
	ULONGLONG jumpTimeStart;
public:
	PlayerStateJump();
	void Update() ;
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartJumpHigh() { isJumping = true; jumpTimeStart = GetTickCount64(); }
};

