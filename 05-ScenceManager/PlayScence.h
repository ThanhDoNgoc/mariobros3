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
#define END_GAME_TIME	3000
class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	Map* maps;
	float camL, camT, camR, camB;

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_CAMERA(string line);
	DWORD waitEndScene_start;
	bool isEndGame=false;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	vector<LPGAMEOBJECT> addobjects;
	
public: 
	HUD* hud;
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void OnKeyUp(int KeyCode) override;
	virtual void OnKeyDown(int KeyCode) override;

	virtual void AddObject(LPGAMEOBJECT addobject) { addobjects.push_back(addobject); };
	virtual void DeleteObject(LPGAMEOBJECT object) { earseobjects.push_back(object); };
	CMario * GetPlayer() { return player; } 
	void EndScene();
	//friend class CPlayScenceKeyHandler;
};
