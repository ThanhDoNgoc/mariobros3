#pragma once
#include "GameObject.h"
#include <unordered_set>

#define CELL_WIDTH	384
#define CELL_HEIGHT	360

class CGameObject;

class Cell
{
	int idX, idY;
	std::unordered_set<CGameObject* > objects;
	RECT rect;
public:
	Cell(int x, int y);

	void AddObject(CGameObject* obj);
	void DeleteObject(CGameObject* obj);

	std::unordered_set<CGameObject*> getCellObject();
};

