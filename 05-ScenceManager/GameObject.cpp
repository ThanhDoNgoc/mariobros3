#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	isActive = false;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (IsOverLapped(coObjects->at(i)))
		{
			this->OnOverLap(coObjects->at(i));
			//coObjects->at(i)->OnOverLap(this);
		}

		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
		{
			float ml = 0, mt = 0, mr = 0, mb = 0;
			// check for collisiont tag and collide direction if match then create the event!!!
			e->obj->GetBoundingBox(ml, mt, mr, mb);
			if (e->obj->collision == Collision2D::Full)
				coEvents.push_back(e);
			else if (e->ny < 0 && e->obj->collision == Collision2D::Top)
				coEvents.push_back(e);
			else if (e->ny > 0 && e->obj->collision == Collision2D::Bottom)
				coEvents.push_back(e);
		}
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny, float &rdx, float &rdy)
{
	vector<LPGAMEOBJECT> coObjectsResult;
	for (UINT i = 0; i < coEvents.size(); i++)  coObjectsResult.push_back(coEvents[i]->obj);

	vector<LPCOLLISIONEVENT> coEventsxy;
	float tempx, tempy;
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	nx = 0.0f;
	ny = 0.0f;
	tempx = this->x;
	tempy = this->y;
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_tx > min_ty)
	{
		x += min_ty * dx;
		y += min_ty * dy + ny * 0.4f;
		dy = 0;
		coEventsResult.push_back(coEvents[min_iy]);
		coEventsxy.clear();

		CalcPotentialCollisions(&coObjectsResult, coEventsxy);
		if (coEvents.size() > 0)
		{
			FilterCollisionX(coEventsxy, coEventsResult, min_tx, nx, rdx);
			if (min_ty + min_tx < 1) min_tx = min_ty + min_tx;
			else min_tx = 1;

		}
		else
		{
			nx = 0;
			min_tx = 1;
		}
		dy = vy * dt;
		y -= min_ty * dy + ny * 0.4f;
		x -= min_ty * dx;

	}
	else
	{


		x += min_tx * dx + nx * 0.4f;
		y += min_tx * dy;
		dx = 0;
		coEventsResult.push_back(coEvents[min_ix]);
		coEventsxy.clear();
		CalcPotentialCollisions(&coObjectsResult, coEventsxy);
		if (coEvents.size() > 0)
		{
			FilterCollisionY(coEventsxy, coEventsResult, min_ty, ny, rdy);
			if (min_ty + min_tx < 1) min_ty = min_ty + min_tx;
			else min_ty = 1;
		}

		else
		{

			ny = 0;
			min_ty = 1;
		}
		dx = vx * dt;
		x -= min_tx * dx + nx * 0.4f;
		y -= min_tx * dy;
	}
	for (UINT i = 0; i < coEventsxy.size(); i++)  coEvents.push_back(coEventsxy[i]);
}

void CGameObject::FilterCollisionX(
	vector<LPCOLLISIONEVENT>& coEvents, 
	vector<LPCOLLISIONEVENT>& coEventsResult, 
	float& min_tx, float& nx, float& rdx)
{
	min_tx = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	nx = 0.0f;

	for (UINT i = 0; i < coEvents.size(); i++)
	{

		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
}

void CGameObject::FilterCollisionY(
	vector<LPCOLLISIONEVENT>& coEvents, 
	vector<LPCOLLISIONEVENT>& coEventsResult, 
	float& min_ty, float& ny, float& rdy)
{
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	ny = 0.0f;


	for (UINT i = 0; i < coEvents.size(); i++)
	{

		LPCOLLISIONEVENT c = coEvents[i];
		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CGameObject::AddAnimation(int aniID)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniID);
	animation_set.push_back(ani);
	//animation_set->push_back(ani);
	DebugOut(L"ADD ANIMATION: %d \n ", aniID);
}


bool CGameObject::IsOverLapped(CGameObject* object)
{
	float left, top, right, bottom;
	float left1, top1, right1, bottom1;

	this->GetBoundingBox(left, top, right, bottom);
	object->GetBoundingBox(left1, top1, right1, bottom1);

	return CheckOverlapped(left, top, right, bottom, left1, top1, right1, bottom1);
}

bool CGameObject::CheckOverlapped(float left, float top, float right, float bottom, float left1, float top1, float right1, float bottom1)
{
	if (left >= right1 || left1 >= right || top >= bottom1 || top1 >= bottom)
		return false;

	return true;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 
	D3DXVECTOR2 direction(1.0f, 1.0f);

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	CGame::GetInstance()->Draw(x - camera->GetCamPosX() + (rect.right - rect.left)/2, y - camera->GetCamPosY() + ((rect.bottom - rect.top) / 2), (float)((rect.right - rect.left)/2), (float)(rect.bottom-rect.top)/2, bbox, rect.left, rect.top, rect.right, rect.bottom, direction, 32);
}

void CGameObject::setOwnerCell(Cell* cell)
{
	this->ownerCell = cell;
}

Cell* CGameObject::getOwerCell()
{
	return this->ownerCell;
}

void CGameObject::setId(int id)
{
	this->id = id;
}

CGameObject::~CGameObject()
{

}
