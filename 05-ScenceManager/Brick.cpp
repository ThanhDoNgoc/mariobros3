#include "Brick.h"
#include "Game.h"
#include "Camera.h"

CBrick::CBrick()
{
	AddAnimation(ID_ANI_BRICK);
	ObjectGroup = Group::block;
	collision = Collision2D::Full;
}

void CBrick::Render()
{
	int ani = ANI_BRICK;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + BRICK_BBOX_WIDTH / 2, y - camera->GetCamPosY() + BRICK_BBOX_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}