#include "WorldMapScene.h"
#include "Portal.h"
using namespace std;

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

void WorldMapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new WorldMapMario();
		player = (WorldMapMario*)obj;
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
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

void WorldMapScene::_ParseSection_MAP(string line)
{
	tileMap = new Map();
	vector<string> tokens = split(line);
	const char* filepath = tokens[0].c_str();
	const char* path = tokens[1].c_str();
	tileMap->LoadMap(filepath, path);
}

void WorldMapScene::_ParseSection_CAMERA(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 4) return;
	this->camL = atof(tokens[0].c_str());
	this->camT = atof(tokens[1].c_str());
	this->camR = atof(tokens[2].c_str());
	this->camB = atof(tokens[3].c_str());
}

WorldMapScene::WorldMapScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
}

void WorldMapScene::Load()
{
	
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
	if (player == NULL) return;

	if (camera != NULL)
	{
		camera->Update();
	}
}

void WorldMapScene::Render()
{
	tileMap->Render(camera);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	hud->Render();
}

void WorldMapScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
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
