#pragma once
#include "PlayerState.h"
class PlayerStateJump : public PlayerState
{
	bool isJumping;
	DWORD jumpTimeStart;
public:
	PlayerStateJump();
	void Update() ;
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void StartJumpHigh() { isJumping = true; jumpTimeStart = GetTickCount(); }
};

