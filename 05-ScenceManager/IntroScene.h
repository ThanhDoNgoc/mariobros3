#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Camera.h"

#include "KeyHanler.h"
#include "Map.h"
#define MAX_SCENE_LINE 1024
class IntroScene : public CScene
{
	Map* maps;
	float camL, camT, camR, camB;
	int option = 0;
	DWORD startTime;
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_CAMERA(string line);
	DWORD waitEndScene_start;
	bool isEndGame = false;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	vector<LPGAMEOBJECT> addobjects;
public:
	IntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void OnKeyUp(int KeyCode) override;
	virtual void OnKeyDown(int KeyCode) override;

	virtual void AddObject(LPGAMEOBJECT addobject) { addobjects.push_back(addobject); };
	virtual void DeleteObject(LPGAMEOBJECT object) { earseobjects.push_back(object); };
	virtual void AddObjectInGame(LPGAMEOBJECT object) {};
	void DrawCurtain();
	void DrawBushs();
	void DrawFloor();
	void DrawTittle();
	void DrawSelection();
};

