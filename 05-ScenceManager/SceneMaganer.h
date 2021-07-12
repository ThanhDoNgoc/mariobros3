#pragma once
#include "Scence.h"

class SceneMaganer
{
	static SceneMaganer* __instance;
	CScene* currentScene;

public:
	SceneMaganer();

	CScene* getCurrentScene() { return currentScene; };
	void SwitchScene(CScene* scene) { this->currentScene = scene; }
	static SceneMaganer* GetInstance();

	
	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
};

