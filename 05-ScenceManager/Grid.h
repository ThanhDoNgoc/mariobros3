#pragma once
#include <vector>
#include "Cell.h"
#include "GlobalVariables.h"
#include "Camera.h"
#include "GameObject.h"

#include "tinyXML/tinyxml/tinyxml.h"

class Grid
{
	Camera* camera;
	int maxCellX, maxCellY;

	std::vector <std::vector<Cell*>> cells;
	std::vector<Cell*> activeCells;

public:
	Grid(int mapWidth, int mapHeigth);
	void Update();

	void AddObject(CGameObject* obj);
	void AddObject(CGameObject* obj, int cellX, int cellY);
	void DeleteObject(CGameObject* obj);
	
	Cell* getCell(int x, int y);
	Cell* getCellByObjectPosition(float x, float y);

	std::vector<CGameObject*> getActiveGameObject();

	void GetActiveCell();
	void UpdateActiveCell();

	void UpdateGridObject();
	void UpdateGridObjectpos(CGameObject* obj);

	void LoadGridFromFile(std::vector<CGameObject*> objects, std::string gridfilepath);
};

