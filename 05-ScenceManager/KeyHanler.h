#pragma once
#pragma warning (disable : 4005)
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Utils.h"
#include "Game.h"

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

class KeyHanler
{
	static KeyHanler* __instance;

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 
	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
public:
	void InitKeyboard(HWND hWnd);
	void ProcessKeyboard();

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	bool IsKeyDown(int KeyCode);

	static KeyHanler* GetInstance();

};

