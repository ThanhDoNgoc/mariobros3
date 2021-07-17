#include "EndGameReward.h"
#include"Camera.h"
#include"Game.h"
#include "Mario.h"
EndGameReward::EndGameReward()
{
	this->isCollected = false;
	this->isAddCard = false;
	this->switchTime = GetTickCount();
	this->state = REWARD_STATE_MUSHROOM;
	this->ObjectGroup = Group::item;
	this->collision = Collision2D::None;
	AddAnimation(ID_ANI_REWARD_MUSHROOM);
	AddAnimation(ID_ANI_REWARD_FLOWER);
	AddAnimation(ID_ANI_REWARD_STAR);
}

void EndGameReward::Render()
{
	int ani = 0;
	switch (this->state)
	{
	case REWARD_STATE_MUSHROOM:
		ani = ANI_REWARD_MUSHROOM;
		break;
	case REWARD_STATE_FLOWER:
		ani = ANI_REWARD_FLOWER;
		break;
	case REWARD_STATE_STAR:
		ani = ANI_REWARD_STAR;
		break;
	}
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY());
	RenderBoundingBox();
}

void EndGameReward::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + REWARD_BBOX_WIDTH;
	b = y + REWARD_BBOX_HEIGHT;
}

void EndGameReward::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		this->isCollected=true;
		__Mario->SetState(new PlayerStateEndGame());
		//__Mario->isEndScene = true;
		//__Mario->SetState(new PlayerStateEndGame());
		if (!isAddCard)
		{
			GlobalVariables::GetInstance()->AddCard(this->state+1);
			DebugOut(L" endgamecard: %d \n ", this->state + 1);
			this->isAddCard = true;
		}
	}
}

void EndGameReward::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (!isCollected)
	{
		switch (state)
		{
		case REWARD_STATE_MUSHROOM:
			if (GetTickCount() - switchTime > SWITCH_TIME)
			{
				this->switchTime = GetTickCount();
				this->state = REWARD_STATE_FLOWER;
			}
			break;
		case REWARD_STATE_FLOWER:
			if (GetTickCount() - switchTime > SWITCH_TIME)
			{
				this->switchTime = GetTickCount();
				this->state = REWARD_STATE_STAR;
			}
			break;
		case REWARD_STATE_STAR:
			if (GetTickCount() - switchTime > SWITCH_TIME)
			{
				this->switchTime = GetTickCount();
				this->state = REWARD_STATE_MUSHROOM;
			}
			break;
		}
	}
	else 
	{
		this->y -= FLY_SPEED*dt;
	}
}

