#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include "Utils.h"
#include <dinput.h>

#include "KeyHanler.h"
#include "Camera.h"
#include "GlobalVariables.h"

#include "Scence.h"

using namespace std;


class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	//int screen_width;
	//int screen_height; 

	unordered_map<int, LPSCENE> scenes;
	int current_scene; 

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
	void _ParseSection_ANIMATIONS(string line);

public:
	void Init(HWND hWnd);
	void Draw(float x, float y, float cx, float cy, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DXVECTOR2 flip = D3DXVECTOR2(1.0f, 1.0f) , int alpha = 255);
	void DrawTileMap(float x, float y,int width, int height, LPDIRECT3DTEXTURE9 texture, RECT* Rect);
	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath, D3DCOLOR TransColor);

	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	//int GetScreenWidth() { return screen_width; }
	//int GetScreenHeight() { return screen_height; }

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame * GetInstance();

	~CGame();
};


