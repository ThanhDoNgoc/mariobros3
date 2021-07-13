#include "HUD.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Mario.h"
#include "GlobalVariables.h"

HUD::HUD()
{
}
void HUD::Load()
{
	
}

void HUD::Render()
{
	DrawBackground();
	auto sprite = CSprites::GetInstance();
	CSprite* hud = sprite->Get(40000);
	hud->Draw(SCREEN_WIDTH/2, (SCREEN_HEIGHT-90));
	DrawCoin();
	DrawScore();
	DrawTimer();
	DrawLife();
	DrawWorld();
	DrawAbilityBar();
	DrawCard();
	if (__Mario->isEndScene)
		DrawEndGame();
}

void HUD::DrawBackground()
{
	
}

void HUD::DrawCoin()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE num = sprites->Get(0);

	int coin = GlobalVariables::GetInstance()->GetCoin();
	string coinString = NumberToString(coin, 2);

	for (int i = 0; (unsigned)i < coinString.length(); i++)
	{
		if (coinString[i] == ' ')
			continue;

		for (int j = 0; j < 10; j++)
		{
			if (coinString[i] == 48 + j)
			{
				num = sprites->Get(j);
			}
		}
		if (coin < 10 && i == 0) continue;
		num->Draw(SCREEN_WIDTH / 2 + 58 + i*NUM_WIDTH, (SCREEN_HEIGHT - 112));
	}
}

void HUD::DrawScore()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE num = sprites->Get(0);
	int score = GlobalVariables::GetInstance()->GetScore();
	string scoreString = NumberToString(score, 7);
	for (int i = 0; (unsigned)i < scoreString.length(); i++)
	{

		if (scoreString[i] == ' ')
			continue;

		for (int j = 0; j < 10; j++)
		{
			if (scoreString[i] == 48 + j)
			{
				num = sprites->Get(j);
			}
		}
		num->Draw(SCREEN_WIDTH / 2 - 180 + i * NUM_WIDTH, (SCREEN_HEIGHT - 88));
	}
}

void HUD::DrawTimer()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE num = sprites->Get(0);
	int time = GlobalVariables::GetInstance()->GameTimeLeft()/1000;
	string scoreString = NumberToString(time, 3);
	for (int i = 0; (unsigned)i < scoreString.length(); i++)
	{

		if (scoreString[i] == ' ')
			continue;

		for (int j = 0; j < 10; j++)
		{
			if (scoreString[i] == 48 + j)
			{
				num = sprites->Get(j);
			}
		}
		num->Draw(SCREEN_WIDTH / 2 + 38 + i * NUM_WIDTH, (SCREEN_HEIGHT - 88));
	}
}

void HUD::DrawLife()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE num = sprites->Get(0);
	int life = GlobalVariables::GetInstance()->GetLife();
	num = sprites->Get(life);
	num->Draw(SCREEN_WIDTH / 2 - 230, (SCREEN_HEIGHT - 88));

}

void HUD::DrawWorld()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE num = sprites->Get(1);
	num->Draw(SCREEN_WIDTH / 2 - 230, (SCREEN_HEIGHT - 112));
}

void HUD::DrawAbilityBar()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE num = sprites->Get(SPRITE_ABILITY_OFF);
	int bar = __Mario->abilytiBar / ABILITY_BAR;
	for (int i = 0; i < 6; i++)
	{
		if (bar > i)
			num = sprites->Get(SPRITE_ABILITY_ON);
		else num = sprites->Get(SPRITE_ABILITY_OFF);
		num->Draw(SCREEN_WIDTH / 2 - 180 + i * NUM_WIDTH, (SCREEN_HEIGHT - 112));
	}
	LPSPRITE p = sprites->Get(SPRITE_P_OFF);
	if (bar == 6)
		p = sprites->Get(SPRITE_P_ON);
	else p = sprites->Get(SPRITE_P_OFF);
	p->Draw(SCREEN_WIDTH / 2 - 180 + 7 * NUM_WIDTH, (SCREEN_HEIGHT - 112));
}

void HUD::DrawEndGame()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE text = sprites->Get(20);
	text->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -200);
	LPSPRITE card = sprites->Get(0);
	auto cardCollected = GlobalVariables::GetInstance()->GetCardCollected();
	for (int i = 2; i >= 0; i--)
	{
		if (cardCollected[i] != 0)
		{
			DebugOut(L" get card end: %d \n ", cardCollected[i]);
			card = sprites->Get(16 + cardCollected[i]);
			card->Draw(SCREEN_WIDTH / 2+150, SCREEN_HEIGHT / 2 - 200);
			break;
		}
	}
}

std::string HUD::NumberToString(int num, int numOfChar)
{
	string numStr = to_string(num);
	int delta = numOfChar - numStr.length();
	for (int i = 0; i < delta; i++)
	{
		numStr = "0" + numStr;
	}
	return numStr;
}

void HUD::DrawCard()
{
	auto sprites = CSprites::GetInstance();
	LPSPRITE card = sprites->Get(0);
	auto cardCollected = GlobalVariables::GetInstance()->GetCardCollected();
	for (int i = 0; i < 3; i++)
	{
		if (cardCollected[i] != 0)
		{
			card = sprites->Get(14+i);
			card->Draw(SCREEN_WIDTH / 2 +168 +i*CARD_WIDTH, (SCREEN_HEIGHT - 90));
		}
	}
}
