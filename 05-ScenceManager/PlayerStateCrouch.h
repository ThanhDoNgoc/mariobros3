#pragma once
#include "PlayerState.h"
#include "KeyHanler.h"

class PlayerStateCrouch : public PlayerState
{
public:
	PlayerStateCrouch();
	~PlayerStateCrouch();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
	void ExitCrouch();
};

