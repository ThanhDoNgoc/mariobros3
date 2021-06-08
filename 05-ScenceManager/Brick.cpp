#include "Brick.h"
#include "Game.h"
#include "Camera.h"

CBrick::CBrick()
{
	ObjectGroup = Group::block;
}

void CBrick::Render()
{
	//Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	//animation_set->at(0)->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY());
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}