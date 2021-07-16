#pragma once
#include"PlayerState.h"
class PlayerStateDead : public PlayerState
{
public:
	PlayerStateDead();
	virtual void Update();
	virtual void SetAnimation();
	virtual void OnKeyDown(int KeyCode);
};

