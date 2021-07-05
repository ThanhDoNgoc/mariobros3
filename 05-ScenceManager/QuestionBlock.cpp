#include "QuestionBlock.h"
#include "Camera.h"
#include "Game.h"
#include "Coin.h"
#include "Leaf.h"
#include "PButton.h"
#include "RedMushroom.h"
QuestionBlock::QuestionBlock()
{
	AddAnimation(ID_ANI_QUESTION_BLOCK);
	AddAnimation(ID_ANI_QUESTION_BLOCK_CLAIMED);
	this->isClaimed = false;
	this->collision = Collision2D::Full;
	this->ObjectGroup = Group::block;
	this->isVisible = true;
}

void QuestionBlock::Render()
{
	if (this->isVisible)
	{
		int ani = ANI_QUESTION_BLOCK;
		if (isClaimed)
			ani = ANI_QUESTION_BLOCK_CLAIMED;
		Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
		animation_set[ani]->Render(x - camera->GetCamPosX() + QBLOCK_BBOX_WIDTH / 2, y - camera->GetCamPosY() + QBLOCK_BBOX_HEIGHT / 2, direction, 255);
	}
	RenderBoundingBox();
}

void QuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QBLOCK_BBOX_WIDTH;
	b = y + QBLOCK_BBOX_HEIGHT;
}

void QuestionBlock::TakeDamage()
{
	if (!isClaimed)
	{
		this->isClaimed = true;
		switch (qblockItem)
		{
		case Item::Coin:
		{
			break;
		}
		case Item::RedMushroom:
		{
			RedMushroom* red = new RedMushroom();
			red->SetPosition(this->x, this->y);
			CGame::GetInstance()->GetCurrentScene()->AddObject(red);
			break;
		}
		case Item::GreenMushroom:
		{
			break;
		}
		case Item::Leaf:
		{
			Leaf* leaf = new Leaf();
			leaf->SetPosition(this->x, this->y);
			CGame::GetInstance()->GetCurrentScene()->AddObject(leaf);
			break;
		}
		case Item::Flower:
		{
			break;
		}
		case Item::PButton:
		{
			this->isVisible = true;
			PButton* pbtn = new PButton();
			pbtn->SetPosition(this->x, this->y - 48);
			CGame::GetInstance()->GetCurrentScene()->AddObject(pbtn);
			break;
		}
		}
	}

}

void QuestionBlock::SetItem(string item)
{
	if (item == "coin")
		this->qblockItem = Item::Coin;
	else if (item == "redmushroom")
		this->qblockItem = Item::RedMushroom;
	else if (item == "greenmushroom")
		this->qblockItem = Item::GreenMushroom;
	else if (item == "leaf")
		this->qblockItem = Item::Leaf;
	else if (item == "flower")
		this->qblockItem = Item::Flower;
	else if (item == "pbutton")
	{
		this->qblockItem = Item::PButton;
		this->isVisible = false;
	}
}
