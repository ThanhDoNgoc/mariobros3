#include "QuestionBlock.h"
#include "Camera.h"
#include "Game.h"
QuestionBlock::QuestionBlock()
{
	AddAnimation(ID_ANI_QUESTION_BLOCK);
	AddAnimation(ID_ANI_QUESTION_BLOCK_CLAIMED);
	this->isClaimed = false;
	this->collision = Collision2D::Full;
}

void QuestionBlock::Render()
{
	int ani = ANI_QUESTION_BLOCK;
	if (isClaimed)
		ani = ANI_QUESTION_BLOCK_CLAIMED;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	animation_set[ani]->Render(x - camera->GetCamPosX() + QBLOCK_BBOX_WIDTH / 2, y - camera->GetCamPosY() + QBLOCK_BBOX_HEIGHT / 2, direction, 255);
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
	this->isClaimed = true;
}
