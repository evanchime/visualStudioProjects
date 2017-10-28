#include "stdafx.h"

#include "OrderProcessing.h"

COrderProcessing::COrderProcessing(void)
{
	_flr = gcnew CFlower;
}

COrderProcessing::~COrderProcessing()
{
	delete _flr;
}

double COrderProcessing::GetTotalPrice()
{
	return Quantity * _flr->UnitPrice;
}
