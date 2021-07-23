#include "WorldMapMario.h"

WorldMapMario::WorldMapMario()
{
	this->level = GlobalVariables::GetInstance()->mariolvl;
	AddAnimation(ID_ANI_WORLDMAP_MARIO_SMALL);
	AddAnimation(ID_ANI_WORLDMAP_MARIO_BIG);
	AddAnimation(ID_ANI_WORLDMAP_MARIO_FIRE);
	AddAnimation(ID_ANI_WORLDMAP_MARIO_RACC);
	this->ObjectGroup = Group::player;
	this->collision = Collision2D::None;
	this->curentNode = 0;
	//this->wmmstate = WMMarioState::idle;
}

void WorldMapMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + WORLD_MAP_MARIO_WIDTH;
	bottom = right + WORLD_MAP_MARIO_HEIGHT;
}

void WorldMapMario::Update(DWORD dt)
{
	this->startX += vx * dt;
	this->startY += vy * dt;
	switch (wmmstate)
	{
	case WMMarioState::idle:
		break;
	case WMMarioState::up:
		if (this->startY < this->y)
			switchstate(WMMarioState::idle);
		break;
	case WMMarioState::down:
		if (this->startY > this->y)
			switchstate(WMMarioState::idle);
		break;
	case WMMarioState::left:
		if (this->startX < this->x)
			switchstate(WMMarioState::idle);
		break;
	case WMMarioState::right:
		if (this->startX > this->x)
			switchstate(WMMarioState::idle);
		break;
	}
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

	animation_set[ani]->Render(startX - camera->GetCamPosX() + WORLD_MAP_MARIO_WIDTH / 2, startY - camera->GetCamPosY() + WORLD_MAP_MARIO_HEIGHT / 2);

}

void WorldMapMario::OnKeyDown(int KeyCode)
{
	/*if (this->ismovingx || this->ismovingy) 
		return;*/
	if (wmmstate != WMMarioState::idle) return;
	auto currentnode = map->getNode(this->curentNode);

	if (KeyCode == DIK_A)
	{
		if (currentnode->getScence() != 0)
			CGame::GetInstance()->SwitchScene(currentnode->getScence());
	}


	int acceptedKey;
	for (auto adj : *currentnode->getAdjacentList())
	{
		switch (adj.direction)
		{
		case NextNode::left: acceptedKey = (DIK_LEFT); break;
		case NextNode::right: acceptedKey = (DIK_RIGHT); break;
		case NextNode::up: acceptedKey = (DIK_UP); break;
		case NextNode::down: acceptedKey = (DIK_DOWN); break;
		}

		if (KeyCode == acceptedKey)
		{
			switch (KeyCode)
			{
			case DIK_LEFT:
				switchstate(WMMarioState::left);
				break;
			case DIK_RIGHT:
				switchstate(WMMarioState::right);
				break;
			case DIK_UP:
				switchstate(WMMarioState::up);
				break;
			case DIK_DOWN:
				switchstate(WMMarioState::down);
				break;
			}
			auto adjNode = map->getNode(adj.nodeID);
			if (adjNode)
			{
				//this->x = currentnode->GetPositionX();
				//this->y = currentnode->GetPositionY();

				curentNode = adj.nodeID;
				this->x = adjNode->GetPositionX();
				this->y = adjNode->GetPositionY();
			}
			break;
		}
	}
}

void WorldMapMario::setMap(NodeMap* map)
{
	this->map = map;
}

void WorldMapMario::switchstate(WMMarioState state)
{
	this->wmmstate = state;
	switch (wmmstate)
	{
	case WMMarioState::idle:
		this->vx = 0;
		this->vy = 0;
		this->startX = this->x;
		this->startY = this->y;
		break;
	case WMMarioState::up:
		this->vx = 0;
		this->vy = -WORLD_MAP_MARIO_MOVE_SPEED;
		break;
	case WMMarioState::down:
		this->vx = 0;
		this->vy = WORLD_MAP_MARIO_MOVE_SPEED;
		break;
	case WMMarioState::left:
		this->vx = -WORLD_MAP_MARIO_MOVE_SPEED;
		this->vy = 0;
		break;
	case WMMarioState::right:
		this->vx = WORLD_MAP_MARIO_MOVE_SPEED;
		this->vy = 0;
		break;
	}
}

NodeMap* WorldMapMario::getMap()
{
	return map;
}
