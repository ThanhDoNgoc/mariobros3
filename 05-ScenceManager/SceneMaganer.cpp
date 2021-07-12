#include "SceneMaganer.h"
SceneMaganer* SceneMaganer::__instance = NULL;
SceneMaganer::SceneMaganer()
{
	this->__instance = this;
}

SceneMaganer* SceneMaganer::GetInstance()
{
	if (__instance == NULL)
		__instance = new SceneMaganer();
	return __instance;
}

void SceneMaganer::Load()
{
	currentScene->Load();
}

void SceneMaganer::Unload()
{
	currentScene->Unload();
}

void SceneMaganer::Update(DWORD dt)
{
	currentScene->Update(dt);
}

void SceneMaganer::Render()
{
	currentScene->Render();
}
