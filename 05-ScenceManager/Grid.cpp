#include "Grid.h"
#include "Game.h"
#include "Utils.h"
#include "Camera.h"
Grid::Grid(int mapWidth, int mapHeigth)
{
	this->maxCellX = mapWidth / CELL_WIDTH;
	this->maxCellY = mapHeigth / CELL_HEIGHT;

	for (int y = 0; y <= maxCellY; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x <= maxCellX; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		cells.push_back(row);
	}

	this->camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
}

void Grid::Update()
{
	GetActiveCell();
	UpdateGridObject();
}

void Grid::AddObject(CGameObject* obj)
{
	Cell* cell = getCellByObjectPosition(obj->GetPositionX(), obj->GetPositionY());
	cell->AddObject(obj);
	obj->setOwnerCell(cell);
}

void Grid::AddObject(CGameObject* obj, int cellX, int cellY)
{
	Cell* cell = this->cells[cellY][cellX];
	cell->AddObject(obj);
	obj->setOwnerCell(cell);

}

void Grid::DeleteObject(CGameObject* obj)
{
	Cell* cell = getCellByObjectPosition(obj->GetPositionX(), obj->GetPositionY());
	cell->DeleteObject(obj);
}

Cell* Grid::getCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= maxCellX)
		x = maxCellX;

	if (y < 0) y = 0;
	if (y >= maxCellY)
		y = maxCellY;

	return cells[y][x];
}

Cell* Grid::getCellByObjectPosition(float x, float y)
{
	int cellX =(int) x / CELL_WIDTH;
	int cellY = (int) y / CELL_HEIGHT;
	return getCell(cellX, cellY);
}

std::vector<CGameObject*> Grid::getActiveGameObject()
{
	//return std::vector<CGameObject*>();

	std::unordered_set<CGameObject*> coObject;
	for (size_t i = 0; i < activeCells.size(); i++)
	{
		auto x = activeCells[i]->getCellObject();

		auto o = x.begin();
		while (o!=x.end())
		{
			coObject.insert(*o);
			o++;
		}
	}

	std::vector<CGameObject*> returned;
	returned.insert(returned.end(), coObject.begin(), coObject.end());
	return returned;
}

void Grid::GetActiveCell()
{
	activeCells.clear();
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	int startX = camera->GetCamPosX() / CELL_WIDTH;
	int endX = ((camera->GetCamPosX() + SCREEN_WIDTH) / CELL_WIDTH)+1;
	int startY = camera->GetCamPosY() / CELL_HEIGHT;
	int endY = ((camera->GetCamPosY() + SCREEN_HEIGHT) / CELL_HEIGHT)+1;

	int campos = camera->GetCamPosY();
	int camposx = camera->GetCamPosX();

	for (int i = startX; i <= endX; ++i)
	{
		if (i<0 || i>=maxCellX) 
			continue;
		for (int j = startY; j <= endY; ++j)
		{
			if (j<0 || j>maxCellY) 
				continue;
			activeCells.push_back(cells[j][i]);
		}
	}
}

void Grid::UpdateActiveCell()
{
}

void Grid::UpdateGridObject()
{
	std::vector<LPGAMEOBJECT> gridObjects = getActiveGameObject();
	auto o = gridObjects.begin();
	while (o != gridObjects.end())
	{
		UpdateGridObjectpos(*o);
		++o;
	}
}

void Grid::UpdateGridObjectpos(CGameObject* obj)
{
	Cell* newCell = getCellByObjectPosition(obj->GetPositionX(), obj->GetPositionY());
	if (newCell != obj->getOwerCell())
	{
		obj->getOwerCell()->DeleteObject(obj);
		newCell->AddObject(obj);
		obj->setOwnerCell(newCell);
	}
}

void Grid::LoadGridFromFile(std::vector<CGameObject*> objects, std::string gridfilepath)
{
	TiXmlDocument doc(gridfilepath.c_str());
	if (!doc.LoadFile())
	{
		printf("%s", doc.ErrorDesc());
	}
	else
	{
		TiXmlElement* root = doc.RootElement();

		for (TiXmlElement* group = root->FirstChildElement("group"); group != NULL; group = group->NextSiblingElement("group"))
		{
			for (TiXmlElement* object = group->FirstChildElement("object"); object != NULL; object = object->NextSiblingElement("object"))
			{
				int id, cellx, celly, spanx, spany;

				object->QueryIntAttribute("id", &id);
				object->QueryIntAttribute("cellx", &cellx);
				object->QueryIntAttribute("celly", &celly);
				object->QueryIntAttribute("spanx", &spanx);
				object->QueryIntAttribute("spany", &spany);

				CGameObject* obj = NULL;
				for (size_t  i = 0; i < objects.size(); i++)
				{
					int u = objects[i]->getId();
					if (objects[i]->getId() == id)
					{
						obj = objects[i];

						for (int m = 0; m < spany; m++)
						{
							for (int n = 0; n < spanx; n++)
							{
								this->AddObject(obj, cellx + n, celly + m);
							}
						}

						continue;
					}
				}


			}
		}

		DebugOut(L"[INFO] Read file complete");
	}
}
