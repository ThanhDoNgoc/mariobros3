#include "Ground.h"
#include "Game.h"
#include "Camera.h"

Ground::Ground(int width, int height)
{
	this->groundWidth = width;
	this->groundHeight = height;

	this->ObjectGroup = Group::ground;
	this->collision = Collision2D::Full;
}

void Ground::Render()
{
	RenderBoundingBox();
}

void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + groundWidth;
	b = y + groundHeight;
}
