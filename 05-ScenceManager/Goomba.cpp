#include "Goomba.h"
#include "Game.h"
#include "Camera.h"

CGoomba::CGoomba()
{
	AddAnimation(ID_ANI_GOOMBA_WALK);
	AddAnimation(ID_ANI_GOOMBA_DIE);
	SetState(GOOMBA_STATE_WALKING);
	this->width = GOOMBA_BBOX_WIDTH;
	this->height = GOOMBA_BBOX_HEIGHT;
	this->direction.x = -1.0f;
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGame* game = CGame::GetInstance();

	vy += GOOMBA_GRAVITY * dt;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != GOOMBA_STATE_INSTANCE_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0)
		{
			vy = 0;
		}
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				this->direction.x * -1;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	switch (state)
	{
	case GOOMBA_STATE_WALKING:
		ani = GOOMBA_ANI_WALKING;
		break;
	case GOOMBA_STATE_DIE:
		ani = GOOMBA_ANI_DIE;
		break;
	case GOOMBA_STATE_INSTANCE_DEAD:
		ani = GOOMBA_ANI_WALKING;
		this->direction.y = -1.0;
		break;
	}
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + GOOMBA_BBOX_WIDTH/2, y - camera->GetCamPosY() + GOOMBA_BBOX_HEIGHT/2, direction, 255);

	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_INSTANCE_DEAD:
			vx = -GOOMBA_WALKING_SPEED;
			vy = -GOOMBA_INSTANCE_DEAD_VY;
			break;
	}
}

void CGoomba::TakeDamage()
{
	this->SetState(GOOMBA_STATE_DIE);
}

void CGoomba::InstanceDead()
{
	this->SetState(GOOMBA_STATE_INSTANCE_DEAD);
	this->width = 0;
	this->height = 0;
}
