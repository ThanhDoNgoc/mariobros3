#include "BreakBrick.h"
#include "Camera.h"
#include "Game.h"
BreakBrick::BreakBrick(float x, float y, bool ishigh, bool isDirecRight)
{
	AddAnimation(ID_ANI_BREAK_BRICK);
	this->x = x;
	this->y = y;
	if (ishigh)
		this->vy = -BREAK_SPEED_Y_H;
	else if (!ishigh) 
		this->vy = -BREAK_SPEED_Y_L;

	if (isDirecRight)
	{
		this->direction.x = 1.0f;
		this->vx = BREAK_SPEED_X;
	}
	else if (!isDirecRight)
	{
		this->direction.x = -1.0f;
		this->vx = -BREAK_SPEED_X;
	}
	this->objectLayer = LAYER_PIPE;
	this->ObjectGroup = Group::effect;
}

void BreakBrick::Render()
{
	int ani = ANI_ID_BREAK;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + BREAK_WIDTH / 2, y - camera->GetCamPosY() + BREAK_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void BreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//this->x += vx * dt;
	x += dx;
	y += dy;
	this->vy += BREAK_GRAVITY * dt;
	//this->y += vy * dt;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	if (this->y > camera->GetCamPosY() + CAMERA_HEIGHT)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
	}
}
