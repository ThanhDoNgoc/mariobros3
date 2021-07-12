#include "GlobalVariables.h"

GlobalVariables* GlobalVariables::__instance = NULL;
GlobalVariables::GlobalVariables()
{
	this->coin = 0;
	this->life = 4;
	this->plevel = 0;
	this->score = 0;
	this->time = 0;

	this->__instance = this;
	this->Game_time_start = GetTickCount();
}

void GlobalVariables::AddCard(int x)
{
	for (int i = 0; i < 3; i++)
	{
		if (cardCollected[i] == 0)
		{
			cardCollected[i] = x;
			break;
		}
	}
}

void GlobalVariables::ResetCard()
{
	for (int i = 0; i < 3; i++)
	{
		cardCollected[i] = 0;
	}
}

GlobalVariables* GlobalVariables::GetInstance()
{
	if (__instance == NULL)
		__instance = new GlobalVariables();
	return __instance;
}
