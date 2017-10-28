#include "stdafx.h"
#include "FlowerInventory.h"


CFlowerInventory::CFlowerInventory()
{
	Head = nullptr;
	Inventory = gcnew CFlower;
}

int CFlowerInventory::Add(CFlower ^ NewFlower)
{
	CFlower ^ Sample = gcnew CFlower;

	Sample = NewFlower;
	Sample->Next = Head;
	Head = Sample;
	return items++;
}

CFlower ^ CFlowerInventory::Get(int index)
{
	CFlower ^ Current = Head;

	for (int i = Count - 1;
		i > index && Current != nullptr;
		i--)
		Current = Current->Next;
	return Current;
}

bool CFlowerInventory::Delete()
{
	if (Head == nullptr)
	{
		Console::WriteLine(L"The inventory is empty");
		return false;
	}

	CFlower ^ Current;

	/*Current = Head->Next;
	Head->Next = Current->Next;*/

	Current = Head->Next;
	Head = Current;

	items--;
	return true;
}


