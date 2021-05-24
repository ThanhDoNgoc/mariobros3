#include "Koopas.h"
#include "Game.h"
#include "Camera.h"
#include "Goomba.h"
#include "Mario.h"

CKoopas::CKoopas()
{
	AddAnimation(ID_ANI_KOOPAS_WALK);
	AddAnimation(ID_ANI_KOOPAS_SHELL);
	AddAnimation(ID_ANI_KOOPAS_SHELL_MOVING);
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	CGame* game = CGame::GetInstance();
	
	if (state == KOOPAS_STATE_BEING_HOLD)
	{
		this->x = __Mario->x + (__Mario->_marioLevel->width * __Mario->direction.x);
		this->y = __Mario->y - __Mario->_marioLevel->height / 2;
		return;
	}

	this->vy += KOOPAS_GRAVITY * dt;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != KOOPAS_STATE_DIE && state != KOOPAS_STATE_BEING_HOLD)
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

			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (this->state == KOOPAS_STATE_SHELL_MOVING)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
						goomba->InstanceDead();
				}					
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING;
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		ani = KOOPAS_ANI_WALKING;
		break;
	case KOOPAS_STATE_SHELL:
		ani = KOOPAS_ANI_SHELL;
		break;
	case KOOPAS_STATE_SHELL_MOVING:
		ani = KOOPAS_ANI_SHELLMOVING;
		break;
	case KOOPAS_STATE_BEING_HOLD:
		ani = KOOPAS_ANI_SHELL;
		break;
	}
	if (vx > 0) this->direction.x = -1.0f;
	else if (vx <= 0) this->direction.x = 1.0f;

	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + KOOPAS_BBOX_WIDTH / 2, y - camera->GetCamPosY() + KOOPAS_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		this->vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SHELL:
		this->vx = 0;
		break;
	case KOOPAS_STATE_SHELL_MOVING:
		this->vx = KOOPAS_SHELL_MOVING_SPEED;
		break;
	case KOOPAS_STATE_BEING_HOLD:
		this->vx = 0;
		this->vy = 0;
		break;
	}

}

void CKoopas::TakeDamage()
{
	if (state == KOOPAS_STATE_WALKING)
		SetState(KOOPAS_STATE_SHELL);
}

void CKoopas::InstanceDead()
{
	SetState(KOOPAS_STATE_DIE);
	this->direction.y = -1;
	vy = -KOOPAS_INSTANCE_DEAD_VY;
}

void CKoopas::BeingHold()
{
	SetState(KOOPAS_STATE_BEING_HOLD);
}
