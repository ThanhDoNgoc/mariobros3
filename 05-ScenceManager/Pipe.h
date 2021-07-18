#pragma once
#define TILE_SIZE	48
#include "GameObject.h"
#define ANI_ID_BLACK_HEAD	0
#define ANI_ID_BLACK_BODY	1
#define ANI_ID_GREEN_HEAD	2
#define ANI_ID_GREEN_BODY	3
enum class PipeType
{
	green,
	black
};
class Pipe : public CGameObject
{
	int pipeWidth, pipeHeight;
	bool directionUp;
	PipeType type = PipeType::green;
public:
	Pipe(int width, int height);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
	void isDirectionUp(bool direction) { this->directionUp = direction; }
	void SetPipeType(PipeType pipeType) { this->type = pipeType; }

};

