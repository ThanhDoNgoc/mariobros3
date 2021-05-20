#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "KeyHanler.h"
#include "defineMario.h"


class PlayerState
{
public:
	PlayerState() {};
	virtual void Update() {};
	virtual void SetAnimation() {};
	virtual void OnKeyDown(int KeyCode) {};

};