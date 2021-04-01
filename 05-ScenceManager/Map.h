#pragma once
#include <vector>
#include <d3dx9.h>
#include <string>

#include "Utils.h"
#include "TileSet.h"
#include "TileMap.h"
#include "tinyXML/tinyxml/tinyxml.h"
#include "Camera.h"


class Map
{
	int tileWidth;
	int tileHeight;

	int mapWidth;
	int mapHeight;

	LPTILESET tileSets;
	std::vector<LPTILEMAP> tileMaps;
public:
	Map();
	~Map();

	void AddTileSet(LPTILESET tileset);
	void AddTileMap(LPTILEMAP tilemap);

	void LoadMap(const char* filePath, const char* path);

};

