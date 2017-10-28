#pragma once
#include "Flower.h"

using namespace System;

public ref class COrderProcessing
{
public:
	CFlower ^ FlowerOrder;

private:
	int qty;
public:
	COrderProcessing(void);

	property int Quantity
	{
		int get() { return qty; }
		void set(int value) { qty = value; }
	}

	property double TotalPrice
	{
		double get() { return Quantity * FlowerOrder->UnitPrice; }
	}

	void GetFlowerType();
	void GetFlowerColor();
	void GetFlowerArrangement();
	void ProcessOrder();
	void ShowOrder();
};

