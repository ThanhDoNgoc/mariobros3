#pragma once
#include "PlayerState.h"
#include "KeyHanler.h"
class PlayerStateWarp : public PlayerState
{
	float distance;
	float toX, toY;
	bool isDown;
public:
	PlayerStateWarp(bool down, float posX, float posY);
	void Update();
	void SetAnimation();
	void OnKeyDown(int KeyCode);

};

