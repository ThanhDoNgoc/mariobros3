#pragma once
#include "PlayerState.h"
#include "KeyHanler.h"

class PlayerStateRun : public PlayerState
{
public:
	PlayerStateRun();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);
};
