#pragma once
#include "Scence.h"

class SceneMaganer
{
	static SceneMaganer* __instance;
	CScene* currentScene;

public:
	CScene* getCurrentScene() { return currentScene; };
	static SceneMaganer* GetInstance();

};

