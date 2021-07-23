#include "WorldMapScene.h"
#include <iostream>
#include <fstream>
#include "Mario.h"
using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define SCENE_SECTION_CAMERA	8


#define OBJECT_TYPE_PORTAL	50

void WorldMapScene::_ParseSection_OBJECTS(string line)
{
}

void WorldMapScene::_ParseSection_MAP(string line)
{
	maps = new Map();
	vector<string> tokens = split(line);
	const char* filepath = tokens[0].c_str();
	const char* path = tokens[1].c_str();
	maps->LoadMap(filepath, path);
}

void WorldMapScene::_ParseSection_CAMERA(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 4) return;
	this->camL = (float)atof(tokens[0].c_str());
	this->camT = (float)atof(tokens[1].c_str());
	this->camR = (float)atof(tokens[2].c_str());
	this->camB = (float)atof(tokens[3].c_str());
}

WorldMapScene::WorldMapScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	camL = camT = camR = camB = 0;
}

void WorldMapScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);
	this->player = new WorldMapMario();
	player->SetPosition(96, 144);
	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;
	this->isEndScene = false;
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
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

	//this->player->level = CGame::GetInstance()->mariolvl;

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void WorldMapScene::Update(DWORD dt)
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
	if (player != NULL) player->Update(dt);

	if (camera != NULL)
	{
		camera->Update();
	}
}

void WorldMapScene::Render()
{
	maps->Render(camera);
	for (size_t  i = 0; i < objects.size(); i++)
		objects[i]->Render();
	player->Render();
	hud->Render();
}

void WorldMapScene::Unload()
{
	for (size_t  i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void WorldMapScene::OnKeyUp(int KeyCode)
{
	player->OnKeyUp(KeyCode);
}

void WorldMapScene::OnKeyDown(int KeyCode)
{
	player->OnKeyDown(KeyCode);
}
