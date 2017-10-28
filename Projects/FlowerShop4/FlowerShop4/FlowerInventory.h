#pragma once
#include "Flower.h"

public ref class CFlowerInventory : CFlower
{
public:
	CFlower ^ Inventory;

	CFlowerInventory(void);
	CFlower ^ Head;
	int Add(CFlower ^ obj);
	CFlower ^ Get(int index);
	bool Delete();
};

