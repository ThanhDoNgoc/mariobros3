#include "ParaGoomba.h"
#include "Game.h"
#include "Camera.h"
#include "Mario.h"
void ParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->goombaState == ParaGoombaState::die)
		return;
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	if (this->goombaState != ParaGoombaState::die)
		vy += GOOMBA_GRAVITY * dt;

	if (this->x + FOLLOW_RANGE > __Mario->x && this->x - FOLLOW_RANGE < __Mario->x)
	{
		if (this->x < __Mario->x)
			this->direction.x = -1;
		else this->direction.x = 1;
	}

	vx = velocity * direction.x;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (goombaState != ParaGoombaState::instancedead)
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
		/*x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;*/

		if (nx != 0)
		{
			this->direction.x *= -1.0f;
		}
		if (ny != 0)
		{
			vy = 0;
		}
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->ObjectGroup == Group::enemy || e->obj->ObjectGroup == Group::ground)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			if (e->obj->ObjectGroup == Group::projectile || e->obj->ObjectGroup == Group::dead || e->obj->ObjectGroup == Group::marioprojectile)
			{
				if (e->obj->ObjectGroup == Group::marioprojectile)
				{
					GlobalVariables::GetInstance()->AddScore(100);
				}
				this->InstanceDead();
				e->obj->TakeDamage();
			}
		}
		if (ny < 0)
		{
			switch (goombaState)
			{
			case ParaGoombaState::jump:
				SetState(ParaGoombaState::bound);
				break;
			case ParaGoombaState::bound:
			{
				this->boundCount -= 1;
				if (this->boundCount < 0)
					SetState(ParaGoombaState::jump);
				break; 
			}
			}
			this->vy = this->velocityY;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (goombaState == ParaGoombaState::die)
	{
		if (GetTickCount64() - this->die_time > GOOMBA_DIE_TIME)
		{
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
			GlobalVariables::GetInstance()->AddScore(100);
		}
	}
	if (goombaState == ParaGoombaState::instancedead)
	{
		if (GetTickCount64() - this->die_time > GOOMBA_INSTANCE_DIE_TIME)
		{
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
			GlobalVariables::GetInstance()->AddScore(100);
		}
	}
}

void ParaGoomba::Render()
{
	int ani = ID_ANI_PARAGOOMBA_FLY;
	switch (goombaState)
	{
	case ParaGoombaState::jump:
		ani = GOOMBA_ANI_FLYING;
		break;
	case ParaGoombaState::bound:
		ani = GOOMBA_ANI_BOUNDING;
		break;
	case ParaGoombaState::walk:
		ani = GOOMBA_ANI_WALKING;
		break;
	case ParaGoombaState::die:
		ani = GOOMBA_ANI_DIE;
		break;
	case ParaGoombaState::instancedead:
		ani = GOOMBA_ANI_WALKING;
		this->direction.y = -1.0;
		break;
	}
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + GOOMBA_BBOX_WIDTH / 2, y - camera->GetCamPosY() + GOOMBA_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

ParaGoomba::ParaGoomba()
{
	AddAnimation(ID_ANI_PARAGOOMBA_FLY);
	AddAnimation(ID_ANI_PARAGOOMBA_BOUND);
	AddAnimation(ID_ANI_PARAGOOMBA_WALK);
	AddAnimation(ID_ANI_PARAGOOMBA_DIE);
	SetState(ParaGoombaState::bound);
	this->width = GOOMBA_BBOX_WIDTH;
	this->height = GOOMBA_BBOX_HEIGHT;
	this->direction.x = 1.0f;

	this->ObjectGroup = Group::enemy;
	this->collision = Collision2D::Full;
}

void ParaGoomba::SetState(ParaGoombaState state)
{
	this->goombaState = state;
	switch (goombaState)
	{
	case ParaGoombaState::jump:
		this->velocityY = -GOOMBA_JUMP_SPEED;
		this->velocity = -GOOMBA_WALKING_SPEED;
		break;
	case ParaGoombaState::bound:
		this->velocityY = -GOOMBA_BOUND_SPEED;
		this->velocity = -GOOMBA_WALKING_SPEED;
		this->boundCount = 3;
		break;
	case ParaGoombaState::walk:
		this->velocityY = 0;
		this->velocity = -GOOMBA_WALKING_SPEED;
		break; 
	case ParaGoombaState::die:
		this->vx = 0;
		this->vy = 0;
		this->velocityY = 0;
		velocity = 0;
		break;
	case ParaGoombaState::instancedead:
		this->vy = -GOOMBA_INSTANCE_DEAD_VY;
	}
}

void ParaGoomba::TakeDamage()
{
	GlobalVariables::GetInstance()->AddScore(100);
	if (this->goombaState != ParaGoombaState::walk)
		this->SetState(ParaGoombaState::walk);
	else
	{
		this->SetState(ParaGoombaState::die);
		this->die_time = GetTickCount64();
	}
}

void ParaGoomba::InstanceDead()
{
	this->die_time = GetTickCount64();
	this->SetState(ParaGoombaState::instancedead);
	this->width = 0;
	this->height = 0;
}

void ParaGoomba::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::marioprojectile)
	{
		this->InstanceDead();
	}
}
