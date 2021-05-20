#pragma once
#include "PlayerState.h"
#include "KeyHanler.h"

class PlayerStateWalk : public PlayerState
{
public:
	PlayerStateWalk();
	void Update() ;
	void SetAnimation() ;
	void OnKeyDown(int KeyCode);
};

