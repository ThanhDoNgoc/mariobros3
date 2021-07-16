#pragma once
#include "PlayerState.h"
class PlayerStateEndGame : public PlayerState
{
public:
	PlayerStateEndGame();
	virtual void Update();
	virtual void SetAnimation();
	virtual void OnKeyDown(int KeyCode);
};

