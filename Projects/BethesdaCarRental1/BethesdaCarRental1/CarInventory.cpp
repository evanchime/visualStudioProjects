#include "stdafx.h"
#include "CarInventory.h"

CCarInventory::CCarInventory(void)
{
	Head = nullptr;
}

int CCarInventory::Add(CCar ^ NewCar)
{
	CCar ^ Sample = gcnew CCar;

	Sample = NewCar;
	Sample->Next = Head;
	Head = Sample;
	return items++;
}

CCar ^ CCarInventory::Get(int index)
{
	CCar ^ Current = Head;

	for (int i = Count - 1;
		i > index && Current != nullptr;
		i--)
		Current = Current->Next;
	return Current;
}

bool CCarInventory::Delete()
{
	if (Head == nullptr)
	{
		Console::WriteLine(L"The inventory is empty");
		return false;
	}

	CCar ^ Current;

	Current = Head->Next;
	Head->Next = Current->Next;
	items--;
	return true;
}
