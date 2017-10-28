#pragma once

#include "Flower.h"

public ref class COrderProcessing
{
private:
	int       _qty;
	CFlower ^ _flr;

public:
	COrderProcessing(void);
	~COrderProcessing();

	property CFlower ^ Flower
	{
		CFlower ^ get() { return _flr; }
		void set(CFlower ^ flr) { _flr = flr; }
	}

	property int Quantity
	{
		int get() { return _qty; }
		void set(int q)
		{
			_qty = (q <= 0 ? 0 : q);
		}
	}

	double GetTotalPrice();
};

