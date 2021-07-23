#include "GoombaPoop.h"
#include "Camera.h"
#include "Game.h"
#include "Mario.h"
GoombaPoop::GoombaPoop()
{
	AddAnimation(ID_ANI_GOOMBA_POOP);
	this->ObjectGroup = Group::poop;
	this->collision = Collision2D::None;
	this->vy = POOP_FALL_SPEED;
	this->cycleTime = GetTickCount64();
	this->vx = POOP_FALL_SPEEDX;
	this->isDead = false;
	this->isOnMario = false;
	this->movingX = 0;
	this->movingY = 0;
}

void GoombaPoop::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + POOP_BBOX_WIDTH;
	bottom = top + POOP_BBOX_HEIGHT;
}

void GoombaPoop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (!isOnMario)
	{
		this->x += dx * direction.x;
		this->y += dy * direction.y;
		if (GetTickCount64() - cycleTime > POOP_CYCLE_TIME)
		{
			direction.x = -direction.x;
			cycleTime = GetTickCount64();
		}
	}
	else if (isOnMario && !isDead)
	{
		this->movingX += dx * direction.x;
		if (this->movingX < -POOP_BBOX_WIDTH)
			direction.x = 1.0f;
		else if (this->movingX > __Mario->width)
			direction.x = -1.0f;

		this->movingY += vy*dt;
		if (this->movingY < 0)
			vy = POOP_ON_MARIO_SPEED;
		else if (this->movingY > __Mario->height - POOP_BBOX_HEIGHT)
			vy = -POOP_ON_MARIO_SPEED;

		this->y = __Mario->y + this->movingY;
		this->x = __Mario->x + this->movingX;
	}
	else 
	{
		this->x += dx * direction.x;
		this->y += dy * direction.y;
	}
	vector<LPCOLLISIONEVENT> coEvents;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
}

void GoombaPoop::Render()
{
	int ani = ANI_ID_GOOMBA_POOP;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	if (isOnMario && !isDead)
	{
		if (this->direction.x == -1.0f)
			this->objectLayer = LAYER_ITEM;
		else this->objectLayer = LAYER_PIPE;
	}
	animation_set[ani]->Render(x - camera->GetCamPosX() + POOP_BBOX_WIDTH / 2, y - camera->GetCamPosY() + POOP_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void GoombaPoop::TakeDamage()
{
	this->isDead = true;
	this->direction.y = -1;
	this->vy = -POOP_DIE_FALL_SPEED;
	//CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}

void GoombaPoop::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		if (isDead) return;
		if (!isOnMario)
		{
			this->isOnMario = true;
			this->x = __Mario->x;
		}
	}
	else if (obj->ObjectGroup == Group::dead)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
	}
}
