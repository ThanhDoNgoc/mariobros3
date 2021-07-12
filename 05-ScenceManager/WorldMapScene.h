#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Scence.h"
#include "TileMap.h"
#include "HUD.h"
#include "Map.h"
#include "KeyHanler.h"
#include "WorldMapMario.h"
#define MAX_SCENE_LINE 1024

class WorldMapScene : public CScene
{
	WorldMapMario* player;
	HUD* hud;
	Map* tileMap;
	
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	vector<LPGAMEOBJECT> addobjects;

	float camL, camT, camR, camB;

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_CAMERA(string line);

public:
	WorldMapScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void OnKeyUp(int KeyCode) override;
	virtual void OnKeyDown(int KeyCode) override;

	virtual void AddObject(LPGAMEOBJECT addobject) { addobjects.push_back(addobject); };
	virtual void DeleteObject(LPGAMEOBJECT object) { earseobjects.push_back(object); };
};

