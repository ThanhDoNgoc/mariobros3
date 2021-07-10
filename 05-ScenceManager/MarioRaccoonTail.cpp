#include "MarioRaccoonTail.h"
#include "Game.h"
MarioRaccoonTail::MarioRaccoonTail(float x, float y)
{
	this->deleteTime = GetTickCount();
	this->ObjectGroup = Group::marioprojectile;
	this->collision = Collision2D::None;
	this->x = x;
	this->y = y;
}

void MarioRaccoonTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void MarioRaccoonTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (GetTickCount() - deleteTime > ATTACK_TIME)
	{
		this->TakeDamage();
	}
}

void MarioRaccoonTail::Render()
{
	RenderBoundingBox();
}

void MarioRaccoonTail::TakeDamage()
{
	CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
}

void MarioRaccoonTail::OnOverLap(CGameObject* obj)
{
}
