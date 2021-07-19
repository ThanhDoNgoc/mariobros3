#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Map.h"
#include "GlobalVariables.h"
#include "MarioFireBall.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define SCENE_SECTION_CAMERA	8

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_GROUND	4
#define OBJECT_TYPE_FIREBALL	5

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj; 
		__Mario->isEndScene = false;
		DebugOut(L"[INFO] Player object created!\n");
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	//LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	AddObject(obj);
	//objects.push_back(obj);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	maps = new Map();
	vector<string> tokens = split(line);
	const char* filepath = tokens[0].c_str();
	const char* path = tokens[1].c_str();
	maps->LoadMap(filepath, path);
}

void CPlayScene::_ParseSection_CAMERA(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 4) return;
	this->camL = atof(tokens[0].c_str());
	this->camT = atof(tokens[1].c_str());
	this->camR = atof(tokens[2].c_str());
	this->camB = atof(tokens[3].c_str());
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[MAP]")
		{
			section = SCENE_SECTION_MAP; continue;
		
		}
		if (line == "[CAMERA]")
		{
			section = SCENE_SECTION_CAMERA; continue;

		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP:  _ParseSection_MAP(line); break;
			case SCENE_SECTION_CAMERA: _ParseSection_CAMERA(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	this->camera = new Camera();
	this->camera->SetCamPos(0, 0);
	this->camera->SetCamLimit(camL, camT, camR, camB);
	this->camera->SetCamTarget(player);
	this->isEndGame = false;
	this->waitEndScene_start = 0;
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	GlobalVariables::GetInstance()->StartGameTime();
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;


	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	if (earseobjects.size() > 0)
	{
		for (auto e : earseobjects)
		{
			for (size_t i = 0; i < objects.size(); i++)
			{
				if (objects[i] == e) objects.erase(objects.begin() + i);
			}
		}
		for (auto e : earseobjects) delete e;
		earseobjects.clear();
	}
	if (addobjects.size() > 0)
	{
		for (auto e : addobjects)
		{
			objects.push_back(e);
		}

		addobjects.clear();
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	if (camera != NULL)
	{
		camera->Update();
	}
	if (GlobalVariables::GetInstance()->GameTimeLeft() <= 0)
	{
		EndScene();
	}

	if (__Mario->isEndScene)
	{
		if (!isEndGame)
		{
			this->waitEndScene_start = GetTickCount();
			isEndGame = true;
			camera->setIsFollow(false);
		}
		if (GetTickCount() - this->waitEndScene_start >= END_GAME_TIME)
		{
			EndScene();
		}
	}
	if (GlobalVariables::GetInstance()->GetCoin() >= 100)
	{
		GlobalVariables::GetInstance()->ResetCoin();
		GlobalVariables::GetInstance()->AddLife();
	}
}

void CPlayScene::Render()
{
	maps->Render(camera);

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->objectLayer == j)
				objects[i]->Render();
		}
	}

	hud->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::OnKeyUp(int KeyCode)
{
	player->OnKeyUp(KeyCode);
}

void CPlayScene::OnKeyDown(int KeyCode)
{
	player->OnKeyDown(KeyCode);
	switch (KeyCode)
	{
	case DIK_O:
		EndScene();
		break;
	case DIK_I:
		CGame::GetInstance()->SwitchScene(1);
		break;
	}
}

void CPlayScene::EndScene()
{
	CGame::GetInstance()->SwitchScene(1);
	__Mario->isEndScene = false;
}
