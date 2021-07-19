#include "BoomerangBro.h"
#include "Camera.h"
#include "Game.h"
#include "Mario.h"
#include "Boomerang.h"
BoomerangBro::BoomerangBro()
{
	AddAnimation(ID_ANI_BOOMERANG_BRO_NONE);
	AddAnimation(ID_ANI_BOOMERANG_BRO_ATTACK);
	this->bbroState=BBroState::idleright;
	this->isDead = false;
	this->ObjectGroup = Group::enemy;
	this->collision = Collision2D::Full;
	this->startAttackTime = GetTickCount();
	this->bbroAtkState = BBroAttackSate::NoneAttack1;
}

void BoomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDead) return;
	left = x;
	top = y;
	right = x + BBRRO_BBOX_WIDTH;
	bottom = y + BBRRO_BBOX_HEIGHT;
}

void BoomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	if (this->x < __Mario->x)
		this->direction.x = -1;
	else this->direction.x = 1;

	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (!isDead)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	else
	{
		x += dx;
		y += dy;
	}

	this->vy += BBRO_GRAVITY * dt;

	if (coEvents.size() == 0)
	{
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

		if (ny != 0)
		{
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->ObjectGroup == Group::projectile || e->obj->ObjectGroup == Group::marioprojectile)
			{
				this->TakeDamage();
			}
		}
		
		
	}

	switch (this->bbroState)
	{
	case BBroState::idleright:
	{
		this->vx = 0;
		if (GetTickCount() - idleTime > BBRO_IDLE_TIME)
		{
			bbroState = BBroState::walkleft;
		}

		break;
	}
	case BBroState::walkleft:
	{
		this->vx = -BBRO_WALKING_SPEED;
		if (abs(this->x - this->startX) > BBRO_WALKING_DISTANCE)
		{
			this->x = this->startX - BBRO_WALKING_DISTANCE;
			this->idleTime = GetTickCount();
			bbroState = BBroState::idleleft;
		}
		break;
	}
	case BBroState::idleleft:
	{
		this->vx = 0;
		if (GetTickCount() - idleTime > BBRO_IDLE_TIME)
		{
			bbroState = BBroState::walkright;
		}
		break;
	}
	case BBroState::walkright:
	{
		this->vx = +BBRO_WALKING_SPEED;
		if (this->x > this->startX)
		{
			this->x = this->startX;
			this->idleTime = GetTickCount();
			bbroState = BBroState::idleright;
		}
		break;
	}
	}
	CGameObject::Update(dt);

	switch (bbroAtkState)
	{
	case BBroAttackSate::NoneAttack1:
		this->startAttackTime = GetTickCount();
		this->waitAttack = true;
		this->bbroAtkState = BBroAttackSate::WaitAttack1;
		break;
	case BBroAttackSate::WaitAttack1:
		if (GetTickCount() - startAttackTime > BBRO_ATTACK_WAIT_TIME)
		{
			this->waitAttack = false;
			Boomerang* bmr = new Boomerang(this->x, this->y-24, -this->direction.x);
			CGame::GetInstance()->GetCurrentScene()->AddObject(bmr);
			this->bbroAtkState = BBroAttackSate::NoneAttack2;
		}
		break;
	case BBroAttackSate::NoneAttack2:
		if (GetTickCount() - startAttackTime > BBRO_SECOND_ATTACK_TIME)
		{
			this->waitAttack = true;
			this->bbroAtkState = BBroAttackSate::WaitAttack2;
		}
		break;
	case BBroAttackSate::WaitAttack2:
		if (GetTickCount() - startAttackTime > BBRO_SECOND_ATTACK_TIME + BBRO_ATTACK_WAIT_TIME)
		{
			this->waitAttack = false;
			Boomerang* bmr = new Boomerang(this->x, this->y-24, -this->direction.x);
			CGame::GetInstance()->GetCurrentScene()->AddObject(bmr);
			this->bbroAtkState = BBroAttackSate::NoneAttack3;
		}
		break;
	case BBroAttackSate::NoneAttack3:
		if (GetTickCount() - startAttackTime > BBRO_ATTACK_TIME)
		{
			this->bbroAtkState = BBroAttackSate::NoneAttack1;
		}
	}

}

void BoomerangBro::Render()
{
	int ani = ANI_ID_BBRO_NONE;
	if (waitAttack)
		ani = ANI_ID_BBRO_ATTACK;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + BBRRO_BBOX_WIDTH / 2, y - camera->GetCamPosY() + BBRRO_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}


void BoomerangBro::TakeDamage()
{
	this->direction.y = -1.0f;
	this->isDead = true;
	GlobalVariables::GetInstance()->AddScore(1000);
}

void BoomerangBro::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::projectile || obj->ObjectGroup == Group::marioprojectile)
	{
		this->TakeDamage();
	}
	else if (dynamic_cast<Boomerang*>(obj))
	{
		Boomerang* bmr = dynamic_cast<Boomerang*>(obj);
		if (bmr -> canFlyBack == false)
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(bmr);
	}
	else if (obj->ObjectGroup == Group::dead)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
	}
}
