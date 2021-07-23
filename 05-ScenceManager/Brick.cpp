#include "Brick.h"
#include "Game.h"
#include "Camera.h"
#include "Mario.h"
#include "BreakBrick.h"
CBrick::CBrick()
{
	AddAnimation(ID_ANI_BRICK);
	AddAnimation(ID_ANI_BRICK_COIN);
	ObjectGroup = Group::block;
	collision = Collision2D::Full;
	this->state = STATE_BRICK;
	this->vy = 0;
	this->vx = 0;
}

void CBrick::Render()
{
	int ani = ANI_BRICK;
	if (state == STATE_BRICK)
		ani = ANI_BRICK;
	else ani = ANI_COIN;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + BRICK_BBOX_WIDTH / 2, y - camera->GetCamPosY() + BRICK_BBOX_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrick::TakeDamage()
{
	if (state == STATE_BRICK)
	{
		BreakBrick* br1 = new BreakBrick(this->x, this->y, true, false);
		BreakBrick* br2 = new BreakBrick(this->x + 24, this->y, true, true);
		BreakBrick* br3 = new BreakBrick(this->x, this->y + 24, false, false);
		BreakBrick* br4 = new BreakBrick(this->x + 24, this->y + 24, false, true);

		CGame::GetInstance()->GetCurrentScene()->AddObjectInGame(br1);
		CGame::GetInstance()->GetCurrentScene()->AddObjectInGame(br2);
		CGame::GetInstance()->GetCurrentScene()->AddObjectInGame(br3);
		CGame::GetInstance()->GetCurrentScene()->AddObjectInGame(br4);
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (GlobalVariables::GetInstance()->isPtime())
	{
		this->state = STATE_COIN;
		this->collision = Collision2D::None;
	}
	else
	{
		this->state = STATE_BRICK;
		this->collision = Collision2D::Full;
	}

	this->y += vy * dt;

	if (this->y > this->startY)
	{
		this->y = this->startY;
		vy = 0;
	}
	

}

void CBrick::BrickToCoin()
{
	this->collision = Collision2D::None;
	this->state = STATE_COIN;
}

void CBrick::OnOverLap(CGameObject* obj)
{
	switch (state)
	{
	case STATE_BRICK:
	{
		if (obj->ObjectGroup == Group::marioprojectile)
		{
			this->TakeDamage();
			obj->TakeDamage();
		}
		break;
	}
	case STATE_COIN:
	{
		if (obj->ObjectGroup == Group::player)
		{
			GlobalVariables::GetInstance()->AddCoin(1);
			CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
		}
		break;		
	}
	}
}

void CBrick::Bound()
{
	this->y -= 12;
	this->vy = 0.05f;
}
