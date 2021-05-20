#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, float cx, float cy, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->centerX = cx;
	this->centerY = cy;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, D3DXVECTOR2 direction, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x , y , centerX, centerY, texture, left, top, right, bottom, direction, alpha);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, float cx, float cy, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, cx, cy, tex);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d, %f, %f \n", id, left, top, right, bottom, cx , cy);
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



