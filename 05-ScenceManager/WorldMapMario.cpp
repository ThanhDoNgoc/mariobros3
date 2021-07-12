#include "WorldMapMario.h"

WorldMapMario::WorldMapMario()
{
	this->level = __Mario->level;
	AddAnimation(ID_ANI_WORLDMAP_MARIO_SMALL);
	AddAnimation(ID_ANI_WORLDMAP_MARIO_BIG);
	AddAnimation(ID_ANI_WORLDMAP_MARIO_FIRE);
	AddAnimation(ID_ANI_WORLDMAP_MARIO_RACC);
	this->ObjectGroup = Group::player;
	this->collision = Collision2D::None;
}

void WorldMapMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + WORLD_MAP_MARIO_WIDTH;
	bottom = right + WORLD_MAP_MARIO_HEIGHT;
}

void WorldMapMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void WorldMapMario::Render()
{
	int ani = 0;
	switch (this->level)
	{
	case MARIO_LEVEL_SMALL:
		ani = WORLD_MAP_MARIO_ANI_SMALL;
		break;
	case MARIO_LEVEL_BIG:
		ani = WORLD_MAP_MARIO_ANI_BIG;
		break;
	case MARIO_LEVEL_FIRE:
		ani = WORLD_MAP_MARIO_ANI_FIRE;
		break;
	case MARIO_LEVEL_RACCOON:
		ani = WORLD_MAP_MARIO_ANI_RACOON;
		break;
	}
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();

	animation_set[ani]->Render(x - camera->GetCamPosX() + WORLD_MAP_MARIO_WIDTH / 2, y - camera->GetCamPosY() + WORLD_MAP_MARIO_HEIGHT / 2, direction, 255);

	RenderBoundingBox();
}

void WorldMapMario::OnOverLap(CGameObject* obj)
{
}

void WorldMapMario::OnKeyUp(int KeyCode)
{
}

void WorldMapMario::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		break;
	case DIK_RIGHT:
		break;
	case DIK_LEFT:
		break;
	case DIK_DOWN:
		break;
	}
}
