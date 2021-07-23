#include "Leaf.h"
#include "Camera.h"
#include "Game.h"
#include "Mario.h"
Leaf::Leaf()
{
	AddAnimation(ID_ANI_LEAF);

	this->ObjectGroup = Group::item;
	this->collision = Collision2D::None;

	leafRevealTime = GetTickCount64();

	this -> state = 1;
	this->objectLayer = 0;
	this->cycleTime = 0;
	this->isClaimed = false;
	this->timeClaimed = 0;

}

void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);
	this->x += dx;
	this->y += dy;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	switch (state)
	{
	case 1:
	{
		if (GetTickCount64() - leafRevealTime > LEAF_REVEAL_TIME)
		{
			cycleTime = GetTickCount64();
			vy = 0;
			state = 2;
		}
		else
		{
			vy = -LEAF_REVEAL_VY;
		}
	}
	break;
	case 2:
	{
		vy = LEAF_FALLING_VEL;
		vx = -LEAF_FALLING_VX * direction.x;
	}
	break;
	}

	if (GetTickCount64() - cycleTime > LEAF_CYCLE_TIME)
	{
		direction.x = -direction.x;
		cycleTime = GetTickCount64();
	}
}

void Leaf::Render()
{
	int ani = ANI_ID_LEAF;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + LEAF_WIDTH / 2, y - camera->GetCamPosY() + LEAF_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void Leaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + LEAF_WIDTH;
	b = y + LEAF_HEIGHT;
}

void Leaf::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteObject(this);
		GlobalVariables::GetInstance()->AddScore(1000);
		if (__Mario->level = MARIO_LEVEL_SMALL)
			__Mario->y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
		__Mario->_marioLevel = new MarioLevelRaccoon();
	}
}
