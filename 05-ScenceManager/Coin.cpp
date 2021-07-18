#include "Coin.h"
#include "Game.h"
#include "Camera.h"
#include "GlobalVariables.h"

Coin::Coin()
{
	AddAnimation(ID_ANI_COIN);
	ObjectGroup = Group::item;
	collision = Collision2D::None;
	this->isSprouting = false;
	this->vx = 0;
	this->vy = 0;
	this->objectLayer = 0;
}

void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (isSprouting)
	{
		vy += 0.0015 * dt;
		if (this->y > this->startY)
		{
				CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
				GlobalVariables::GetInstance()->AddCoin(1);
		}
	}

	x += dx;
	y += dy;
}

void Coin::Render()
{
	int ani = ANI_COIN;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + COIN_BBOX_WIDTH / 2, y - camera->GetCamPosY() + COIN_BBOX_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}

void Coin::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
		GlobalVariables::GetInstance()->AddCoin(1);
	}
}

void Coin::Sprout()
{
	this->vy = -0.5;
	this->isSprouting = true;
}
