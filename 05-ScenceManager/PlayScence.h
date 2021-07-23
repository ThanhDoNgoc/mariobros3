#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Camera.h"

#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Ground.h"

#include "KeyHanler.h"
#include "Map.h"
#include "HUD.h"
#include "Grid.h"
#define END_GAME_TIME	3000
class CPlayScene: public CScene
{
protected: 
	CMario *player=0;					// A play scene has to have player, right? 
	Map* maps=0;
	HUD* hud=0;
	Grid* grid=0;
	float camL=0, camT=0, camR=0, camB=0;

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_CAMERA(string line);
	void _ParseSection_GRID(string line);
	ULONGLONG waitEndScene_start=0;
	bool isEndGame=false;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	vector<LPGAMEOBJECT> addobjects;
	vector<LPGAMEOBJECT> activegameobject;
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void OnKeyUp(int KeyCode) override;
	virtual void OnKeyDown(int KeyCode) override;

	virtual void AddObject(LPGAMEOBJECT addobject) { objects.push_back(addobject);};
	virtual void DeleteObject(LPGAMEOBJECT object) { grid->DeleteObject(object); };
	virtual void AddObjectInGame(LPGAMEOBJECT object) { grid->AddObject(object); }
	CMario * GetPlayer() { return player; } 
	void EndScene();


	//friend class CPlayScenceKeyHandler;
};
