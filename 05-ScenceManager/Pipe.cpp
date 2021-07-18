#include "Pipe.h"
#include "Camera.h"
#include "Game.h"
Pipe::Pipe(int width, int height)
{
	this->pipeWidth = width;
	this->pipeHeight = height;
	this->type = PipeType::green;
	this->ObjectGroup = Group::ground;
	this->collision = Collision2D::Full;
	
	AddAnimation(ID_ANI_PIPE_BLACK_HEAD);
	AddAnimation(ID_ANI_PIPE_BLACK_BODY);
	AddAnimation(ID_ANI_PIPE_GREEN_HEAD);
	AddAnimation(ID_ANI_PIPE_GREEN_BODY);
	this->objectLayer = LAYER_PIPE;
}

void Pipe::Render()
{
	int ani = ANI_ID_GREEN_HEAD;
	int tile = pipeHeight / TILE_SIZE;
	Camera* camera = CGame::GetInstance()->GetCurrentScene()->GetCamera();
	if (type==PipeType::green)
	{
		if (directionUp)
		{
			animation_set[ANI_ID_GREEN_HEAD]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY());
			for (int i = 1; i < tile; i++)
			{
				animation_set[ANI_ID_GREEN_BODY]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY() + i * TILE_SIZE);
				//RenderBoundingBox();
			}
		}
		else
		{
			animation_set[ANI_ID_GREEN_HEAD]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY() + (tile-1)*TILE_SIZE);
			for (int i = 0; i < tile-1; i++)
			{
				animation_set[ANI_ID_GREEN_BODY]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY() + i * TILE_SIZE);
				//RenderBoundingBox();
			}
		}
	}
	else if (type == PipeType::black)
	{
		animation_set[ANI_ID_BLACK_HEAD]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY() + (tile - 1) * TILE_SIZE);
		for (int i = 0; i < tile - 1; i++)
		{
			animation_set[ANI_ID_BLACK_BODY]->Render(x - camera->GetCamPosX(), y - camera->GetCamPosY() + i * TILE_SIZE);
			//RenderBoundingBox();
		}
	}

}

void Pipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + pipeWidth;
	b = y + pipeHeight;
}
