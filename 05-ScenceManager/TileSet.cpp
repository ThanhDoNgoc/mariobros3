#include "TileSet.h"

TileSet::TileSet()
{
}

TileSet::TileSet(TiXmlElement* TMXtileset, std::string Path)
{
	TMXtileset->QueryIntAttribute("firstgrid", &this->firstgid);
	TMXtileset->QueryIntAttribute("tilewidth", &this->tileWidth);
	TMXtileset->QueryIntAttribute("tileheight", &this->tileHeight);


	TiXmlElement* TMXimage = TMXtileset->FirstChildElement("image");
	std::string imagepath = Path + TMXimage->Attribute("source");
	TMXimage->QueryIntAttribute("width", &this->imageWidth);
	TMXimage->QueryIntAttribute("height", &this->imageHeight);

	this->mapTexture = CGame::GetInstance()->LoadTexture(ToLPCWSTR(imagepath), NULL);
	int index = 1;
	for (int i = 0; i < imageHeight / tileHeight; i++)
	{
		for (int j = 0; j < imageWidth / tileWidth; j++, index++)
		{
			RECT* rect = new RECT();

			rect->left = j * tileWidth;
			rect->top = i * tileHeight;
			rect->right = rect->left + tileWidth;
			rect->bottom = rect->top + tileHeight;

			this->cells[index] = rect;

			DebugOut(L"rect %d: %d %d %d %d \n",index, rect->left, rect->top, rect->right, rect->bottom);
		}
	}
}

TileSet::~TileSet()
{
}

void TileSet::SetTileWidth(int width)
{
	this->tileWidth = width;
}

void TileSet::SetTileHeight(int height)
{
	this->tileHeight = height;
}

void TileSet::SetMapTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->mapTexture = texture;
}

int TileSet::GetTileWidth()
{
	return tileWidth;
}

int TileSet::GetTileHeight()
{
	return tileHeight;
}

LPDIRECT3DTEXTURE9 TileSet::GetMapTexture()
{
	return this->mapTexture;
}

void TileSet::Draw(int id, float x, float y)
{
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	CGame::GetInstance()->DrawTileMap(x - camera->GetCamPosX(), y - camera->GetCamPosY(),tileWidth, tileHeight, mapTexture, cells[id]);
}


void TileSet::ClearMapTexture()
{
	this->mapTexture->Release();
}
