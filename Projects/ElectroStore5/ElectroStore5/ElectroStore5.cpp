#include "stdafx.h"

#include "StoreItem.h"

using namespace System;
using namespace ElectronicsStore;

CStoreItem ^ CreateStoreItem();
static void DescribeStoreItem(CStoreItem ^ %);
static void DescribeStoreItem(CStoreItem ^ %, const int);

int main()
{
	String ^ strTitle = L"=-= Nearson Electonics =-=\n"
		L"******* Store Items ******";

	CStoreItem ^ saleItem = CreateStoreItem();

	Console::WriteLine(L"");
	DescribeStoreItem(saleItem, 0);

	Console::WriteLine();
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
	Console::WriteLine(L"B - Instructional and Tutorials (Books)");
	Console::WriteLine(L"C - Cell Phones and Accessories");
	Console::WriteLine(L"D - Bags and Cases");
	Console::WriteLine(L"H - Headphones");
	Console::WriteLine(L"I - Instructional and Tutorials (VHS & DVD)");
	Console::WriteLine(L"M - Digital Cameras");
	Console::WriteLine(L"O - Cables and Connectors");
	Console::WriteLine(L"P - PDAs and Accessories");
	Console::WriteLine(L"T - Telephones and Accessories");
	Console::WriteLine(L"S - Surge Protector");
	Console::WriteLine(L"V - TVs and Videos");
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
	sItem->ItemNumber = number;
	sItem->Category = category;
	sItem->Make = make;
	sItem->Model = model;
	sItem->DiscountRate = discount;
	sItem->UnitPrice = price;

	return sItem;
}

// This function is used when an item is specified by its make and model
void DescribeStoreItem(CStoreItem ^ %item)
{
	Console::WriteLine(L"Store Item Description");
	Console::WriteLine(L"Item Number:   {0}", item->ItemNumber);
	Console::WriteLine(L"Category:      {0}", item->Category);
	Console::WriteLine(L"Make           {0}", item->Make);
	Console::WriteLine(L"Model:         {0}", item->Model);
	Console::WriteLine(L"Name:          {0}", item->Name);
	Console::WriteLine(L"Discount Rate: {0:P}", item->DiscountRate);
	Console::WriteLine(L"Unit Price:    {0:C}", item->UnitPrice);
}

// This function is used when an item is specified by its name
void DescribeStoreItem(CStoreItem ^ %item, const int)
{
	Console::WriteLine(L"Store Item Description");
	Console::WriteLine(L"Item Number:   {0}", item->ItemNumber);
	Console::WriteLine(L"Category:      {0}", item->Category);
	Console::WriteLine(L"Make           {0}", item->Make);
	Console::WriteLine(L"Model:         {0}", item->Model);
	Console::WriteLine(L"Discount Rate: {0:P}", item->DiscountRate);
	Console::WriteLine(L"Unit Price:    {0:C}", item->UnitPrice);
}