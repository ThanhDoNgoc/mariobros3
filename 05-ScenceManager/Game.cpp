#include <iostream>
#include <fstream>

#include "Game.h"
#include "Utils.h"

#include "PlayScence.h"
#include "AniMaganer.h"
#include "WorldMapScene.h"
#include "IntroScene.h"
#define PLAY_SCENCE		2
#define MAP_SCENCE		1
#define INTRO_SCENCE	0
CGame * CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for 
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;									

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	/*screen_height = r.bottom + 1;
	screen_width = r.right + 1;*/

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw 
*/
void CGame::Draw(float x, float y, float cx, float cy, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DXVECTOR2 flip, int alpha)
{
	D3DXVECTOR3 p(x , y , 0);
	D3DXVECTOR3 center(cx ,cy, 0);

	RECT r; 
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	D3DXMATRIX mPre;
	D3DXMATRIX mFlip;

	spriteHandler->GetTransform(&mPre);
	spriteHandler->GetTransform(&mFlip);
	D3DXMatrixScaling(&mFlip, flip.x, flip.y, 0.0f);
	spriteHandler->SetTransform(&mFlip);
	if (flip.x < 0)
	{
		p.x = -p.x;
	}
	if (flip.y < 0)
	{
		p.y = -p.y;
	}
	spriteHandler->Draw(texture, &r, &center, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&mPre);
}

void CGame::DrawTileMap(float x, float y, int width, int height, LPDIRECT3DTEXTURE9 texture, RECT* Rect)
{
	D3DXVECTOR3 p(x + width/2, y + height/2, 0);
	D3DXVECTOR3 center((float)(width/2), (float)(height/2), 0);
	spriteHandler->Draw(texture, Rect, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
}

LPDIRECT3DTEXTURE9 CGame::LoadTexture(LPCWSTR texturePath, D3DCOLOR TransColor)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", texturePath);
		return NULL;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		TransColor,
		//D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", texturePath);
		return NULL;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
	return texture;
}


CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

/*
	Standard sweptAABB implementation
	Source: GameDev.net
*/
void CGame::SweptAABB(
	float ml, float mt,	float mr, float mb,			
	float dx, float dy,			
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry; 
	float t_exit; 

	t = -1.0f;			// no collision
	nx = ny = 0;
	 
	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr; 
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl- mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -999999.0f;
		tx_exit = 999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}
	
	if (dy == 0)
	{
		ty_entry = -99999.0f;
		ty_exit = 99999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}
	

	if (  (tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);
	
	if (t_entry > t_exit) return; 

	t = t_entry; 

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else 
	{
		nx = 0.0f;
		dy > 0?ny = -1.0f:ny = 1.0f;
	}

}


CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

#define MAX_GAME_LINE 1024


#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2
#define GAME_FILE_SECTION_ANIMATION 3
void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		current_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CGame::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);
	int type = atoi(tokens[2].c_str());

	LPSCENE scene;
	switch (type)
	{
	case PLAY_SCENCE:
		scene = new CPlayScene(id, path);
		scenes[id] = scene;
		break;
	case MAP_SCENCE:
		scene = new WorldMapScene(id, path);
		scenes[id] = scene;
		break;
	case INTRO_SCENCE:
		scene = new IntroScene(id, path);
		scenes[id] = scene;
		break;
	}
	//scenes[id] = scene;
}

void CGame::_ParseSection_ANIMATIONS(string line)
{
	AniMaganer::GetInstance()->LoadResource(line);
}

/*
	Load game campaign file and load/initiate first scene
*/
void CGame::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
		if (line == "[ANIMATIONS]") { section = GAME_FILE_SECTION_ANIMATION; continue; }
		//
		// data section
		//
		switch (section)
		{
			case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
			case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
			case GAME_FILE_SECTION_ANIMATION: _ParseSection_ANIMATIONS(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n",gameFile);

	SwitchScene(current_scene);
}

void CGame::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	scenes[current_scene]->Unload();;

	//CTextures::GetInstance()->Clear();
	//CSprites::GetInstance()->Clear();

	current_scene = scene_id;
	LPSCENE s = scenes[scene_id];
	s->Load();	
	GlobalVariables::GetInstance()->StartGameTime();
	__Mario->isEndScene = false;
	__Mario->SetState(new PlayerStateIdle());
}
