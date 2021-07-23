#include "Goomba.h"
#include "Game.h"
#include "Camera.h"
#include "Mario.h"
#include "GoombaPoop.h"
CGoomba::CGoomba()
{
	AddAnimation(ID_ANI_GOOMBA_WALK);
	AddAnimation(ID_ANI_GOOMBA_DIE);
	AddAnimation(ID_ANI_GOOMBA_FLY);
	AddAnimation(ID_ANI_GOOMBA_WALK_FLY);
	AddAnimation(IA_ANI_GOOMBA_FLOAT);

	SetState(GoombaState::walk);
	this->width = GOOMBA_BBOX_WIDTH;
	this->height = GOOMBA_BBOX_HEIGHT;
	this->direction.x = 1.0f;

	this->ObjectGroup = Group::enemy;
	this->collision = Collision2D::Full;
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (this->goombaState == GoombaState::die)
		return;
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;

}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGame* game = CGame::GetInstance();

	if(this->goombaState != GoombaState::die)
		vy += GOOMBA_GRAVITY * dt;
	vx = velocity * direction.x;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (goombaState != GoombaState::instancedead)
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

			if (goombaState == GoombaState::flydown)
			{
				goombaState = GoombaState::walkfly;
				this->waitFlyTime = GetTickCount64();
			}
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
			if (e->obj->ObjectGroup == Group::projectile|| e->obj->ObjectGroup == Group::dead || e->obj->ObjectGroup == Group::marioprojectile)
			{
				if (e->obj->ObjectGroup == Group::marioprojectile)
				{
					GlobalVariables::GetInstance()->AddScore(100);
				}
				this->InstanceDead();
				e->obj->TakeDamage();
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (goombaState == GoombaState::die)
	{
		if (GetTickCount64() - this->die_time > GOOMBA_DIE_TIME)
		{
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
			GlobalVariables::GetInstance()->AddScore(100);
		}
	}
	if (goombaState == GoombaState::instancedead)
	{
		if (GetTickCount64() - this->die_time > GOOMBA_INSTANCE_DIE_TIME)
		{
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
			GlobalVariables::GetInstance()->AddScore(100);
		}
	}

	switch (goombaState)
	{
	case GoombaState::flyup:
	{
		this->vy = -GOOMBA_FLY_SPEED;
		if (this->y < CMario::GetInstance()->y - GOOMBA_HIGH_DISTANCE)
		{
			flyTime = GetTickCount64();
			poopTime = GetTickCount64();
			goombaState = GoombaState::fly;
		}
		break;
	}
	case GoombaState::fly:
	{
		if (this->x > __Mario->x)
		{
			direction.x = 1.0f;
		}
		else if (this->x < __Mario->x)
		{
			direction.x = -1.0f;
		}

		if (this->y < __Mario->y - GOOMBA_HIGH_DISTANCE)
			this->vy = GOOMBA_FLOAT_SPEED;
		else this->vy = -GOOMBA_FLOAT_SPEED;

		if (GetTickCount64() - flyTime > GOOBA_FLY_TIME)
		{
			goombaState = GoombaState::flydown;
		}
		if (GetTickCount64() - poopTime > GOOMBA_POOP_TIME)
		{
			poopTime = GetTickCount64();
			GoombaPoop* poop = new GoombaPoop();
			poop->SetPosition(this->x + GOOMBA_BBOX_WIDTH/2, this->y + GOOMBA_BBOX_HEIGHT);
			CGame::GetInstance()->GetCurrentScene()->AddObjectInGame(poop);

		}
		break;
	}
	case GoombaState::flydown:
		this->vy = GOOMBA_FLY_SPEED;
		break;
	case GoombaState::walkfly:
		if (this->x > __Mario->x)
		{
			direction.x = 1.0f;
		}
		else if (this->x < __Mario->x)
		{
			direction.x = -1.0f;
		}
		if (GetTickCount64() - waitFlyTime > GOOMBA_WALK_TIME)
			goombaState = GoombaState::flyup;
		break;
		
	}
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	switch (goombaState)
	{
	case GoombaState::walk:
		ani = GOOMBA_ANI_WALKING;
		break;
	case GoombaState::die:
		ani = GOOMBA_ANI_DIE;
		break;
	case GoombaState::instancedead:
		ani = GOOMBA_ANI_WALKING;
		this->direction.y = -1.0;
		break;
	case GoombaState::flyup:
		ani = GOOMBA_ANI_FLY;
		break;
	case GoombaState::fly:
		ani = GOOMBA_ANI_FLOAT;
		break;
	case GoombaState::flydown:
		ani = GOOMBA_ANI_FLY;
		break;
	case GoombaState::walkfly:
		ani = GOOMBA_ANI_WALK_FLY;
		break;
	}
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + GOOMBA_BBOX_WIDTH/2, y - camera->GetCamPosY() + GOOMBA_BBOX_HEIGHT/2, direction, 255);

	RenderBoundingBox();
}

void CGoomba::SetState(GoombaState state)
{
	//CGameObject::SetState(state);
	this->goombaState = state;
	switch (state)
	{
	case GoombaState::die:
		velocity = 0;
		vy = 0;
		break;
	case GoombaState::walk: 
		velocity = -GOOMBA_WALKING_SPEED;
		break;
	case GoombaState::instancedead:
		velocity = -GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_INSTANCE_DEAD_VY;
		break;
	case GoombaState::flyup:
		velocity = -GOOMBA_FLY_SPEED_X;
		break;
	}
}

void CGoomba::TakeDamage()
{
	if (goombaState != GoombaState::walk)
		SetState(GoombaState::walk);
	else
	{
		this->SetState(GoombaState::die);
		this->die_time = GetTickCount64();
	}
}

void CGoomba::InstanceDead()
{
	this->die_time = GetTickCount64();
	this->SetState(GoombaState::instancedead);
	this->width = 0;
	this->height = 0;
}

void CGoomba::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::marioprojectile|| obj->ObjectGroup == Group::projectile || obj->ObjectGroup == Group::projectile2)
	{
		this->InstanceDead();
	}
}
