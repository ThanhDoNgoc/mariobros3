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


class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 

	Map* maps;

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);

	
public: 
	vector<LPGAMEOBJECT> objects;
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void OnKeyUp(int KeyCode) override;
	virtual void OnKeyDown(int KeyCode) override;

	virtual void AddObject(LPGAMEOBJECT addobject) { objects.push_back(addobject); };
	virtual void DeleteObject(LPGAMEOBJECT object);

	CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};
