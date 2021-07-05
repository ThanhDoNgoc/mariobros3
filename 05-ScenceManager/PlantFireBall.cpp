#include "PlantFireBall.h"
#include "Camera.h"
#include "Game.h"
void PlantFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void PlantFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	this->x += dx*direction.x;
	this->y += dy*direction.y;
}

void PlantFireBall::Render()
{
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[FIREBALL_ANI]->Render(x - camera->GetCamPosX() + FIREBALL_BBOX_WIDTH / 2, y - camera->GetCamPosY() + FIREBALL_BBOX_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void PlantFireBall::TakeDamage()
{
}


PlantFireBall::PlantFireBall(float posX, float posY, float direcX, float direcY)
{
	AddAnimation(ID_ANI_FIREBALL);
	this->vx = FIREBALL_SPEED;
	this->vy = -FIREBALL_SPEED;
	this->direction = D3DXVECTOR2(direcX, direcY);
	this->x = posX;
	this->y = posY;
	this->ObjectGroup = Group::projectile2;
	this->collision = Collision2D::None;
}
