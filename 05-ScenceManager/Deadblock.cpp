#include "Deadblock.h"

Deadblock::Deadblock(int width, int height)
{
	this->dbWidth = width;
	this->dbHeight= height;

	this->ObjectGroup = Group::dead;
	this->collision = Collision2D::Full;
}

void Deadblock::Render()
{
	RenderBoundingBox();
}

void Deadblock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + dbWidth;
	b = y + dbHeight;
}
