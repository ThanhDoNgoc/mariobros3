#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->idX = x;
	this->idY = y;

	rect.left = x * CELL_WIDTH;
	rect.top = y * CELL_HEIGHT;
	rect.right = x * CELL_WIDTH + CELL_WIDTH;
	rect.bottom = y * CELL_HEIGHT + CELL_HEIGHT;
}

void Cell::AddObject(CGameObject* obj)
{
	if (!(objects.find(obj) != objects.end()))
	{
		objects.insert(obj);
	}
}

void Cell::DeleteObject(CGameObject* obj)
{
	if (objects.find(obj) != objects.end())
	{
		objects.erase(obj);
	}
}

std::unordered_set<CGameObject*> Cell::getCellObject()
{
	return this->objects;
}
