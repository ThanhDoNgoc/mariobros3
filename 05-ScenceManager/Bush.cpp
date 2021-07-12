#include "Bush.h"
#include "Camera.h"
#include "Game.h"
Bush::Bush()
{
	AddAnimation(ID_ANI_WORLDMAP_BUSH);
	this->ObjectGroup = Group::none;
	this->collision = Collision2D::None;
}

void Bush::Render()
{
	int ani = ANI_BUSH;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY());
}

void Bush::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + BUSH_WIDTH;
	bottom = right + BUSH_HEIGHT;
}
