#pragma once
#include "PlayerState.h"
#define WAIT_END_TIME 1500
class PlayerStateEndGame : public PlayerState
{
	DWORD startEndScene;
public:
	PlayerStateEndGame();
	virtual void Update();
	virtual void SetAnimation();
	virtual void OnKeyDown(int KeyCode);
};

