#include "Curtain.h"
#define ID_ANI_CURTAIN	106
Curtain::Curtain()
{
	AddAnimation(ID_ANI_CURTAIN);
	this->vy = -CURTAIN_SPEED;
}

void Curtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void Curtain::Render()
{
	int ani = ANI_ID_CURTAIN;
	animation_set[ani]->Render(x , y);
}
