#include "MarioFireBall.h"
#include "defineAni.h"
#include "Camera.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopas.h"
MarioFireBall::MarioFireBall(float posX, float posY, float direcX, float direcY)
{
	AddAnimation(ID_ANI_FIREBALL);
	this->vx = FIREBALL_SPEED;
	this->direction = D3DXVECTOR2(direcX, direcY);
	this->x = posX;
	this->y = posY;
}

void MarioFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;

}

void MarioFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	// Calculate dx, dy 
	vx = FIREBALL_SPEED * this->direction.x;
	vy += FIREBALL_GRAVITY * dt;
	CGameObject::Update(dt);

	//playerState->Update(*this);
	// Simple fall down
	//vy += FIREBALL_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0)
		{
			vy = -FIREBALL_SPEED;
		}
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				if (goomba->GetState()!= GOOMBA_STATE_DIE)
					goomba->InstanceDead();
				
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (koopas->GetState() != KOOPAS_STATE_DIE)
				koopas->InstanceDead();
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void MarioFireBall::Render()
{
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[FIREBALL_ANI]->Render(x - camera->GetCamPosX() + FIREBALL_BBOX_WIDTH / 2, y - camera->GetCamPosY() + FIREBALL_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}