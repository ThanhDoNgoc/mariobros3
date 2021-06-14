#include "Map.h"
#include "Ground.h"
#include "GhostPlatform.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Brick.h"
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

		this->AddObject(root);

		DebugOut(L"[INFO] map load successful \n");
	}
	else
	{
		DebugOut(L"[ERROR] failed to load map \n");
	}
}


void Map::AddObject(TiXmlElement* RootElement)
{
	for (TiXmlElement* TMXObjectsgroup = RootElement->FirstChildElement("objectgroup"); TMXObjectsgroup != NULL; TMXObjectsgroup = TMXObjectsgroup->NextSiblingElement("objectgroup"))
	{
		for (TiXmlElement* TMXObject = TMXObjectsgroup->FirstChildElement("object"); TMXObject != NULL; TMXObject = TMXObject->NextSiblingElement("object"))
		{
			int id;
			float x, y, width, height;
			std::string name = TMXObject->Attribute("name");
			if (name == "ground")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);
				Ground* ground = new Ground(width, height);
				ground->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(ground);
				//DebugOut(L"[INFO] map object ground \n");

			}
			else if (name == "ghostplatform")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);
				GhostPlatform* ghost = new GhostPlatform(width, height);
				ghost->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(ghost);
				//DebugOut(L"[INFO] map object ghostplatform \n");
			}
			else if (name == "goomba")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				CGoomba* goomba = new CGoomba();
				goomba->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(goomba);
			}
			else if (name == "koopa")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				CKoopas* koopa = new CKoopas();
				koopa->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(koopa);
			}
			else if (name == "brick")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				CBrick* brick = new CBrick();
				brick->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(brick);
			}
		}
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
	//DebugOut(L"[INFO] RENDER MAPP \n");

}
