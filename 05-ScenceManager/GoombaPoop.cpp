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
	this->cycleTime = GetTickCount();
	this->vx = POOP_FALL_SPEEDX;
	this->isDead = false;
	this->isOnMario = false;
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
	this->x += dx * direction.x;
	this->y += dy * direction.y;

	if (!isOnMario)
	{
		if (GetTickCount() - cycleTime > POOP_CYCLE_TIME)
		{
			direction.x = -direction.x;
			cycleTime = GetTickCount();
		}
	}
	else if (isOnMario && !isDead)
	{
		this->y = __Mario->y + __Mario->height - POOP_BBOX_HEIGHT;
		this->x = __Mario->x + __Mario->width/2 - POOP_BBOX_WIDTH/2;
	}
	vector<LPCOLLISIONEVENT> coEvents;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
}

void GoombaPoop::Render()
{
	int ani = ANI_ID_GOOMBA_POOP;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + POOP_BBOX_WIDTH / 2, y - camera->GetCamPosY() + POOP_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void GoombaPoop::TakeDamage()
{
	this->isDead = true;
	this->direction.y = -1;
	this->vy = -POOP_DIE_FALL_SPEED;
}

void GoombaPoop::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
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
