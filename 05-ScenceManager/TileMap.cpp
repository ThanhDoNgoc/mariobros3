#include "TileMap.h"
#include <string.h>
 
TileMap::TileMap()
{
	this->mapWidth = 16;
	this->mapHeight = 16;
}

TileMap::~TileMap()
{
}

TileMap::TileMap(TiXmlElement* TMLTileMap)
{
	TMLTileMap->QueryIntAttribute("id", &this->id);
	TMLTileMap->QueryIntAttribute("width", &this->mapWidth);
	TMLTileMap->QueryIntAttribute("height", &this->mapHeight);

	std::string cells = TMLTileMap->FirstChildElement()->GetText();
	std::vector<std::string> tile = split(cells, ",");

	map = new int* [this->mapWidth];
	for (int i = 0; i < this->mapWidth; i++)
	{
		map[i] = new int[this->mapHeight];
		for (int j = 0; j < this->mapHeight; j++)
		{
			map[i][j] = stoi(tile[i + j * mapWidth]);
		}
	}
}


void TileMap::SetMapWidth(int width)
{
	this->mapWidth = width;
}

void TileMap::SetMapHeight(int height)
{
	this->mapHeight = height;
}


int TileMap::GetMapWidth()
{
	return this->mapWidth;
}

int TileMap::GetMapHeight()
{
	return this->mapHeight;
}

int TileMap::GetMapData(int x, int y)
{
	return this->map[x][y];
}
