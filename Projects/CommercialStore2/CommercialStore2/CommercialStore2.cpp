// CommercialStore2.cpp : main project file.

#include "stdafx.h"

#include "ListOfItems.h"

using namespace System;

int main()
{
	CItem<double> ^ item;
	CListOfItems ^ Items = gcnew CListOfItems;


	item = gcnew CItem<double>;
	item->Item = 97.46;
	Items->Add(item);

	item = gcnew CItem<double>;
	item->Item = 8844.82;
	Items->Add(item);

	item = gcnew CItem<double>;
	item->Item = 108.7873;
	Items->Add(item);

	item = gcnew CItem<double>;
	item->Item = 2764.48;
	Items->Add(item);

	item = gcnew CItem<double>;
	item->Item = 70062.83;
	Items->Add(item);

	Console::WriteLine(L"-=- List of Items -=-");

	for (int i = 0; i < Items->Count(); i++)
	{
		CItem<double> ^ One = Items->Retrieve(i);

		Console::WriteLine(L"Item: {0}", One->Item);
	}

	Console::WriteLine(L"\nNumber of Items: {0}\n", Items->Count());

	return 0;
}