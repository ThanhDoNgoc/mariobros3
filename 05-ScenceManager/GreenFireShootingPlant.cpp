#include "GreenFireShootingPlant.h"

GreenFireShootingPlant::GreenFireShootingPlant()
{
	this->animation_set.clear();
	AddAnimation(ID_ANI_GREEN_SHOOTING_PLANT_DOWN);
	AddAnimation(ID_ANI_GREEN_SHOOTING_PLANT_UP);

	this->fsheight = GREEN_FIRE_SHOOTING_HEIGHT;
}
