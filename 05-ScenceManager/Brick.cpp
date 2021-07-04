#include "Brick.h"
#include "Game.h"
#include "Camera.h"

CBrick::CBrick()
{
	AddAnimation(ID_ANI_BRICK);
	AddAnimation(ID_ANI_BRICK_COIN);
	ObjectGroup = Group::block;
	collision = Collision2D::Full;
	this->state = STATE_BRICK;
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

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (state == STATE_COIN)
		if (GetTickCount() - coinTime > COIN_TIME)
		{
			this->state = STATE_BRICK;
			this->collision = Collision2D::Full;
		}

}

void CBrick::BrickToCoin()
{
	coinTime = GetTickCount();
	this->collision = Collision2D::None;
	this->state = STATE_COIN;
}
