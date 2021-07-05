#include "Map.h"
#include "Ground.h"
#include "GhostPlatform.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Brick.h"
#include "QuestionBlock.h"
#include "Coin.h"
#include "Deadblock.h"
#include "RedFireShootingPlant.h"
#include "GreenFireShootingPlant.h"
#include "GreenEatingPlant.h"
#include "Warp.h"
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
			else if (name == "deadblock")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);
				Deadblock* deadblock = new Deadblock(width, height);
				deadblock->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(deadblock);
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
			else if (name == "redfiretree")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				RedFireShootingPlant* obj = new RedFireShootingPlant();
				obj->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(obj);
			}
			/*else if (name == "greenfiretree")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				GreenFireShootingPlant* greenshoot = new GreenFireShootingPlant();
				greenshoot->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(greenshoot);
			}*/
			else if (name == "greeneating")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				GreenEatingPlant* obj = new GreenEatingPlant();
				obj->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(obj);
				DebugOut(L"[INFO] greeneating \n");
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
			else if (name == "qblock")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				QuestionBlock* qblock = new QuestionBlock();
				qblock->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(qblock);
				qblock->SetItem(TMXObject->Attribute("type"));
			}
			else if (name == "coin")
			{
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				Coin* coin = new Coin();
				coin->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddObject(coin);
			}
			else if (name == "wrap")
			{
			TMXObject->QueryFloatAttribute("x", &x);
			TMXObject->QueryFloatAttribute("y", &y);
			Warp* warp = new Warp();
			warp->SetPosition(x, y);
			CGame::GetInstance()->GetCurrentScene()->AddObject(warp);
			std::string dir;
			dir = TMXObject->Attribute("type");

			if (dir == "up")
			{
				warp->setWarpDirection(WarpDirection::up);
			}
			else if (dir == "down")
			{
				warp->setWarpDirection(WarpDirection::down);
			}
			float toposX, toposY;
			TMXObject->QueryFloatAttribute("toX", &toposX);
			TMXObject->QueryFloatAttribute("toY", &toposY);
			warp->toX = toposX;
			warp->toY = toposY;
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
