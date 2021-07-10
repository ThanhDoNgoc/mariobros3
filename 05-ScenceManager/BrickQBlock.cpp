#include "BrickQBlock.h"

BrickQBlock::BrickQBlock()
{
	this->animation_set.clear();
	AddAnimation(ID_ANI_BRICK);
	AddAnimation(ID_ANI_QUESTION_BLOCK_CLAIMED);
}
