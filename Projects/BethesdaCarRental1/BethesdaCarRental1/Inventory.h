#pragma once
#include "Car.h"

using namespace System;

public ref class CInventory abstract
{
protected:
	int items;

public:
	CInventory(void);

	property int Count
	{
		int get() { return items; }
	}

	virtual int Add(CCar ^ obj) = 0;
	virtual CCar ^ Get(int index) = 0;
	virtual bool Delete() = 0;
};

