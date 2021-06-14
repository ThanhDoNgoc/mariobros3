#include "GhostPlatform.h"

GhostPlatform::GhostPlatform(int width, int height)
{
	this->platformWidth = width;
	this->platformHeight = height;

	this->ObjectGroup = Group::ground;
	this->collision = Collision2D::Top;
}

void GhostPlatform::Render()
{
	RenderBoundingBox();
}

void GhostPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + this->platformWidth;
	b = y + this->platformHeight;
}
