#pragma once
#include "PlayerState.h"
#include "KeyHanler.h"
class PlayerStateWarpJump : public PlayerState
{
public:
	PlayerStateWarpJump();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
};

