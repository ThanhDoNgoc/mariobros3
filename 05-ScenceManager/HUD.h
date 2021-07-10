#pragma once
#include <string>

#define ANI_HUD_MAIN 0
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 720
#define NUM_WIDTH	24
#define SPRITE_ABILITY_ON	10
#define SPRITE_ABILITY_OFF	11
#define SPRITE_P_ON			12
#define SPRITE_P_OFF		13
class HUD
{
	float startTime;
	float hudX;
	float hudY;
public:
	HUD();
	void Load();
	void Render();

	void DrawBackground();
	void DrawCoin();
	void DrawScore();
	void DrawTimer();
	void DrawLife();
	void DrawWorld();
	void DrawAbilityBar();

	std::string NumberToString(int num, int numOfChar);
};

