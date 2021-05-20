#pragma once
#include "PlayerState.h"
#include "KeyHanler.h"

class PlayerStateIdle : public PlayerState
{
public:
	PlayerStateIdle();
	void Update() ;
	void SetAnimation() ;
	void OnKeyDown(int KeyCode);
};

