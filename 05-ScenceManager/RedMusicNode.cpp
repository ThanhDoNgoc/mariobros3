#include "RedMusicNode.h"
#include "Game.h"
#include "Camera.h"
RedMusicNode::RedMusicNode()
{
	AddAnimation(ID_ANI_HIDDEN_NOTE);
	ObjectGroup = Group::hiddenmusicblock;
	collision = Collision2D::Bottom;
	this->vy = 0;
	this->vx = 0;
	this->boundUp = this->boundDown = false;
	this->isVisibility = false;
}

void RedMusicNode::Render()
{
	if (!isVisibility) return;
	int ani = ANI_MUSIC_BLOCK;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + MUSIC_BBOX_WIDTH / 2, y - camera->GetCamPosY() + MUSIC_BBOX_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void RedMusicNode::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MUSIC_BBOX_WIDTH;
	b = y + MUSIC_BBOX_HEIGHT;
}

void RedMusicNode::TakeDamage()
{
	this->y -= MUSIC_BOUND_POSITION;
	this->vy = +MUSIC_VELOCITY;
	this->boundUp = true;
	if (!isVisibility)
	{
		isVisibility = true;
		collision = Collision2D::Full;
	}
}

void RedMusicNode::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (this->boundDown == true)
	{
		if (this->y < this->startY)
		{
			this->y = this->startY;
			this->vy = 0;
			this->boundDown = false;
		}

	}
	else if (this->boundUp == true)
	{
		if (this->y > this->startY)
		{
			this->y = this->startY;
			this->vy = 0;
			this->boundUp = false;
		}
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->ObjectGroup == Group::player)
			{
				if (ny > 0)
				{
					if (boundDown == false)
					{
						this->y += MUSIC_BOUND_POSITION;
						this->vy = -MUSIC_VELOCITY;
						this->boundDown = true;
					}
				}
			}
		}
	}
	this->y += vy * dt;
	DebugOut(L" velocity y: %f \n ", vy);
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void RedMusicNode::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::marioprojectile || obj->ObjectGroup == Group::projectile)
	{
		if (isVisibility)
			this->TakeDamage();
	}
}
