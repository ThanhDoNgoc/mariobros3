#include "PButton.h"
#include "Game.h"
#include "Camera.h"
PButton::PButton()
{
	AddAnimation(ID_ANI_P_BUTTON);
	AddAnimation(ID_ANI_P_BUTTON_CLAIMED);
	ObjectGroup = Group::item;
	collision = Collision2D::None;
}

void PButton::Render()
{
	int ani = ANI_ID_P_BUTTON;
	if (isClaimed == true)
		ani = ANI_ID_P_CLAIMED;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + PBUTTON_BBOX_WIDTH / 2, y - camera->GetCamPosY() + PBUTTON_BBOX_HEIGHT / 2, direction, 255);
	RenderBoundingBox();
}

void PButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PBUTTON_BBOX_WIDTH;
	b = y + PBUTTON_BBOX_HEIGHT;
}

void PButton::TakeDamage()
{
	if (!isClaimed)
	{
		isClaimed = true;
		GlobalVariables::GetInstance()->StartPtime();
	}
}

void PButton::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::player)
	{
		this->TakeDamage();
	}
}

void PButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
}
