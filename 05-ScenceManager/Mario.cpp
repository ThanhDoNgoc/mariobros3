#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "Camera.h"

#include "Goomba.h"
#include "Portal.h"
#include "Koopas.h"
#include "Warp.h"
#include "Leaf.h"
#include "PSPortal.h"

#include "PlayerState.h"
#include "PlayerStateIdle.h"
#include "PlayerStateWalk.h"
#include "PlayerStateRun.h"
#include "PlayerStateJump.h"
#include "PlayerStateCrouch.h"
#include "PlayerStateWarp.h"
#include "PlayerStateFall.h"

CMario* CMario::__instance = NULL;

CMario::CMario(float x, float y) : CGameObject()
{
	this->__instance = this;
	this->_marioLevel = new MarioLevelSmall();
	this->isHolding = false;
	this->isWarping = false;

	untouchable = 0;
	DebugOut(L"[INFO] create new IDLE");
	this->SetState(new PlayerStateIdle());

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 

	this->obj = NULL;

	this->ObjectGroup = Group::player;
	this->collision = Collision2D::Full;

	this->fireball = 2;
}

CMario* CMario::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new CMario();
	}
	return __instance;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	_playerState->Update();
	
	CGame* game = CGame::GetInstance();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CGameObject::Update(dt);

	if (isWarping)
	{
		CalcPotentialCollisions(coObjects, coEvents);
		y += dy;
		return;
	}

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	// turn off collision when die 
	//if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount() - on_max_charge_start > MARIO_MAX_CHARGE_TIME)
	{
		this->isMaxCharge = false;
	}
	if (GetTickCount() - kickStart > MARIO_KICK_TIME)
	{
		this->isKicking = false;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
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
		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny != 0)
		{
			vy = 0;
		}
		if (ny < 0) isOnGround = true;
		else
		{
			isOnGround = false;
		}

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->ObjectGroup == Group::enemy) // if e->obj is Enemy 
			{
				// jump on top >> kill Enemy and deflect a bit 
				if (e->ny < 0)
				{
					e->obj->TakeDamage();
					this->SetState(new PlayerStateJump());
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
							this->TakeDamage();
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopa = dynamic_cast<CKoopas*>(e->obj);
				if (koopa->koopaState == KoopaState::shell)
				{
					if (KeyHanler::GetInstance()->IsKeyDown(DIK_A))
					{
						koopa->isBeingHold = true;
						this->obj = koopa;
						this->isHolding = true;
					}
					else
					{
						koopa->direction.x = this->direction.x;
						koopa->SetState(KoopaState::slide);
						StartKick();
					}
				}
			}
			else if (e->obj->ObjectGroup == Group::projectile)
			{
				this->TakeDamage();
			}
			else if (e->obj->ObjectGroup == Group::block)
			{
				if (e->ny > 0)
					e->obj->TakeDamage();
			}
			else if (e->obj->ObjectGroup == Group::item)
			{
					e->obj->TakeDamage();
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	DebugOut(L" velocity y: %f \n ", vy);
	//if (this->obj != NULL)
}

void CMario::Render()
{

	_playerState->SetAnimation();
	if (isKicking)
		ani = MARIO_ANI_KICK;
	int alpha = 255;
	if (untouchable) alpha = 128;

	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + this->width/2  , y - camera->GetCamPosY() + this->height/2 , direction, alpha);

	RenderBoundingBox();
}

void CMario::SetState(PlayerState* newState)
{
	delete _playerState;
	_playerState = newState;
}

void CMario::SetLevel(int lvl)
{
	//this->level = lvl;
}


void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + this->width;
	bottom = y + this->height;

}

void CMario::TakeDamage()
{
	this->_marioLevel->LevelDown();
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(new PlayerStateIdle());
	this->_marioLevel = new MarioLevelSmall();
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CMario::GetAnimation(int new_ani)
{
	ani = new_ani;
}

void CMario::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_A:
		if (isHolding)
		{
			//obj->SetState(KOOPAS_STATE_SHELL);
			isHolding = false;
			obj->setBeingHold(false);
			obj->setHoldAble(true);
		}
		break;
	}
}


void CMario::OnKeyDown(int KeyCode)
{
	this->_playerState->OnKeyDown(KeyCode);

	switch (KeyCode)
	{
	case DIK_0:
		Reset();
		break;
	case DIK_1:
		this->_marioLevel = new MarioLevelSmall();
		break;
	case DIK_2:
		this->_marioLevel = new MarioLevelBig();
		break;
	case DIK_3:
		this->_marioLevel = new MarioLevelFire();
		break;
	case DIK_4:
		this->_marioLevel = new MarioLevelRaccoon();
		break;
	case DIK_9:
		_marioLevel->LevelDown();
		break;
	case DIK_5:
		this->SetPosition(6744, 330);
		break;
	}
}

void CMario::OnOverLap(CGameObject* obj)
{
	if (obj->ObjectGroup == Group::projectile2)
	{
		this->TakeDamage();
	}
	else if (dynamic_cast<CKoopas*>(obj))
	{
		CKoopas* koopa = dynamic_cast<CKoopas*>(obj);
		if (koopa->koopaState == KoopaState::shell)
		{
			if (!isHolding)
			{
				koopa->direction.x = this->direction.x;
				koopa->SetState(KoopaState::slide);
				StartKick();
			}
		}
	}
	else if (obj->ObjectGroup == Group::warp)
	{
		auto warp = static_cast<Warp*>(obj);
		if (KeyHanler::GetInstance()->IsKeyDown(warp->getKeyDirection()))
		{

			this->SetState(new PlayerStateWarp(warp->isDown(), warp->toX, warp->toY));
		}
	}
	else if (dynamic_cast<PSPortal*>(obj))
	{
		PSPortal* portal = dynamic_cast<PSPortal*>(obj);
		Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
		camera->SetCamLimit(portal->camL, portal->camT, portal->camR, portal->camB);
		if (this->level == MARIO_LEVEL_SMALL)
			this->SetPosition(portal->posX, portal->posY);
		else
			this->SetPosition(portal->posX, portal->posY - 100);
		this->SetState(new PlayerStateJump());
		this->isWarping = false;
		this->vy = 0;
		switch (level)
		{
		case MARIO_LEVEL_SMALL:
			this->_marioLevel = new MarioLevelSmall();
			break;
		case MARIO_LEVEL_BIG:
			this->_marioLevel = new MarioLevelBig();
			break;
		case MARIO_LEVEL_FIRE:
			this->_marioLevel = new MarioLevelFire();
			break;
		case MARIO_LEVEL_RACCOON:
			this->_marioLevel = new MarioLevelRaccoon();
			break;
		}
	}

}


