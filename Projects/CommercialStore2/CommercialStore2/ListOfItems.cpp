#include "stdafx.h"
#include "ListOfItems.h"

CListOfItems::CListOfItems(void)
	: Head(nullptr), Size(0)
{
}

CListOfItems::~CListOfItems()
{
	delete Head;
}

CListOfItems::!CListOfItems()
{
}

int CListOfItems::Count()
{
	return Size;
}

int CListOfItems::Add(CItem<double> ^ NewItem)
{
	CItem<double> ^ Sample = gcnew CItem<double>;

	Sample = NewItem;
	Sample->Next = Head;
	Head = Sample;

	return Size++;
}

CItem<double> ^ CListOfItems::Retrieve(int Position)
{
	CItem<double> ^ Current = Head;

	for (int i = Count() - 1; i > Position && Current != nullptr; i--)
	{
		Current = Current->Next;
	}

	return Current;
}
