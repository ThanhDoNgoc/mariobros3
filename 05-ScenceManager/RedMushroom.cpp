#include "RedMushroom.h"
#include "Camera.h"
#include "Game.h"
#include "Mario.h"
RedMushroom::RedMushroom()
{
	AddAnimation(ID_ANI_MUSHROOM_RED);

	this->ObjectGroup = Group::item;
	this->collision = Collision2D::None;
	this->isOut = false;
	this->setVx = false;
	this->velocity = 0;

}

void RedMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

			if (e->obj->ObjectGroup == Group::player)
			{
				this->TakeDamage();
			}
		}
		if (ny != 0) 
			vy = 0;

		if (nx != 0)
			direction.x = -direction.x; 

	}
	this->vx = this->velocity * direction.x;
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGameObject::Update(dt);
}

void RedMushroom::Render()
{
	int ani = ANI_ID_MUSHROOM;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + MUSHROOM_WIDTH / 2, y - camera->GetCamPosY() + MUSHROOM_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void RedMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MUSHROOM_WIDTH;
	b = y + MUSHROOM_HEIGHT;
}

void RedMushroom::TakeDamage()
{
	if (__Mario->level < 1)
	{
		__Mario->y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
		__Mario->_marioLevel = new MarioLevelBig();
	}
	CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}

void RedMushroom::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
		if (__Mario->level < 1)
		{
			__Mario->y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
			__Mario->_marioLevel = new MarioLevelBig();
		}
	}
	if (obj->ObjectGroup == Group::block)
	{
		this->y -= SPROUT_SPEED*dt;
		this->distance += abs(SPROUT_SPEED * dt);
	}
}
