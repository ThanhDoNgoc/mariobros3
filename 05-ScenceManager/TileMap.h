#pragma once
#include "Utils.h"
#include "tinyXML/tinyxml/tinyxml.h"

class TileMap
{
	int id;
	int mapWidth;
	int mapHeight;
	int** map;

public:
	TileMap();
	TileMap(TiXmlElement* TMLTileMap);
	~TileMap();

	void SetMapWidth(int width);
	void SetMapHeight(int height);

	int GetMapWidth();
	int GetMapHeight();
	int GetMapData(int x, int y);

};
typedef TileMap* LPTILEMAP;


