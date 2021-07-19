#include "Boomerang.h"
#include "Camera.h"
#include "Game.h"
Boomerang::Boomerang(float posX, float posY, float direcX)
{
	AddAnimation(ID_ANI_BOOMERANG_FLY);
	this->canFlyBack = true;
	this->x = posX;
	this->y = posY;
	this->startX = posX;
	this->startY = posY;
	this->collision = Collision2D::None;
	this->ObjectGroup = Group::projectile2;
	this->direction.x = direcX;
	this->vx = BOOMERANG_FLY_SPEED;
	this->vy = -BOOMERANG_FLY_SPEED_Y;
}

void Boomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + BOOMERANG_BBOX_WIDTH;
	bottom = top + BOOMERANG_BBOX_HEIGHT;
}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	if (camera->GetCamPosX() + CAMERA_WIDTH < this->x || camera->GetCamPosX() > this->x + BOOMERANG_BBOX_WIDTH)
	{
		if (!canFlyBack)
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
	}

	this->x += dx * direction.x;
	this->y += dy * direction.y;
	if (abs (this->x-this->startX) > BOOMERANG_DISTANCE_X )
	{
		if (canFlyBack)
		{
			canFlyBack = false;
			this->direction.x = -direction.x;
		}
	}
	if (abs(this->x - this->startX) > BOOMERANG_DISTANCE_X - 48)
	{
		this->vy = BOOMERANG_FLY_SPEED_Y;
	}
	if (this->y < this->startY - 72)
	{
		this->y = this->startY - 72;
		this->vy = 0;
	}
	else if (this->y > this->startY + 48)
	{
		this->y = this->startY + 48;
		this->vy = 0;
	}
}

void Boomerang::Render()
{
	int ani = ANI_ID_BOOMERANG_FLY;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + BOOMERANG_BBOX_WIDTH / 2, y - camera->GetCamPosY() + BOOMERANG_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void Boomerang::TakeDamage()
{
	CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}
