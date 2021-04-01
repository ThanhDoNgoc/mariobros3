#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::AddTileSet(LPTILESET tileset)
{
	this->tileSets = tileset;
}

void Map::AddTileMap(LPTILEMAP tilemap)
{
	this->tileMaps.push_back(tilemap);
}

void Map::LoadMap(const char* filePath, const char* path)
{
	TiXmlDocument TMXdoc(filePath);

	if (TMXdoc.LoadFile())
	{
		TiXmlElement* root = TMXdoc.RootElement();

		root->QueryIntAttribute("width", &this->mapWidth);
		root->QueryIntAttribute("height", &this->mapHeight);
		root->QueryIntAttribute("tilewidth", &this->tileWidth);
		root->QueryIntAttribute("tileheight", &this->tileHeight);

		for (TiXmlElement* TMXtileset = root->FirstChildElement("tileset"); TMXtileset != NULL; TMXtileset = TMXtileset->NextSiblingElement("tileset"))
		{
			LPTILESET tileset = new TileSet(TMXtileset, path);
			this->AddTileSet(tileset);

			//DebugOut(L"[INFO] load success tileset: %", tileset->getFirstgid());
		}

		for (TiXmlElement* TMXlayer = root->FirstChildElement("layer"); TMXlayer != NULL; TMXlayer = TMXlayer->NextSiblingElement("layer"))
		{
			LPTILEMAP tilemap = new TileMap(TMXlayer);
			this->AddTileMap(tilemap);
		}

		DebugOut(L"[INFO] map load successful \n");
	}
	else
	{
		DebugOut(L"[ERROR] failed to load map \n");
	}
}

void Map::Render(Camera* camera)
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			int x = i * tileWidth;
			int y = j * tileHeight;
			for (LPTILEMAP tile : tileMaps)
			{
				int id = tile->GetMapData(i, j);
				if (id != 0)
				{
					tileSets->Draw(id, x, y);
				}
			}
		}
	}
	DebugOut(L"RENDER MAPP \n");

}
