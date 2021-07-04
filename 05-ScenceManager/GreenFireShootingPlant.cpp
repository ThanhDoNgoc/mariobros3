#include "GreenFireShootingPlant.h"
#include "Game.h"
#include "Camera.h"
#include "Mario.h"
#include "PlantFireBall.h"
void GreenFireShootingPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + RED_FIRE_SHOOTING_PLANT_WIDTH;
	bottom = y + RED_FIRE_SHOOTING_PLANT_HEIGHT;
}

void GreenFireShootingPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);
	this->x += dx;
	this->y += dy;

	if (__Mario->y > this->y)
		this->aim = Aim1::down;
	else this->aim = Aim1::up;

	if (this->x < __Mario->x)
		this->direction.x = -1;
	else this->direction.x = 1;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->ObjectGroup == Group::projectile)
			{
				this->TakeDamage();
			}
		}
	}

	switch (this->state)
	{
	case ShootPlantState1::idledown:
	{
		this->vy = 0;
		distance = 0;
		if (GetTickCount() - hideTime_start > RED_FIRE_SHOOTING_PLANT_HIDE_TIME)
		{
			DebugOut(L"[INFO] slide up\n");
			state = ShootPlantState1::slideup;
		}

		break;
	}
	case ShootPlantState1::slideup:
	{
		this->vy = -RED_FIRE_SHOOTING_PLANT_SPEED;
		distance += abs(vy * dt);
		if (distance > RED_FIRE_SHOOTING_PLANT_HEIGHT)
		{
			distance = RED_FIRE_SHOOTING_PLANT_HEIGHT;
			this->waitTime_start = GetTickCount();
			DebugOut(L"[INFO] idle up \n");
			state = ShootPlantState1::idleup;
		}
		break;
	}
	case ShootPlantState1::idleup:
	{
		this->vy = 0;
		if (GetTickCount() - waitTime_start > RED_FIRE_SHOOTING_PLANT_WAIT_TIME)
		{
			distance = 0;
			DebugOut(L"[INFO] slide down \n");
			state = ShootPlantState1::slidedown;
			ShootFire();
		}
		break;
	}
	case ShootPlantState1::slidedown:
	{
		this->vy = +RED_FIRE_SHOOTING_PLANT_SPEED;
		distance += abs(vy * dt);
		if (distance > RED_FIRE_SHOOTING_PLANT_HEIGHT)
		{
			distance = RED_FIRE_SHOOTING_PLANT_HEIGHT;
			this->hideTime_start = GetTickCount();
			DebugOut(L"[INFO] idle down \n");
			state = ShootPlantState1::idledown;
		}
		break;
	}
	}
}

void GreenFireShootingPlant::Render()
{
	int ani = 0;
	if (this->aim == Aim1::down)
		ani = ANI_ID_RED_FIRE_SHOOTING_PLANT_DOWN;
	else ani = ANI_ID_RED_FIRE_SHOOTING_PLANT_UP;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + RED_FIRE_SHOOTING_PLANT_WIDTH / 2, y - camera->GetCamPosY() + RED_FIRE_SHOOTING_PLANT_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void GreenFireShootingPlant::ShootFire()
{
	int aimfire;
	if (this->aim == Aim1::down)
		aimfire = -1;
	else aimfire = 1;
	PlantFireBall* fireball = new PlantFireBall(this->x + FIREBALL_POS, this->y + FIREBALL_POS, -this->direction.x, aimfire);
	CGame::GetInstance()->GetCurrentScene()->AddObject(fireball);
}

void GreenFireShootingPlant::TakeDamage()
{
	this->aim = Aim1::up;
	this->state = ShootPlantState1::idledown;
	AddAnimation(ID_ANI_GREEN_SHOOTING_PLANT_DOWN);
	AddAnimation(ID_ANI_GREEN_SHOOTING_PLANT_UP);

	this->ObjectGroup = Group::projectile;
	this->collision = Collision2D::Full;
	this->hideTime_start = GetTickCount();
}

GreenFireShootingPlant::GreenFireShootingPlant()
{
	CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}
