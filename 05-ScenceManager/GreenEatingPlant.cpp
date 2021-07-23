#include "GreenEatingPlant.h"
#include "Game.h"
#include "Camera.h"
GreenEatingPlant::GreenEatingPlant()
{
	AddAnimation(ID_ANI_GREEN_EATING_PLANT);
	this->ObjectGroup = Group::projectile;
	this->collision = Collision2D::Full;
}

void GreenEatingPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GREENEATING_WIDTH;
	bottom = y + GREENEATING_HEIGHT;
}

void GreenEatingPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);
	this->x += dx;
	this->y += dy;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->ObjectGroup == Group::projectile|| e->obj->ObjectGroup == Group::marioprojectile)
			{
				this->TakeDamage();
			}
		}
	}

	switch (this->state)
	{
	case GreeneatingState::idledown:
	{
		this->vy = 0;
		distance = 0;
		if (GetTickCount() - hideTime_start > GREENEATING_HIDE)
		{
			state = GreeneatingState::slideup;
		}

		break;
	}
	case GreeneatingState::slideup:
	{
		this->vy = -GREENEATING_SPEED;
		if (abs(this->y - this->startY) > GREENEATING_HEIGHT)
		{
			this->y = this->startY - GREENEATING_HEIGHT;
			this->waitTime_start = GetTickCount();
			state = GreeneatingState::idleup;
		}
		break;
	}
	case GreeneatingState::idleup:
	{
		this->vy = 0;
		if (GetTickCount() - waitTime_start > GREENEATING_WAIT)
		{
			distance = 0;
			state = GreeneatingState::slidedown;
		}
		break;
	}
	case GreeneatingState::slidedown:
	{
		this->vy = +GREENEATING_SPEED;
		if (this->y > this->startY)
		{
			this->y = this->startY;
			this->hideTime_start = GetTickCount();
			state = GreeneatingState::idledown;
		}
		break;
	}
	}
}

void GreenEatingPlant::Render()
{
	int ani = 0;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + GREENEATING_WIDTH / 2, y - camera->GetCamPosY() + GREENEATING_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void GreenEatingPlant::TakeDamage()
{
	CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}

void GreenEatingPlant::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::marioprojectile)
		this->TakeDamage();
}
