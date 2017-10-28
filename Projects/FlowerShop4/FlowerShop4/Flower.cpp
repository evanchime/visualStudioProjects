#include "stdafx.h"
#include "Flower.h"


CFlower::CFlower()
{
	Type = FlowerType::Mixed;
	Color = FlowerColor::Orange;
	Arrangement = FlowerArrangement::Vase;
	pc = 0.00;

	items = 0;
}
