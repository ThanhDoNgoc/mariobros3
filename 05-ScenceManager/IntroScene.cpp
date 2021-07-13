#include "IntroScene.h"
#include <iostream>
#include <fstream>
using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define SCENE_SECTION_CAMERA	8

void IntroScene::_ParseSection_OBJECTS(string line)
{
}

void IntroScene::_ParseSection_MAP(string line)
{
	maps = new Map();
	vector<string> tokens = split(line);
	const char* filepath = tokens[0].c_str();
	const char* path = tokens[1].c_str();
	maps->LoadMap(filepath, path);
}

void IntroScene::_ParseSection_CAMERA(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 4) return;
	this->camL = atof(tokens[0].c_str());
	this->camT = atof(tokens[1].c_str());
	this->camR = atof(tokens[2].c_str());
	this->camB = atof(tokens[3].c_str());
}

IntroScene::IntroScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	
}

void IntroScene::Load()
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


	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void IntroScene::Update(DWORD dt)
{
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
}

void IntroScene::Render()
{
	maps->Render(camera);
	DrawCurtain();
	DrawBushs();
	DrawFloor();
	DrawTittle();
	DrawSelection();
	DrawBushs();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void IntroScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();


	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void IntroScene::OnKeyUp(int KeyCode)
{
}

void IntroScene::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		this->option = 0;
		break;
	case DIK_DOWN:
		this->option = 1;
		break;
	case DIK_A:
		if (this->option == 0)
		{
			CGame::GetInstance()->SwitchScene(1);
		}
		break;
	}

}

void IntroScene::DrawCurtain()
{
	auto sprite = CSprites::GetInstance();
	CSprite* cutrain = sprite->Get(90010);
	cutrain->Draw(0,0);
}

void IntroScene::DrawBushs()
{
	auto sprite = CSprites::GetInstance();
	CSprite* bushleft = sprite->Get(90003);
	CSprite* bushright = sprite->Get(90002);
	bushleft->Draw(0, SCREEN_HEIGHT - 102-192);
	bushright->Draw(SCREEN_WIDTH-165, SCREEN_HEIGHT - 102 - 288);
}

void IntroScene::DrawFloor()
{
	auto sprite = CSprites::GetInstance();
	CSprite* floor = sprite->Get(90001);
	floor->Draw(0, SCREEN_HEIGHT-102);
}

void IntroScene::DrawTittle()
{
	auto animation = CAnimations::GetInstance();
	CAnimation* tittle = animation->Get(105);
	tittle->Render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-140);
}

void IntroScene::DrawSelection()
{
	auto sprite = CSprites::GetInstance();
	CSprite* choose = sprite->Get(90008);
	if (this->option == 0)
		choose = sprite->Get(90008);
	else choose = sprite->Get(90009);
	choose->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+150);
	//p2->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
