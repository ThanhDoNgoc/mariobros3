#pragma once
#include "Scence.h"
#include "PlayScence.h"

#define MAX_SCENE_LINE 1024

class AniMaganer
{
	AniMaganer();
	static AniMaganer* __instance;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
public:
	~AniMaganer();
	static AniMaganer* GetInstance();
	void LoadResource();
};

