#include "stdafx.h"

#include "Flower.h"

CFlower::CFlower(void)
	: _tp(0), _clr(0),
	_arg(L'B'), _price(45.95)
{
}

CFlower::CFlower(int type)
	: _tp(type),
	_clr(0),
	_arg(L'B'),
	_price(35.95)
{
}

CFlower::CFlower(int type, int color,
	__wchar_t argn, double price)
{
	_tp = type;
	_clr = color;
	_arg = argn;
	_price = price;
}

CFlower::~CFlower()
{
}
