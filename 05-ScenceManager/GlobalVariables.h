#pragma once
#include <d3dx9.h>
#include <directxmath.h>
#include <vector>
#include <string>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"SuperMarioBros3"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(181, 235, 242)
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 720

#define CAMERA_WIDTH	768
#define CAMERA_HEIGHT	576

#define CAMERA_DEFAULT_SCROLLING_SPEED_VX 2.0f
#define CAMERA_DEFAULT_SCROLLING_SPEED_VY 2.0f

#define KEYBOARD_BUFFER_SIZE 1024

#define PSWITCH_TIME  10000

#define GAME_TIME 300000

#define PLAY_STATE_PLAYING	0
#define PLAY_STATE_LOSE		1
#define PLAY_STATE_VICTORY	2

class GlobalVariables
{
	static GlobalVariables* __instance;
	long score;
	int life, coin;
	int time;
	int plevel;
	int mariolevel;
	int playstate = 0;

	DWORD Ptime_start;

	DWORD Game_time_start;

public:
	GlobalVariables();
	void ResetScore() { this->score = 0; }
	void AddScore(long s) { this->score += s; }
	int GetScore() { return this->score; }

	void ResetCoin() { this->coin = 0; }
	void AddCoin(int x) { this->coin += x; }
	int GetCoin() { return this->coin; }

	void ResetLife() { this->life = 4; }
	void AddLife() { this->life += 1; }
	int GetLife() { return this->life; }

	void updatePlevel(int x) { this->plevel = x; }
	int getPlevel() { return this->plevel; }

	void StartPtime() { this->Ptime_start = GetTickCount(); }
	bool isPtime(){return ((GetTickCount() - Ptime_start) <= PSWITCH_TIME);}

	void StartGameTime() { this->Game_time_start = GetTickCount(); }
	DWORD GameTimeLeft() { return GAME_TIME - (GetTickCount() - this->Game_time_start); }


	static GlobalVariables* GetInstance();

};

