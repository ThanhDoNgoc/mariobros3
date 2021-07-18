#include "GreenMushroom.h"
#include "GlobalVariables.h"
#include "Game.h"
GreenMushroom::GreenMushroom()
{
	AddAnimation(ID_ANI_MUSHROOM_GREEN);
	this->ObjectGroup = Group::item;
	this->collision = Collision2D::None;
	this->isOut = false;
	this->setVx = false;
	this->velocity = 0;
	this->objectLayer = 0;
}

void GreenMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	if (this->distance >= MUSHROOM_HEIGHT)
		this->isOut = true;

	if (isOut)
	{
		if (!setVx)
		{
			//vx = MUSHROOM_SPEED * direction.x;
			this->velocity = MUSHROOM_SPEED;
			this->setVx = true;
		}
		vy += MUSHROOM_GRAVITY * dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		this->x += dx;
		this->y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		this->x += min_tx * dx + nx * 0.4f;
		this->y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->ObjectGroup == Group::ground || e->obj->ObjectGroup == Group::block)
			{
				if (nx!=0)
					direction.x = -direction.x;
				if (ny != 0)
					vy = 0;
			}
			
		}

	}
	this->vx = this->velocity * direction.x;
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGameObject::Update(dt);
}

void GreenMushroom::Render()
{
	int ani = ANI_ID_MUSHROOM;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + MUSHROOM_WIDTH / 2, y - camera->GetCamPosY() + MUSHROOM_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void GreenMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MUSHROOM_WIDTH;
	b = y + MUSHROOM_HEIGHT;
}

void GreenMushroom::TakeDamage()
{
	GlobalVariables::GetInstance()->AddLife();
	CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}

void GreenMushroom::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		GlobalVariables::GetInstance()->AddLife();
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
	}
	if (obj->ObjectGroup == Group::block)
	{
		this->y -= SPROUT_SPEED * dt;
		this->distance += abs(SPROUT_SPEED * dt);
	}
}
