#include "stdafx.h"

#include "Flower.h"

CFlower::CFlower(void)
	: _tp(0), _clr(0),
	_arg(0), _mx(false),
	_price(45.95)
{
}

CFlower::CFlower(int type, int color,
	int argn, bool mx,
	double price)
	: _tp(type),
	_clr(color),
	_arg(argn),
	_mx(mx),
	_price(price)
{
}

CFlower::~CFlower()
{
}
