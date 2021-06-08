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
	ObjectGroup = Group::enemy;
	isBeingHold = false;
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isBeingHold || koopaState == KoopaState::die) return;

	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	CGame* game = CGame::GetInstance();
	
	if (isBeingHold)
	{
		this->x = __Mario->x + (__Mario->_marioLevel->width * __Mario->direction.x);
		this->y = __Mario->y - __Mario->_marioLevel->height / 2;
		return;
	}
	CGameObject::Update(dt);
	this->vx = this->velocity * this->direction.x;
	this->vy += KOOPAS_GRAVITY*dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (koopaState!=KoopaState::die && !isBeingHold)
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

		if (nx != 0)
		{
			//this->vx = -this->vx;
		}
		if (ny != 0)
		{
			this->vy = 0;
		}
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->ObjectGroup == Group::ground || e->obj->ObjectGroup == Group::enemy)
			{
				this->direction.x = this->direction.x * -1.0f;
			}
		}
	}

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

	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + KOOPAS_BBOX_WIDTH / 2, y - camera->GetCamPosY() + KOOPAS_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();

}

void CKoopas::SetState(KoopaState state)
{
	//CGameObject::SetState(state);
	this->koopaState = state;
	switch (koopaState)
	{
	case KoopaState::walk:
		this->velocity = -KOOPAS_WALKING_SPEED;
		this->ObjectGroup = Group::enemy;
		this->isHoldAble = false;
		break;
	case KoopaState::shell:
		this->velocity = 0;
		this->ObjectGroup = Group::shell;
		this->isHoldAble = true;
		this->y -= 0.4;
		break;
	case KoopaState::slide:
		this->velocity = KOOPAS_SHELL_MOVING_SPEED;
		this->ObjectGroup = Group::projectile;
		this->isHoldAble = false;
		this->y -= 0.4;
		break;
	case KoopaState::die:
		this->isHoldAble = false;
	}
	DebugOut(L" velocity x: %f \n ", this->vx);
}

void CKoopas::TakeDamage()
{
	if (koopaState == KoopaState::walk)
		SetState(KoopaState::shell);
}

void CKoopas::InstanceDead()
{
	SetState(KoopaState::die);
	this->direction.y = -1;
	this->vy = -KOOPAS_INSTANCE_DEAD_VY;
}

void CKoopas::BeingHold()
{
	//SetState(KOOPAS_STATE_BEING_HOLD);
}
