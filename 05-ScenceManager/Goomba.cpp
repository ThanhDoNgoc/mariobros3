#include "Goomba.h"
#include "Game.h"
#include "Camera.h"

CGoomba::CGoomba()
{
	AddAnimation(ID_ANI_GOOMBA_WALK);
	AddAnimation(ID_ANI_GOOMBA_DIE);
	SetState(GoombaState::walk);
	this->width = GOOMBA_BBOX_WIDTH;
	this->height = GOOMBA_BBOX_HEIGHT;
	this->direction.x = -1.0f;

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
			if (e->obj->ObjectGroup == Group::projectile)
			{
				this->InstanceDead();
				e->obj->TakeDamage();
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (goombaState == GoombaState::die)
	{
		if (GetTickCount() - this->die_time > GOOMBA_DIE_TIME)
		{
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
			GlobalVariables::GetInstance()->AddScore(100);
		}
	}
	if (goombaState == GoombaState::instancedead)
	{
		if (GetTickCount() - this->die_time > GOOMBA_INSTANCE_DIE_TIME)
		{
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
			GlobalVariables::GetInstance()->AddScore(100);
		}
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
	}
}

void CGoomba::TakeDamage()
{
	this->SetState(GoombaState::die);
	this->die_time = GetTickCount();
}

void CGoomba::InstanceDead()
{
	this->die_time = GetTickCount();
	this->SetState(GoombaState::instancedead);
	this->width = 0;
	this->height = 0;
}

void CGoomba::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::marioprojectile)
	{
		this->InstanceDead();
	}
}
