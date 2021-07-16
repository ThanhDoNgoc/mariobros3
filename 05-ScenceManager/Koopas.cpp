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
	this->SetState(KoopaState::walk);

	this->ObjectGroup = Group::enemy;
	this->collision = Collision2D::Full;

	isBeingHold = false;
	//this->direction.x *= -1.0f;
	this->startShellTime = 0;
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (koopaState == KoopaState::die) return;

	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	if (koopaState==KoopaState::walk)
		bottom = y + KOOPAS_BBOX_HEIGHT;
	else bottom = y + KOOPAS_SHELL_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	CGame* game = CGame::GetInstance();
	
	if (isBeingHold)
	{
		if (__Mario->direction.x<0)
			this->x = __Mario->x - __Mario->width;
		else this->x = __Mario->x + __Mario->width-3;
		if (__Mario->level == MARIO_LEVEL_SMALL)
			this->y = __Mario->y - __Mario->height / 2;
		else this->y = __Mario->y + __Mario->height / 4 ;
		return;
	}
	CGameObject::Update(dt);

	this->vy += KOOPAS_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (koopaState!=KoopaState::die)
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
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->ObjectGroup == Group::ground || e->obj->ObjectGroup == Group::enemy || e->obj->ObjectGroup == Group::block|| e->obj->ObjectGroup == Group::musicblock)
			{
				if (e->nx != 0)
				{
					if (koopaState == KoopaState::slide)
					{
						if (e->obj->ObjectGroup == Group::block || e->obj->ObjectGroup == Group::musicblock)
						{
							e->obj->TakeDamage();
						}
						if (e->obj->ObjectGroup == Group::enemy)
							nx = 0;
					}
				}
			}
			if (e->obj->ObjectGroup == Group::marioprojectile || e->obj->ObjectGroup == Group::projectile)
			{
				this->InstanceDead();
				//e->obj->TakeDamage();
			}
			else if (e->obj->ObjectGroup == Group::dead) 
			{
				CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
				GlobalVariables::GetInstance()->AddScore(100);
			}
		}
		if (nx != 0)
		{
			this->direction.x = -this->direction.x;
			DebugOut(L" change direc x: \n ");
		}
		if (ny != 0)
		{
			this->vy = 0;
		}
	}
	this->vx = this->velocity * this->direction.x;
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING;
	switch (koopaState)
	{
	case KoopaState::walk:
		ani = KOOPAS_ANI_WALKING;
		break;
	case KoopaState::shell:
		ani = KOOPAS_ANI_SHELL;
		break;
	case KoopaState::slide:
		ani = KOOPAS_ANI_SHELLMOVING;
		break;
	}
	D3DXVECTOR2 renderdirec = direction;
	renderdirec.x = -direction.x;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + KOOPAS_BBOX_WIDTH / 2, y - camera->GetCamPosY() + KOOPAS_BBOX_HEIGHT / 2, renderdirec, 255);

	RenderBoundingBox();

}

void CKoopas::SetState(KoopaState state)
{
	//CGameObject::SetState(state);
	this->koopaState = state;
	switch (koopaState)
	{
	case KoopaState::walk:
		this->velocity = KOOPAS_WALKING_SPEED;
		this->ObjectGroup = Group::enemy;
		break;
	case KoopaState::shell:
		this->velocity = 0;
		this->ObjectGroup = Group::shell;
		this->y -= 0.4;
		break;
	case KoopaState::slide:
		this->velocity = KOOPAS_SHELL_MOVING_SPEED;
		this->ObjectGroup = Group::projectile;
		this->y -= 0.4;
		break;
	case KoopaState::die:
		break;
	}
	DebugOut(L" velocity x: %f \n ", this->vx);
}

void CKoopas::TakeDamage()
{
	if (koopaState == KoopaState::walk)
		SetState(KoopaState::shell);
	GlobalVariables::GetInstance()->AddScore(100);
}

void CKoopas::InstanceDead()
{
	if (koopaState == KoopaState::walk)
		SetState(KoopaState::shell);
	this->vy = -KOOPAS_INSTANCE_DEAD_VY;
	this->vx = KOOPAS_SHELL_MOVING_SPEED;
}

void CKoopas::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::marioprojectile)
	{
		this->vy = -KOOPAS_INSTANCE_DEAD_VY;
		this->InstanceDead();
	}
}
