#pragma once
#include "PlayerState.h"
class PlayerStateFall : public PlayerState
{
public:
	PlayerStateFall();
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);

};

