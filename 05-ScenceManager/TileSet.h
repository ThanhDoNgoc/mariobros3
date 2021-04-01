#pragma once
#include <d3dx9.h>
#include "Utils.h"
#include "tinyXML/tinyxml/tinyxml.h"
#include "Game.h"

class TileSet
{
	int firstgid;
	int tileWidth;
	int tileHeight;
	int imageWidth;
	int imageHeight;
	LPDIRECT3DTEXTURE9 mapTexture;
	std::unordered_map<int, RECT*> cells;
public:
	TileSet();
	TileSet(TiXmlElement* TMXtileset, std::string Path);
	~TileSet();
	void SetTileWidth(int width);
	void SetTileHeight(int height);
	void SetMapTexture(LPDIRECT3DTEXTURE9 texture);

	int GetTileWidth();
	int GetTileHeight();
	LPDIRECT3DTEXTURE9 GetMapTexture();

	void Draw(int id, float x, float y);
	void ClearMapTexture();

};

typedef TileSet* LPTILESET;

