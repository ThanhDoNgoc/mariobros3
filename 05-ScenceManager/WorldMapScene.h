#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "KeyHanler.h"
#include "Map.h"
#include "HUD.h"
#include "WorldMapMario.h"
#define MAX_SCENE_LINE 1024

class WorldMapScene : public CScene
{
	WorldMapMario* player =0;
	Map* maps =0 ;
	HUD* hud = 0;
	float camL, camT, camR, camB;

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_CAMERA(string line);
	bool isEndGame = false;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	vector<LPGAMEOBJECT> addobjects;

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
	virtual void AddObjectInGame(LPGAMEOBJECT object) {};
	WorldMapMario * GetPlayer() { return player; }
	//void EndScene();
	//friend class CPlayScenceKeyHandler;
};

