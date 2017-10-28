#pragma once
#include "Inventory.h"
#include "Car.h"

using namespace System;

public ref class CCarInventory : public CInventory
{
public:
	CCar ^ Head;
	CCar ^ Current;
	CCar ^ Inventory;

	virtual int Add(CCar ^ NewCar) override;
	virtual CCar ^ Get(int index) override;
	virtual bool Delete() override;

	CCarInventory(void);
};
