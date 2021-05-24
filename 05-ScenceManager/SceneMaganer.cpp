#include "SceneMaganer.h"

SceneMaganer* SceneMaganer::GetInstance()
{
	if (__instance == NULL)
		__instance = new SceneMaganer();
	return __instance;
}
