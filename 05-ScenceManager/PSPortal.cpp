#include "PSPortal.h"


PSPortal::PSPortal(int psWidth, int psHeight)
{
	this->width = psWidth;
	this->height = psHeight;
	this->collision = Collision2D::None;
	this->ObjectGroup = Group::portal;
}

void PSPortal::Render()
{
	RenderBoundingBox();
}

void PSPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void PSPortal::setcam(float l, float t, float r, float b)
{
	this->camL = l;
	this->camT = t;
	this->camR = r;
	this->camB = b;
}

void PSPortal::setpos(float x, float y)
{
	this->posX = x;
	this->posY = y;
}
