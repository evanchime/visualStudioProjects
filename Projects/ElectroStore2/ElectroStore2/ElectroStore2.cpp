// ElectroStore2.cpp : main project file.

#include "stdafx.h"

#include "StoreItem.h"

using namespace System;
using namespace ElectronicsStore;

CStoreItem ^ CreateStoreItem();
void DescribeStoreItem(CStoreItem ^ %);

int main()
{
	String ^ strTitle = L"=-= Nearson Electonics =-=\n"
		L"******* Store Items ******";
	CStoreItem ^ storeItem = CreateStoreItem();

	Console::WriteLine();
	Console::WriteLine(strTitle);
	DescribeStoreItem(storeItem);

	Console::WriteLine();
	Console::ReadLine();
	return 0;
}

CStoreItem ^ CreateStoreItem()
{
	long        number;
	__wchar_t ^ category;
	String    ^ make;
	String    ^ model;
	double      discount;
	double      price;

	Console::WriteLine(L"To create a store item, enter its information");
	Console::Write(L"Item Number: ");
	number = long::Parse(Console::ReadLine());
	Console::WriteLine(L"Category");
	Console::WriteLine(L"A - Audio Cables");
	Console::WriteLine(L"B - Batteries");
	Console::WriteLine(L"C - Cell Phones and Accessories");
	Console::WriteLine(L"D - Bags and Cases");
	Console::WriteLine(L"H - Headphones");
	Console::WriteLine(L"M - Digital Cameras");
	Console::WriteLine(L"O - Cables and Connectors");
	Console::WriteLine(L"P - PDAs and Accessories");
	Console::WriteLine(L"T - Telephones and Accessories");
	Console::WriteLine(L"S - Surge Protector");
	Console::Write(L"Your Choice? ");
	category = __wchar_t::Parse(Console::ReadLine());
	Console::Write(L"Make         ");
	make = Console::ReadLine();
	Console::Write(L"Model:       ");
	model = Console::ReadLine();
	Console::Write(L"Discount Applied (Enter 0 to 100, 0 if no discount): ");
	discount = double::Parse(Console::ReadLine());
	Console::Write(L"Unit Price:  ");
	price = double::Parse(Console::ReadLine());

	CStoreItem ^ sItem = gcnew CStoreItem;
	sItem->SetItemNumber(number);
	sItem->SetCategory(category);
	sItem->SetMake(make);
	sItem->SetModel(model);
	sItem->SetDiscountRate(discount);
	sItem->SetUnitPrice(price);

	return sItem;
}

void DescribeStoreItem(CStoreItem ^ %item)
{
	Console::WriteLine(L"Store Item Description");
	Console::WriteLine(L"Item Number:   {0}", item->GetItemNumber());
	Console::WriteLine(L"Category:      {0}", item->GetCategory());
	Console::WriteLine(L"Make           {0}", item->GetMake());
	Console::WriteLine(L"Model:         {0}", item->GetModel());
	Console::WriteLine(L"Discount Rate: {0:P}", item->GetDiscountRate());
	Console::WriteLine(L"Unit Price:    {0:C}", item->GetUnitPrice());
}
